/************************************************************************
 * sched/wdog/wdog.h
 *
 *   Copyright (C) 2007, 2009 Gregory Nutt. All rights reserved.
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
 ************************************************************************/

#ifndef __SCHED_WDOG_WDOG_H
#define __SCHED_WDOG_WDOG_H

/************************************************************************
 * Included Files
 ************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <wdog.h>

#include <nuttx/compiler.h>

/************************************************************************
 * Pre-processor Definitions
 ************************************************************************/

/************************************************************************
 * Public Type Declarations
 ************************************************************************/

/* This is the watchdog structure.  The WDOG_ID is a pointer to a
 * watchdog structure.
 */

struct wdog_s
{
  FAR struct wdog_s *next;       /* Support for singly linked lists. */
  wdentry_t          func;       /* Function to execute when delay expires */
#ifdef CONFIG_PIC
  FAR void          *picbase;    /* PIC base address */
#endif
  int                lag;        /* Timer associated with the delay */
  bool               active;     /* true if the watchdog is actively timing */
  uint8_t            argc;       /* The number of parameters to pass */
  uint32_t           parm[CONFIG_MAX_WDOGPARMS];
};
typedef struct wdog_s wdog_t;

/************************************************************************
 * Public Variables
 ************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/* The g_wdfreelist data structure is a singly linked list of watchdogs
 * available to the system for delayed function use.
 */

extern sq_queue_t g_wdfreelist;

/* g_wdpool is a pointer to a list of pre-allocated watchdogs. The number
 * of watchdogs in the pool is a configuration item.
 */

extern FAR wdog_t *g_wdpool;

/* The g_wdactivelist data structure is a singly linked list ordered by
 * watchdog expiration time. When watchdog timers expire,the functions on
 * this linked list are removed and the function is called.
 */

extern sq_queue_t g_wdactivelist;

/************************************************************************
 * Public Function Prototypes
 ************************************************************************/

/************************************************************************
 * Name: wd_initialize
 *
 * Description:
 * This function initializes the watchdog data structures
 *
 * Parameters:
 *   None
 *
 * Return Value:
 *   None
 *
 * Assumptions:
 *   This function must be called early in the initialization sequence
 *   before the timer interrupt is attached and before any watchdog
 *   services are used.
 *
 ************************************************************************/

void weak_function wd_initialize(void);

/****************************************************************************
 * Name: wd_timer
 *
 * Description:
 *   This function is called from the timer interrupt handler to determine
 *   if it is time to execute a watchdog function.  If so, the watchdog
 *   function will be executed in the context of the timer interrupt
 *   handler.
 *
 * Parameters:
 *   ticks - If CONFIG_SCHED_TICKLESS is defined then the number of ticks
 *     in the the interval that just expired is provided.  Otherwise,
 *     this function is called on each timer interrupt and a value of one
 *     is implicit.
 *
 * Return Value:
 *   If CONFIG_SCHED_TICKLESS is defined then the number of ticks for the
 *   next delay is provided (zero if no delay).  Otherwise, this function
 *   has no returned value.
 *
 * Assumptions:
 *   Called from interrupt handler logic with interrupts disabled.
 *
 ****************************************************************************/

#ifdef CONFIG_SCHED_TICKLESS
unsigned int wd_timer(int ticks);
#else
void wd_timer(void);
#endif

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __SCHED_WDOG_WDOG_H */
