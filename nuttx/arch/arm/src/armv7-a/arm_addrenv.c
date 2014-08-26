/****************************************************************************
 * arch/arm/src/armv7/arm_addrenv.c
 *
 *   Copyright (C) 2014 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
/****************************************************************************
 * Address Environment Interfaces
 *
 * Low-level interfaces used in binfmt/ to instantiate tasks with address
 * environments.  These interfaces all operate on type group_addrenv_t which
 * is an abstract representation of a task group's address environment and
 * must be defined in arch/arch.h if CONFIG_ARCH_ADDRENV is defined.
 *
 *   up_addrenv_create  - Create an address environment
 *   up_addrenv_destroy - Destroy an address environment.
 *   up_addrenv_vtext   - Returns the virtual base address of the .text
 *                        address environment
 *   up_addrenv_vdata   - Returns the virtual base address of the .bss/.data
 *                        address environment
 *   up_addrenv_select  - Instantiate an address environment
 *   up_addrenv_restore - Restore an address environment
 *   up_addrenv_assign  - Assign an address environment to a group
 *
 * Higher-level interfaces used by the tasking logic.  These interfaces are
 * used by the functions in sched/ and all operate on the thread which whose
 * group been assigned an address environment by up_addrenv_assign().
 *
 *   up_addrenv_attach  - Clone the address environment assigned to one TCB
 *                        to another.  This operation is done when a pthread
 *                        is created that share's the same address
 *                        environment.
 *   up_addrenv_detach  - Release the threads reference to an address
 *                        environment when a task/thread exits.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <string.h>
#include <errno.h>

#include <nuttx/arch.h>
#include <nuttx/addrenv.h>

#include <arch/arch.h>
#include <arch/irq.h>

#include "mmu.h"

#ifdef CONFIG_ARCH_ADDRENV

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/* Using a 4KiB page size, each 1MiB section maps to a PTE containing
 * 256*2KiB entries
 */

#define ENTRIES_PER_L2TABLE 256

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: set_l2_entry
 *
 * Description:
 *   Set the L2 table entry as part of the initialization of the L2 Page
 *   table.
 *
 ****************************************************************************/

static void set_l2_entry(FAR uint32_t *l2table, uintptr_t paddr,
                         uintptr_t vaddr, uint32_t mmuflags)
{
  uint32_t index;

  /* The table divides a 1Mb address space up into 256 entries, each
   * corresponding to 4Kb of address space.  The page table index is
   * related to the offset from the beginning of 1Mb region.
   */

  index = (vaddr & 0x000ff000) >> 12;

  /* Save the table entry */

  l2table[index] = (paddr | mmuflags);
}

/****************************************************************************
 * Name: set_l1_entry
 *
 * Description:
 *   Set an L1 page table entry to refer to a specific L2 page table.
 *
 ****************************************************************************/

static inline void set_l1_entry(uintptr_t l2vaddr, uintptr_t l2paddr)
{
  mmu_l1_setentry(l2paddr & PMD_PTE_PADDR_MASK,
                  l2vaddr & PMD_PTE_PADDR_MASK,
                  MMU_L1_PGTABFLAGS);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_addrenv_create
 *
 * Description:
 *   This function is called when a new task is created in order to
 *   instantiate an address environment for the new task group.
 *   up_addrenv_create() is essentially the allocator of the physical
 *   memory for the new task.
 *
 * Input Parameters:
 *   textsize - The size (in bytes) of the .text address environment needed
 *     by the task.  This region may be read/execute only.
 *   datasize - The size (in bytes) of the .data/.bss address environment
 *     needed by the task.  This region may be read/write only.
 *   addrenv - The location to return the representation of the task address
 *     environment.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int up_addrenv_create(size_t textsize, size_t datasize,
                      FAR group_addrenv_t *addrenv)
{
  irqstate_t flags;
  uintptr_t vaddr;
  uintptr_t paddr;
  FAR uint32_t *l2table;
  uint32_t l1save;
  size_t nmapped;
  unsigned int ntextpages;
  unsigned int ndatapages;
  unsigned int i;
  unsigned int j;
  int ret;

  DEBUGASSERT(addrenv);

  /* Initialize the address environment structure to all zeroes */

  memset(addrenv, 0, sizeof(group_addrenv_t));

  /* Verify that we are configured with enough virtual address space to
   * support this address environment.
   */

  ntextpages = MM_NPAGES(textsize);
  ndatapages = MM_NPAGES(datasize);

  if (ntextpages > ARCH_TEXT_NSECTS || ndatapages > ARCH_DATA_NSECTS)
    {
      return -E2BIG;
    }

  /* Back the allocation up with physical pages and set up the level mapping
   * (which of course does nothing until the L2 page table is hooked into
   * the L1 page table).
   */

  /* Allocate .text space pages */

  vaddr   = CONFIG_ARCH_TEXT_VBASE;
  nmapped = 0;

  for (i = 0; i < ntextpages; i++)
    {
      /* Allocate one physical page */

      paddr = mm_pgalloc(1);
      if (!paddr)
        {
          ret = -ENOMEM;
          goto errout;
        }
      
      DEBUGASSERT(MM_ISALIGNED(paddr));
      addrenv->text[i] = (FAR uint32_t *)paddr;

      /* Temporarily map the page into the virtual address space */

      flags = irqsave();
      l1save = mmu_l1_getentry(ARCH_SCRATCH_VBASE);
      set_l1_entry(ARCH_SCRATCH_VBASE, paddr);
      l2table = (FAR uint32_t *)ARCH_SCRATCH_VBASE;

      /* Initialize the page table */

      memset(l2table, 0, ENTRIES_PER_L2TABLE * sizeof(uint32_t));
      for (j = 0; j < ENTRIES_PER_L2TABLE && nmapped < textsize; j++)
        {
          set_l2_entry(l2table, paddr, vaddr, MMU_L2_TEXTFLAGS);
          nmapped += MM_PGSIZE;
          paddr   += MM_PGSIZE;
          vaddr   += MM_PGSIZE;
        }

      /* Restore the original L1 page table entry */

      mmu_l1_restore(ARCH_SCRATCH_VBASE, l1save);
      irqrestore(flags);
    }

  /* Allocate .bss/.data space pages */

  vaddr   = CONFIG_ARCH_DATA_VBASE;
  nmapped = 0;

  for (i = 0; i < ndatapages; i++)
    {
      /* Allocate one physical page */

      paddr = mm_pgalloc(1);
      if (!paddr)
        {
          ret = -ENOMEM;
          goto errout;
        }
      
      DEBUGASSERT(MM_ISALIGNED(paddr));
      addrenv->data[i] = (FAR uint32_t *)paddr;

      /* Temporarily map the page into the virtual address space */

      flags = irqsave();
      l1save = mmu_l1_getentry(ARCH_SCRATCH_VBASE);
      set_l1_entry(ARCH_SCRATCH_VBASE, paddr);
      l2table = (FAR uint32_t *)ARCH_SCRATCH_VBASE;

      /* Initialize the page table */

      memset(l2table, 0, ENTRIES_PER_L2TABLE * sizeof(uint32_t));
      for (j = 0; j < ENTRIES_PER_L2TABLE && nmapped < datasize; j++)
        {
          set_l2_entry(l2table, paddr, vaddr, MMU_L2_DATAFLAGS);
          nmapped += MM_PGSIZE;
          paddr   += MM_PGSIZE;
          vaddr   += MM_PGSIZE;
        }

      /* Restore the original L1 page table entry */

      mmu_l1_restore(ARCH_SCRATCH_VBASE, l1save);
      irqrestore(flags);
    }

  /* Notice that no pages are yet allocated for the heap */

  return OK;

errout:
  up_addrenv_destroy(addrenv);
  return ret;
}

/****************************************************************************
 * Name: up_addrenv_destroy
 *
 * Description:
 *   This function is called when a final thread leaves the task group and
 *   the task group is destroyed.  This function then destroys the defunct
 *   address environment, releasing the underlying physical memory.
 *
 * Input Parameters:
 *   addrenv - The address environment to be destroyed.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int up_addrenv_destroy(FAR group_addrenv_t *addrenv)
{
  uintptr_t vaddr;
  int i;

  DEBUGASSERT(addrenv);

  for (vaddr = CONFIG_ARCH_TEXT_VBASE, i = 0;
       i < ARCH_TEXT_NSECTS;
       vaddr += MM_PGSIZE, i++)
    {
      mmu_l1_clrentry(vaddr);
      if (addrenv->text[i])
        {
          mm_pgfree((uintptr_t)addrenv->text[i], ARCH_SECT2PG(1));
        }
    }

  for (vaddr = CONFIG_ARCH_DATA_VBASE, i = 0;
       i < ARCH_DATA_NSECTS;
       vaddr += MM_PGSIZE, i++)
    {
      mmu_l1_clrentry(vaddr);
      if (addrenv->data[i])
        {
          mm_pgfree((uintptr_t)addrenv->data[i], ARCH_SECT2PG(1));
        }
    }

#if 0 /* Not yet implemented */
  for (vaddr = CONFIG_ARCH_HEAP_VBASE, i = 0;
       i < ARCH_HEAP_NSECTS;
       vaddr += MM_PGSIZE, i++)
    {
      mmu_l1_clrentry(vaddr);
      if (addrenv->heap[i])
        {
          mm_pgfree((uintptr_t)addrenv->heap[i], ARCH_SECT2PG(1));
        }
    }
#endif

  memset(addrenv, 0, sizeof(group_addrenv_t));
  return OK;
}

/****************************************************************************
 * Name: up_addrenv_vtext
 *
 * Description:
 *   Return the virtual address associated with the newly create .text
 *   address environment.  This function is used by the binary loaders in
 *   order get an address that can be used to initialize the new task.
 *
 * Input Parameters:
 *   addrenv - The representation of the task address environment previously
 *      returned by up_addrenv_create.
 *   vtext - The location to return the virtual address.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int up_addrenv_vtext(FAR group_addrenv_t *addrenv, FAR void **vtext)
{
  /* Not much to do in this case */

  DEBUGASSERT(addrenv && vtext);
  *vtext = (FAR void *)CONFIG_ARCH_TEXT_VBASE;
  return OK;
}

/****************************************************************************
 * Name: up_addrenv_vdata
 *
 * Description:
 *   Return the virtual address associated with the newly create .text
 *   address environment.  This function is used by the binary loaders in
 *   order get an address that can be used to initialize the new task.
 *
 * Input Parameters:
 *   addrenv - The representation of the task address environment previously
 *      returned by up_addrenv_create.
 *   textsize - For some implementations, the text and data will be saved
 *      in the same memory region (read/write/execute) and, in this case,
 *      the virtual address of the data just lies at this offset into the
 *      common region.
 *   vdata - The location to return the virtual address.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int up_addrenv_vdata(FAR group_addrenv_t *addrenv, uintptr_t textsize,
                     FAR void **vdata)
{
  /* Not much to do in this case */

  DEBUGASSERT(addrenv && vdata);
  *vdata = (FAR void *)CONFIG_ARCH_DATA_VBASE;
  return OK;
}

/****************************************************************************
 * Name: up_addrenv_select
 *
 * Description:
 *   After an address environment has been established for a task group (via
 *   up_addrenv_create().  This function may be called to to instantiate
 *   that address environment in the virtual address space.  this might be
 *   necessary, for example, to load the code for the task group from a file or
 *   to access address environment private data.
 *
 * Input Parameters:
 *   addrenv - The representation of the task address environment previously
 *     returned by up_addrenv_create.
 *   oldenv
 *     The address environment that was in place before up_addrenv_select().
 *     This may be used with up_addrenv_restore() to restore the original
 *     address environment that was in place before up_addrenv_select() was
 *     called.  Note that this may be a task agnostic, platform-specific
 *     representation that may or may not be different from group_addrenv_t.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int up_addrenv_select(FAR const group_addrenv_t *addrenv,
                      FAR save_addrenv_t *oldenv)
{
  uintptr_t vaddr;
  uintptr_t paddr;
  int i;

  DEBUGASSERT(addrenv);

  for (vaddr = CONFIG_ARCH_TEXT_VBASE, i = 0;
       i < ARCH_TEXT_NSECTS;
       vaddr += MM_PGSIZE, i++)
    {
      /* Save the old L1 page table entry */

      if (oldenv)
        {
          oldenv->text[i] = mmu_l1_getentry(vaddr);
        }

      /* Set (or clear) the new page table entry */

      paddr = (uintptr_t)addrenv->text[i];
      if (paddr)
        {
          set_l1_entry(vaddr, paddr);
        }
      else
        {
          mmu_l1_clrentry(vaddr);
        }
    }

  for (vaddr = CONFIG_ARCH_DATA_VBASE, i = 0;
       i < ARCH_DATA_NSECTS;
       vaddr += MM_PGSIZE, i++)
    {
      /* Save the old L1 page table entry */

      if (oldenv)
        {
          oldenv->data[i] = mmu_l1_getentry(vaddr);
        }

      /* Set (or clear) the new page table entry */

      paddr = (uintptr_t)addrenv->data[i];
      if (paddr)
        {
          set_l1_entry(vaddr, paddr);
        }
      else
        {
          mmu_l1_clrentry(vaddr);
        }
    }

#if 0 /* Not yet implemented */
  for (vaddr = CONFIG_ARCH_HEAP_VBASE, i = 0;
       i < ARCH_HEAP_NSECTS;
       vaddr += MM_PGSIZE, i++)
    {
      /* Save the old L1 page table entry */

      if (oldenv)
        {
          oldenv->heap[i] = mmu_l1_getentry(vaddr);
        }

      /* Set (or clear) the new page table entry */

      paddr = (uintptr_t)addrenv->heap[i];
      if (paddr)
        {
          set_l1_entry(vaddr, paddr);
        }
      else
        {
          mmu_l1_clrentry(vaddr);
        }
    }
#endif

  return OK;
}

/****************************************************************************
 * Name: up_addrenv_restore
 *
 * Description:
 *   After an address environment has been temporarily instantiated by
 *   up_addrenv_select(), this function may be called to to restore the
 *   original address environment.
 *
 * Input Parameters:
 *   oldenv - The platform-specific representation of the address environment
 *     previously returned by up_addrenv_select.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int up_addrenv_restore(FAR const save_addrenv_t *oldenv)
{
  uintptr_t vaddr;
  int i;

  DEBUGASSERT(oldenv);

  for (vaddr = CONFIG_ARCH_TEXT_VBASE, i = 0;
       i < ARCH_TEXT_NSECTS;
       vaddr += MM_PGSIZE, i++)
    {
      /* Restore the L1 page table entry */

      mmu_l1_restore(vaddr, oldenv->text[i]);
    }

  for (vaddr = CONFIG_ARCH_DATA_VBASE, i = 0;
       i < ARCH_DATA_NSECTS;
       vaddr += MM_PGSIZE, i++)
    {
      /* Restore the L1 page table entry */

      mmu_l1_restore(vaddr, oldenv->data[i]);
    }

#if 0 /* Not yet implemented */
  for (vaddr = CONFIG_ARCH_HEAP_VBASE, i = 0;
       i < ARCH_HEAP_NSECTS;
       vaddr += MM_PGSIZE, i++)
    {
      /* Restore the L1 page table entry */

      mmu_l1_restore(vaddr, oldenv->heap[i]);
    }
#endif

  return OK;
}

/****************************************************************************
 * Name: up_addrenv_assign
 *
 * Description:
 *   Assign an address environment to a new task group.
 *
 * Input Parameters:
 *   addrenv - The representation of the task address environment previously
 *     returned by up_addrenv_create().
 *   group - The new task group to receive the address environment.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int up_addrenv_assign(FAR const group_addrenv_t *addrenv,
                      FAR struct task_group_s *group)
{
  DEBUGASSERT(addrenv && group);

  /* Just copy the address environment into the group */

  memcpy(&group->addrenv, addrenv, sizeof(group_addrenv_t));
  return OK;
}

/****************************************************************************
 * Name: up_addrenv_attach
 *
 * Description:
 *   This function is called from the core scheduler logic when a thread
 *   is created that needs to share the address environment of its task
 *   group.
 *
 *   NOTE: In some platforms, nothing will need to be done in this case.
 *   Simply being a member of the group that has the address environment
 *   may be sufficient.
 *
 * Input Parameters:
 *   group - The task group to which the new thread belongs.
 *   tcb   - The TCB of the thread needing the address environment.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int up_addrenv_attach(FAR struct task_group_s *group, FAR struct tcb_s *tcb)
{
  /* Nothing needs to be done in this implementation */

  return OK;
}

/****************************************************************************
 * Name: up_addrenv_detach
 *
 * Description:
 *   This function is called when a task or thread exits in order to release
 *   its reference to an address environment.  The address environment,
 *   however, should persist until up_addrenv_destroy() is called when the
 *   task group is itself destroyed.  Any resources unique to this thread
 *   may be destroyed now.
 *
 *   NOTE: In some platforms, nothing will need to be done in this case.
 *   Simply being a member of the group that has the address environment
 *   may be sufficient.
 *
 * Input Parameters:
 *   group - The group to which the thread belonged.
 *   tcb - The TCB of the task or thread whose the address environment will
 *     be released.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int up_addrenv_detach(FAR struct task_group_s *group, FAR struct tcb_s *tcb)
{
  /* Nothing needs to be done in this implementation */

  return OK;
}

#endif /* CONFIG_ARCH_ADDRENV */
