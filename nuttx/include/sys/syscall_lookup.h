/****************************************************************************
 * syscall/syscall_lookup.h
 *
 *   Copyright (C) 2011, 2013 Gregory Nutt. All rights reserved.
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
 * Pre-processor Definitions
 ****************************************************************************/

/* SYSCALL_LOOKUP must be defined before including this file.
 *
 * These first system calls are supported regardless of the NuttX
 * configuration
 */

SYSCALL_LOOKUP1(_exit,                    _exit,                    1, STUB__exit)
SYSCALL_LOOKUP(exit,                      exit,                      1, STUB_exit)
SYSCALL_LOOKUP(get_errno,                 get_errno,                 0, STUB_get_errno)
SYSCALL_LOOKUP(getpid,                    getpid,                    0, STUB_getpid)
SYSCALL_LOOKUP(sched_getparam,            sched_getparam,            2, STUB_sched_getparam)
SYSCALL_LOOKUP(sched_getscheduler,        sched_getscheduler,        1, STUB_sched_getscheduler)
SYSCALL_LOOKUP(sched_lock,                sched_lock,                0, STUB_sched_lock)
SYSCALL_LOOKUP(sched_lockcount,           sched_lockcount,           0, STUB_sched_lockcount)
SYSCALL_LOOKUP(sched_rr_get_interval,     sched_rr_get_interval,     2, STUB_sched_rr_get_interval)
SYSCALL_LOOKUP(sched_setparam,            sched_setparam,            2, STUB_sched_setparam)
SYSCALL_LOOKUP(sched_setscheduler,        sched_setscheduler,        3, STUB_sched_setscheduler)
SYSCALL_LOOKUP(sched_unlock,              sched_unlock,              0, STUB_sched_unlock)
SYSCALL_LOOKUP(sched_yield,               sched_yield,               0, STUB_sched_yield)
SYSCALL_LOOKUP(sem_close,                 sem_close,                 1, STUB_sem_close)
SYSCALL_LOOKUP(sem_destroy,               sem_destroy,               2, STUB_sem_destroy)
SYSCALL_LOOKUP(sem_open,                  sem_open,                  6, STUB_sem_open)
SYSCALL_LOOKUP(sem_post,                  sem_post,                  1, STUB_sem_post)
SYSCALL_LOOKUP(sem_timedwait,             sem_timedwait,             2, STUB_sem_timedwait)
SYSCALL_LOOKUP(sem_trywait,               sem_trywait,               1, STUB_sem_trywait)
SYSCALL_LOOKUP(sem_unlink,                sem_unlink,                1, STUB_sem_unlink)
SYSCALL_LOOKUP(sem_wait,                  sem_wait,                  1, STUB_sem_wait)
SYSCALL_LOOKUP(set_errno,                 set_errno,                 1, STUB_set_errno)
SYSCALL_LOOKUP(task_create,               task_create,               5, STUB_task_create)
SYSCALL_LOOKUP(task_delete,               task_delete,               1, STUB_task_delete)
SYSCALL_LOOKUP(task_restart,              task_restart,              1, STUB_task_restart)
SYSCALL_LOOKUP(up_assert,                 up_assert,                 2, STUB_up_assert)

SYSCALL_LOOKUP(register_driver,		   register_driver,		   4, STUB_register_driver)
SYSCALL_LOOKUP(unregister_driver,		   unregister_driver,		   1, STUB_unregister_driver)
SYSCALL_LOOKUP(sched_foreach,		   	   sched_foreach,		   	   2, STUB_sched_foreach)

/* The following can be individually enabled */

#ifdef CONFIG_ARCH_HAVE_VFORK
  SYSCALL_LOOKUP(vfork,                   vfork,                   0, STUB_vfork)
#endif

#ifdef CONFIG_SCHED_ATEXIT
  SYSCALL_LOOKUP(atexit,                  atexit,                  1, STUB_atexit)
#endif

#ifdef CONFIG_SCHED_ONEXIT
  SYSCALL_LOOKUP(on_exit,                 on_exit,                 2, STUB_on_exit)
#endif

#ifdef CONFIG_SCHED_WAITPID
  SYSCALL_LOOKUP(waitpid,                 waitpid,                 3, STUB_waitpid)
#  ifdef CONFIG_SCHED_HAVE_PARENT
  SYSCALL_LOOKUP(wait,                    wait,                    1, STUB_wait)
  SYSCALL_LOOKUP(waitid,                  waitid,                  4, STUB_waitid)
#  endif
#endif

/* The following can only be defined if we are configured to execute
 * programs from a file system.
 */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS)
#  ifdef CONFIG_BINFMT_EXEPATH
  SYSCALL_LOOKUP(posix_spawnp,            posix_spawnp,            6, STUB_posix_spawnp)
#  else
  SYSCALL_LOOKUP(posix_spawn,             posix_spawn,             6, STUB_posix_spawn)
#  endif
  SYSCALL_LOOKUP(execv,                   execv,                   2, STUB_execv)
  SYSCALL_LOOKUP(execl,                   execl,                   6, STUB_execl)

  SYSCALL_LOOKUP(exec_getsymtab,		exec_getsymtab,			2, STUB_exec_getsymtab)
  SYSCALL_LOOKUP(exec_setsymtab,		exec_setsymtab,     		2, STUB_exec_setsymtab)  
#endif

/* The following are only defined is signals are supported in the NuttX
 * configuration.
 */

#ifndef CONFIG_DISABLE_SIGNALS
  SYSCALL_LOOKUP(kill,                    kill,                    2, STUB_kill)
  SYSCALL_LOOKUP(sigaction,               sigaction,               3, STUB_sigaction)
  SYSCALL_LOOKUP(sigpending,              sigpending,              1, STUB_sigpending)
  SYSCALL_LOOKUP(sigprocmask,             sigprocmask,             3, STUB_sigprocmask)
  SYSCALL_LOOKUP(sigqueue,                sigqueue,                3, STUB_sigqueue)
  SYSCALL_LOOKUP(sigsuspend,              sigsuspend,              1, STUB_sigsuspend)
  SYSCALL_LOOKUP(sigtimedwait,            sigtimedwait,            3, STUB_sigtimedwait)
  SYSCALL_LOOKUP(sigwaitinfo,             sigwaitinfo,             2, STUB_sigwaitinfo)
  SYSCALL_LOOKUP(nanosleep,               nanosleep,               2, STUB_nanosleep)
#endif

/* The following are only defined if the system clock is enabled in the
 * NuttX configuration.
 */

#ifndef CONFIG_DISABLE_CLOCK
  SYSCALL_LOOKUP(clock_systimer,  		    syscall_clock_systimer,  		    0, STUB_clock_systimer)
  SYSCALL_LOOKUP(clock_getres,            clock_getres,            2, STUB_clock_getres)
  SYSCALL_LOOKUP(clock_gettime,           clock_gettime,           2, STUB_clock_gettime)
  SYSCALL_LOOKUP(clock_settime,           clock_settime,           2, STUB_clock_settime)
  SYSCALL_LOOKUP(gettimeofday,            gettimeofday,            2, STUB_gettimeofday)
#endif

/* The following are defined only if POSIX timers are supported */

#ifndef CONFIG_DISABLE_POSIX_TIMERS
  SYSCALL_LOOKUP(timer_create,            timer_create,            3, STUB_timer_create)
  SYSCALL_LOOKUP(timer_delete,            timer_delete,            1, STUB_timer_delete)
  SYSCALL_LOOKUP(timer_getoverrun,        timer_getoverrun,        1, STUB_timer_getoverrun)
  SYSCALL_LOOKUP(timer_gettime,           timer_gettime,           2, STUB_timer_gettime)
  SYSCALL_LOOKUP(timer_settime,           timer_settime,           4, STUB_timer_settime)
#endif

/* The following are defined if either file or socket descriptor are
 * enabled.
 */

#if CONFIG_NFILE_DESCRIPTORS > 0 || CONFIG_NSOCKET_DESCRIPTORS > 0
  SYSCALL_LOOKUP(close,                   close,                   1, STUB_close)
  SYSCALL_LOOKUP(ioctl,                   ioctl,                   3, STUB_ioctl)
  SYSCALL_LOOKUP(read,                    read,                    3, STUB_read)
  SYSCALL_LOOKUP(write,                   write,                   3, STUB_write)
#  ifndef CONFIG_DISABLE_POLL
  SYSCALL_LOOKUP(poll,                    poll,                    3, STUB_poll)
  SYSCALL_LOOKUP(select,                  select,                  5, STUB_select)
#  endif
#endif

/* The following are defined if file descriptors are enabled */

#if CONFIG_NFILE_DESCRIPTORS > 0
  SYSCALL_LOOKUP(closedir,                closedir,                1, STUB_closedir)
  SYSCALL_LOOKUP(dup,                     dup,                     1, STUB_dup)
  SYSCALL_LOOKUP(dup2,                    dup2,                    2, STUB_dup2)
  SYSCALL_LOOKUP(fcntl,                   fcntl,                   6, STUB_fcntl)
  SYSCALL_LOOKUP(lseek,                   lseek,                   3, STUB_lseek)
  SYSCALL_LOOKUP(mkfifo,                  mkfifo,                  2, STUB_mkfifo)
  SYSCALL_LOOKUP(mmap,                    mmap,                    6, STUB_mmap)
  SYSCALL_LOOKUP(open,                    open,                    6, STUB_open)
  SYSCALL_LOOKUP(opendir,                 opendir,                 1, STUB_opendir)
  SYSCALL_LOOKUP(pipe,                    pipe,                    1, STUB_pipe)
  SYSCALL_LOOKUP(readdir,                 readdir,                 1, STUB_readdir)
  SYSCALL_LOOKUP(rewinddir,               rewinddir,               1, STUB_rewinddir)
  SYSCALL_LOOKUP(seekdir,                 seekdir,                 2, STUB_seekdir)
  SYSCALL_LOOKUP(stat,                    stat,                    2, STUB_stat)
  SYSCALL_LOOKUP(statfs,                  statfs,                  2, STUB_statfs)
  SYSCALL_LOOKUP(telldir,                 telldir,                 1, STUB_telldir)

#  if CONFIG_NFILE_STREAMS > 0
  SYSCALL_LOOKUP(fs_fdopen,                  fs_fdopen,                  3, STUB_fs_fdopen)
  SYSCALL_LOOKUP(sched_getstreams,        sched_getstreams,        0, STUB_sched_getstreams)
#  endif

#  if defined(CONFIG_NET_SENDFILE)
  SYSCALL_LOOKUP(sendfile,                sendfile,                4, STUB_sendfile)
#  endif

#  if !defined(CONFIG_DISABLE_MOUNTPOINT)
  SYSCALL_LOOKUP(fsync,                   fsync,                   1, STUB_fsync)
  SYSCALL_LOOKUP(mkdir,                   mkdir,                   2, STUB_mkdir)
  SYSCALL_LOOKUP(mount,                   mount,                   5, STUB_mount)
  SYSCALL_LOOKUP(rename,                  rename,                  2, STUB_rename)
  SYSCALL_LOOKUP(rmdir,                   rmdir,                   1, STUB_rmdir)
  SYSCALL_LOOKUP(umount,                  umount,                  1, STUB_umount)
  SYSCALL_LOOKUP(unlink,                  unlink,                  1, STUB_unlink)
  SYSCALL_LOOKUP(losetup, 				   losetup, 				   5, STUB_losetup)
  SYSCALL_LOOKUP(loteardown,			   loteardown,			   1, STUB_loteardown)  
  SYSCALL_LOOKUP(bchlib_teardown,		   bchlib_teardown,		   1, STUB_bchlib_teardown)  
  SYSCALL_LOOKUP(bchlib_setup,			   bchlib_setup,			   3, STUB_bchlib_setup)  
  SYSCALL_LOOKUP(bchlib_read,			   bchlib_read,			   4, STUB_bchlib_read)  
  SYSCALL_LOOKUP(bchlib_write,			   bchlib_write,			   4, STUB_bchlib_write)  
  
#    if defined(CONFIG_FS_FAT)  
       SYSCALL_LOOKUP(mkfatfs,         	   mkfatfs,         	   2, STUB_mkfatfs)    
#    endif 
#  endif
#endif

/* The following are defined if pthreads are enabled */

#ifndef CONFIG_DISABLE_PTHREAD
  SYSCALL_LOOKUP(pthread_barrier_destroy, pthread_barrier_destroy, 1, STUB_pthread_barrier_destroy)
  SYSCALL_LOOKUP(pthread_barrier_init,    pthread_barrier_init,    3, STUB_pthread_barrier_init)
  SYSCALL_LOOKUP(pthread_barrier_wait,    pthread_barrier_wait,    1, STUB_pthread_barrier_wait)
  SYSCALL_LOOKUP(pthread_cancel,          pthread_cancel,          1, STUB_pthread_cancel)
  SYSCALL_LOOKUP(pthread_cond_broadcast,  pthread_cond_broadcast,  1, STUB_pthread_cond_broadcast)
  SYSCALL_LOOKUP(pthread_cond_destroy,    pthread_cond_destroy,    1, STUB_pthread_cond_destroy)
  SYSCALL_LOOKUP(pthread_cond_init,       pthread_cond_init,       2, STUB_pthread_cond_init)
  SYSCALL_LOOKUP(pthread_cond_signal,     pthread_cond_signal,     1, STUB_pthread_cond_signal)
  SYSCALL_LOOKUP(pthread_cond_wait,       pthread_cond_wait,       2, STUB_pthread_cond_wait)
  SYSCALL_LOOKUP(pthread_create,          pthread_create,          4, STUB_pthread_create)
  SYSCALL_LOOKUP(pthread_detach,          pthread_detach,          1, STUB_pthread_detach)
  SYSCALL_LOOKUP(pthread_exit,            pthread_exit,            1, STUB_pthread_exit)
  SYSCALL_LOOKUP(pthread_getschedparam,   pthread_getschedparam,   3, STUB_pthread_getschedparam)
  SYSCALL_LOOKUP(pthread_getspecific,     pthread_getspecific,     1, STUB_pthread_getspecific)
  SYSCALL_LOOKUP(pthread_join,            pthread_join,            2, STUB_pthread_join)
  SYSCALL_LOOKUP(pthread_key_create,      pthread_key_create,      2, STUB_pthread_key_create)
  SYSCALL_LOOKUP(pthread_key_delete,      pthread_key_delete,      1, STUB_pthread_key_delete)
  SYSCALL_LOOKUP(pthread_mutex_destroy,   pthread_mutex_destroy,   1, STUB_pthread_mutex_destroy)
  SYSCALL_LOOKUP(pthread_mutex_init,      pthread_mutex_init,      2, STUB_pthread_mutex_init)
  SYSCALL_LOOKUP(pthread_mutex_lock,      pthread_mutex_lock,      1, STUB_pthread_mutex_lock)
  SYSCALL_LOOKUP(pthread_mutex_trylock,   pthread_mutex_trylock,   1, STUB_pthread_mutex_trylock)
  SYSCALL_LOOKUP(pthread_mutex_unlock,    pthread_mutex_unlock,    1, STUB_pthread_mutex_unlock)
  SYSCALL_LOOKUP(pthread_once,            pthread_once,            2, STUB_pthread_once)
  SYSCALL_LOOKUP(pthread_setcancelstate,  pthread_setcancelstate,  2, STUB_pthread_setcancelstate)
  SYSCALL_LOOKUP(pthread_setschedparam,   pthread_setschedparam,   3, STUB_pthread_setschedparam)
  SYSCALL_LOOKUP(pthread_setschedprio,    pthread_setschedprio,    2, STUB_pthread_setschedprio)
  SYSCALL_LOOKUP(pthread_setspecific,     pthread_setspecific,     2, STUB_pthread_setspecific)
  SYSCALL_LOOKUP(pthread_yield,           pthread_yield,           0, STUB_pthread_yield)
#  ifndef CONFIG_DISABLE_SIGNAL
  SYSCALL_LOOKUP(pthread_cond_timedwait,  pthread_cond_timedwait,  3, STUB_pthread_cond_timedwait)
  SYSCALL_LOOKUP(pthread_kill,            pthread_kill,            2, STUB_pthread_kill)
  SYSCALL_LOOKUP(pthread_sigmask,         pthread_sigmask,         3, STUB_pthread_sigmask)
#  endif
#endif

/* The following are defined only if message queues are enabled */

#ifndef CONFIG_DISABLE_MQUEUE
  SYSCALL_LOOKUP(mq_close,                mq_close,                1, STUB_mq_close)
  SYSCALL_LOOKUP(mq_notify,               mq_notify,               2, STUB_mq_notify)
  SYSCALL_LOOKUP(mq_open,                 mq_open,                 6, STUB_mq_open)
  SYSCALL_LOOKUP(mq_receive,              mq_receive,              4, STUB_mq_receive)
  SYSCALL_LOOKUP(mq_send,                 mq_send,                 4, STUB_mq_send)
  SYSCALL_LOOKUP(mq_timedreceive,         mq_timedreceive,         5, STUB_mq_timedreceive)
  SYSCALL_LOOKUP(mq_timedsend,            mq_timedsend,            5, STUB_mq_timedsend)
  SYSCALL_LOOKUP(mq_unlink,               mq_unlink,               1, STUB_mq_unlink)
#endif

/* The following are defined only if environment variables are supported */

#ifndef CONFIG_DISABLE_ENVIRON
  SYSCALL_LOOKUP(clearenv,                clearenv,                0, STUB_clearenv)
  SYSCALL_LOOKUP(getenv,                  getenv,                  1, STUB_getenv)
  SYSCALL_LOOKUP(putenv,                  putenv,                  1, STUB_putenv)
  SYSCALL_LOOKUP(setenv,                  setenv,                  3, STUB_setenv)
  SYSCALL_LOOKUP(unsetenv,                unsetenv,                1, STUB_unsetenv)
#endif

/* The following are defined only if networking AND sockets are supported */

#if defined(CONFIG_NET)
  SYSCALL_LOOKUP(psock_send,		 psock_send,		 4, STUB_psock_send)
  SYSCALL_LOOKUP(psock_close, 	 psock_close, 	 1, STUB_psock_close)
  SYSCALL_LOOKUP(psock_recvfrom, psock_recvfrom, 6, STUB_psock_recvfrom)
  SYSCALL_LOOKUP(sockfd_socket,  sockfd_socket,  1, STUB_sockfd_socket)
  SYSCALL_LOOKUP(net_clone,	 net_clone,	 2, STUB_net_clone)
  SYSCALL_LOOKUP(netdev_foreach, netdev_foreach, 2, STUB_netdev_foreach)
#  if CONFIG_NSOCKET_DESCRIPTORS > 0
    SYSCALL_LOOKUP(accept,                  accept,                  3, STUB_accept)
    SYSCALL_LOOKUP(bind,                    bind,                    3, STUB_bind)
    SYSCALL_LOOKUP(connect,                 connect,                 3, STUB_connect)
    SYSCALL_LOOKUP(getsockopt,              getsockopt,              5, STUB_getsockopt)
    SYSCALL_LOOKUP(listen,                  listen,                  2, STUB_listen)
    SYSCALL_LOOKUP(recv,                    recv,                    4, STUB_recv)
    SYSCALL_LOOKUP(recvfrom,                recvfrom,                6, STUB_recvfrom)
    SYSCALL_LOOKUP(send,                    send,                    4, STUB_send)
    SYSCALL_LOOKUP(sendto,                  sendto,                  6, STUB_sendto)
    SYSCALL_LOOKUP(setsockopt,              setsockopt,              5, STUB_setsockopt)
    SYSCALL_LOOKUP(socket,                  socket,                  3, STUB_socket)
#  endif
#endif

/* The following is defined only if CONFIG_TASK_NAME_SIZE > 0 */

#if CONFIG_TASK_NAME_SIZE > 0
  SYSCALL_LOOKUP(prctl,                   prctl,                   5, STUB_prctl)
#endif

#if defined(CONFIG_ARCH_LOWPUTC) || defined(CONFIG_SYSLOG)
  SYSCALL_LOOKUP(lowsyslog,			   lowsyslog,			   6, STUB_lowsyslog)
#endif

#if defined(CONFIG_HAVE_CXX) && defined(CONFIG_HAVE_CXXINITIALIZE)
  SYSCALL_LOOKUP(up_cxxinitialize,       up_cxxinitialize,       0, STUB_up_cxxinitialize)
#endif

#if defined(CONFIG_FS_WRITABLE)
SYSCALL_LOOKUP(ramdisk_register,	   ramdisk_register,	   5, STUB_ramdisk_register)
#else
SYSCALL_LOOKUP(romdisk_register,	   romdisk_register,	   4, STUB_romdisk_register)
#endif

#if defined(CONFIG_NET_ICMP) && defined(CONFIG_NET_ICMP_PING) && !defined(CONFIG_DISABLE_CLOCK) && !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(uip_ping,	   		   uip_ping,	   		   5, STUB_uip_ping)
#endif



/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/


