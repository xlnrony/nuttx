# 1 "proxies/PROXY__exit.c"
# 1 "/opt/nuttx-code/nuttx/syscall//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "proxies/PROXY__exit.c"


# 1 "/opt/nuttx-code/nuttx/include/nuttx/config.h" 1 3 4
# 4 "proxies/PROXY__exit.c" 2
# 1 "/opt/nuttx-code/nuttx/include/unistd.h" 1 3 4
# 43 "/opt/nuttx-code/nuttx/include/unistd.h" 3 4
# 1 "/opt/nuttx-code/nuttx/include/sys/types.h" 1 3 4
# 44 "/opt/nuttx-code/nuttx/include/sys/types.h" 3 4
# 1 "/opt/nuttx-code/nuttx/include/nuttx/compiler.h" 1 3 4
# 45 "/opt/nuttx-code/nuttx/include/sys/types.h" 2 3 4


# 1 "/opt/nuttx-code/nuttx/include/stdint.h" 1 3 4
# 49 "/opt/nuttx-code/nuttx/include/stdint.h" 3 4
# 1 "/opt/nuttx-code/nuttx/include/arch/types.h" 1 3 4
# 68 "/opt/nuttx-code/nuttx/include/arch/types.h" 3 4
typedef signed char _int8_t;
typedef unsigned char _uint8_t;

typedef signed short _int16_t;
typedef unsigned short _uint16_t;

typedef signed int _int32_t;
typedef unsigned int _uint32_t;

typedef signed long long _int64_t;
typedef unsigned long long _uint64_t;




typedef signed int _intptr_t;
typedef unsigned int _uintptr_t;
# 93 "/opt/nuttx-code/nuttx/include/arch/types.h" 3 4
typedef unsigned char irqstate_t;
# 50 "/opt/nuttx-code/nuttx/include/stdint.h" 2 3 4
# 1 "/opt/nuttx-code/nuttx/include/limits.h" 1 3 4
# 47 "/opt/nuttx-code/nuttx/include/limits.h" 3 4
# 1 "/opt/nuttx-code/nuttx/include/arch/limits.h" 1 3 4
# 48 "/opt/nuttx-code/nuttx/include/limits.h" 2 3 4
# 51 "/opt/nuttx-code/nuttx/include/stdint.h" 2 3 4
# 219 "/opt/nuttx-code/nuttx/include/stdint.h" 3 4
typedef _int8_t int8_t;
typedef _uint8_t uint8_t;

typedef _int16_t int16_t;
typedef _uint16_t uint16_t;






typedef _int32_t int32_t;
typedef _uint32_t uint32_t;


typedef _int64_t int64_t;
typedef _uint64_t uint64_t;




typedef _int8_t int_least8_t;
typedef _uint8_t uint_least8_t;

typedef _int16_t int_least16_t;
typedef _uint16_t uint_least16_t;





typedef _int32_t int_least24_t;
typedef _uint32_t uint_least24_t;


typedef _int32_t int_least32_t;
typedef _uint32_t uint_least32_t;


typedef _int64_t int_least64_t;
typedef _uint64_t uint_least64_t;




typedef _int8_t int_fast8_t;
typedef _uint8_t uint_fast8_t;

typedef int int_fast16_t;
typedef unsigned int uint_fast16_t;





typedef _int32_t int_fast24_t;
typedef _uint32_t uint_fast24_t;


typedef _int32_t int_fast32_t;
typedef _uint32_t uint_fast32_t;


typedef _int64_t int_fast64_t;
typedef _uint64_t uint_fast64_t;




typedef _intptr_t intptr_t;
typedef _uintptr_t uintptr_t;
# 303 "/opt/nuttx-code/nuttx/include/stdint.h" 3 4
typedef _int64_t intmax_t;
typedef _uint64_t uintmax_t;
# 48 "/opt/nuttx-code/nuttx/include/sys/types.h" 2 3 4
# 113 "/opt/nuttx-code/nuttx/include/sys/types.h" 3 4
typedef float float32;




typedef double double_t;
typedef double float64;
# 129 "/opt/nuttx-code/nuttx/include/sys/types.h" 3 4
typedef unsigned int mode_t;
# 145 "/opt/nuttx-code/nuttx/include/sys/types.h" 3 4
typedef uint32_t size_t;
typedef int32_t ssize_t;
typedef uint32_t rsize_t;







typedef int16_t uid_t;
typedef int16_t gid_t;



typedef uint16_t dev_t;



typedef uint16_t ino_t;





typedef int16_t pid_t;





typedef int16_t id_t;



typedef intptr_t ptrdiff_t;
# 190 "/opt/nuttx-code/nuttx/include/sys/types.h" 3 4
typedef uint16_t wchar_t;
# 202 "/opt/nuttx-code/nuttx/include/sys/types.h" 3 4
typedef uint32_t blkcnt_t;
typedef int32_t off_t;
typedef off_t fpos_t;




typedef int64_t off64_t;
typedef int64_t fpos64_t;




typedef int16_t blksize_t;



typedef unsigned int socklen_t;
typedef uint16_t sa_family_t;



typedef uint32_t clock_t;







typedef uint32_t useconds_t;
typedef int32_t suseconds_t;



typedef int (*main_t)(int argc, char *argv[]);
# 44 "/opt/nuttx-code/nuttx/include/unistd.h" 2 3 4
# 117 "/opt/nuttx-code/nuttx/include/unistd.h" 3 4
extern char *optarg;
extern int optind;
extern int optopt;
# 132 "/opt/nuttx-code/nuttx/include/unistd.h" 3 4
pid_t vfork(void);
pid_t getpid(void);
void _exit(int status) __attribute__ ((noreturn));
unsigned int sleep(unsigned int seconds);
int usleep(useconds_t usec);
int pause(void);



int close(int fd);
int dup(int fd);
int dup2(int fd1, int fd2);
int fsync(int fd);
off_t lseek(int fd, off_t offset, int whence);
ssize_t read(int fd, void *buf, size_t nbytes);
ssize_t write(int fd, const void *buf, size_t nbytes);



int pipe(int fd[2]);



int chdir( const char *path);
 char *getcwd( char *buf, size_t size);



int unlink( const char *pathname);
int rmdir( const char *pathname);




int execl( const char *path, ...);
int execv( const char *path, char *const argv[]);



struct symtab_s;
void exec_getsymtab( const struct symtab_s **symtab, int *nsymbols);
void exec_setsymtab( const struct symtab_s *symtab, int nsymbols);




int getopt(int argc, char *const argv[], const char *optstring);






 char **getoptargp(void);
int *getopindgp(void);
int *getoptoptp(void);
# 5 "proxies/PROXY__exit.c" 2
# 1 "/opt/nuttx-code/nuttx/include/syscall.h" 1 3 4
# 44 "/opt/nuttx-code/nuttx/include/syscall.h" 3 4
# 1 "/opt/nuttx-code/nuttx/include/sys/syscall.h" 1 3 4
# 72 "/opt/nuttx-code/nuttx/include/sys/syscall.h" 3 4
enum SYS_CALL_NO
{




# 1 "./syscall_lookup.h" 1 3 4
# 46 "./syscall_lookup.h" 3 4
SYS__exit = 8
, SYS_exit
, SYS_get_errno
, SYS_getpid
, SYS_sched_getparam
, SYS_sched_getscheduler
, SYS_sched_lock
, SYS_sched_lockcount
, SYS_sched_rr_get_interval
, SYS_sched_setparam
, SYS_sched_setscheduler
, SYS_sched_unlock
, SYS_sched_yield
, SYS_sem_close
, SYS_sem_destroy
, SYS_sem_open
, SYS_sem_post
, SYS_sem_timedwait
, SYS_sem_trywait
, SYS_sem_unlink
, SYS_sem_wait
, SYS_set_errno
, SYS_task_create
, SYS_task_delete
, SYS_task_restart
, SYS_up_assert

, SYS_register_driver
, SYS_unregister_driver
, SYS_sched_foreach




  , SYS_vfork
# 92 "./syscall_lookup.h" 3 4
  , SYS_waitpid
# 118 "./syscall_lookup.h" 3 4
  , SYS_kill
  , SYS_sigaction
  , SYS_sigpending
  , SYS_sigprocmask
  , SYS_sigqueue
  , SYS_sigsuspend
  , SYS_sigtimedwait
  , SYS_sigwaitinfo
  , SYS_nanosleep







  , SYS_syscall_clock_systimer
  , SYS_clock_getres
  , SYS_clock_gettime
  , SYS_clock_settime
  , SYS_gettimeofday





  , SYS_timer_create
  , SYS_timer_delete
  , SYS_timer_getoverrun
  , SYS_timer_gettime
  , SYS_timer_settime







  , SYS_close
  , SYS_ioctl
  , SYS_read
  , SYS_write

  , SYS_poll
  , SYS_select






  , SYS_closedir
  , SYS_dup
  , SYS_dup2
  , SYS_fcntl
  , SYS_lseek
  , SYS_mkfifo
  , SYS_mmap
  , SYS_open
  , SYS_opendir
  , SYS_pipe
  , SYS_readdir
  , SYS_rewinddir
  , SYS_seekdir
  , SYS_stat
  , SYS_statfs
  , SYS_telldir


  , SYS_fdopen
  , SYS_sched_getstreams







  , SYS_fsync
  , SYS_mkdir
  , SYS_mount
  , SYS_rename
  , SYS_rmdir
  , SYS_umount
  , SYS_unlink
  , SYS_losetup
  , SYS_loteardown
  , SYS_bchlib_teardown
  , SYS_bchlib_setup
  , SYS_bchlib_read
  , SYS_bchlib_write


       , SYS_mkfatfs







  , SYS_pthread_barrier_destroy
  , SYS_pthread_barrier_init
  , SYS_pthread_barrier_wait
  , SYS_pthread_cancel
  , SYS_pthread_cond_broadcast
  , SYS_pthread_cond_destroy
  , SYS_pthread_cond_init
  , SYS_pthread_cond_signal
  , SYS_pthread_cond_wait
  , SYS_pthread_create
  , SYS_pthread_detach
  , SYS_pthread_exit
  , SYS_pthread_getschedparam
  , SYS_pthread_getspecific
  , SYS_pthread_join
  , SYS_pthread_key_create
  , SYS_pthread_key_delete
  , SYS_pthread_mutex_destroy
  , SYS_pthread_mutex_init
  , SYS_pthread_mutex_lock
  , SYS_pthread_mutex_trylock
  , SYS_pthread_mutex_unlock
  , SYS_pthread_once
  , SYS_pthread_setcancelstate
  , SYS_pthread_setschedparam
  , SYS_pthread_setschedprio
  , SYS_pthread_setspecific
  , SYS_pthread_yield

  , SYS_pthread_cond_timedwait
  , SYS_pthread_kill
  , SYS_pthread_sigmask






  , SYS_mq_close
  , SYS_mq_notify
  , SYS_mq_open
  , SYS_mq_receive
  , SYS_mq_send
  , SYS_mq_timedreceive
  , SYS_mq_timedsend
  , SYS_mq_unlink





  , SYS_clearenv
  , SYS_getenv
  , SYS_putenv
  , SYS_setenv
  , SYS_unsetenv





  , SYS_psock_send
  , SYS_psock_close
  , SYS_psock_recvfrom
  , SYS_sockfd_socket
  , SYS_net_clone
  , SYS_netdev_foreach

    , SYS_accept
    , SYS_bind
    , SYS_connect
    , SYS_getsockopt
    , SYS_listen
    , SYS_recv
    , SYS_recvfrom
    , SYS_send
    , SYS_sendto
    , SYS_setsockopt
    , SYS_socket






  , SYS_prctl



  , SYS_lowsyslog



  , SYS_up_cxxinitialize



, SYS_ramdisk_register





, SYS_uip_ping
# 79 "/opt/nuttx-code/nuttx/include/sys/syscall.h" 2 3 4
, SYS_maxsyscall
};
# 131 "/opt/nuttx-code/nuttx/include/sys/syscall.h" 3 4
extern const uint8_t g_funcnparms[(SYS_maxsyscall-8)];
# 45 "/opt/nuttx-code/nuttx/include/syscall.h" 2 3 4
# 1 "/opt/nuttx-code/nuttx/include/arch/syscall.h" 1 3 4
# 52 "/opt/nuttx-code/nuttx/include/arch/syscall.h" 3 4
# 1 "/opt/nuttx-code/nuttx/include/arch/armv7-m/syscall.h" 1 3 4
# 85 "/opt/nuttx-code/nuttx/include/arch/armv7-m/syscall.h" 3 4
static inline uintptr_t sys_call0(unsigned int nbr)
{
  register long reg0 __asm__("r0") = (long)(nbr);

  __asm__ __volatile__
  (
    "svc %1"
    : "=r"(reg0)
    : "i"(0x00), "r"(reg0)
    : "memory"
  );

  return reg0;
}



static inline uintptr_t sys_call1(unsigned int nbr, uintptr_t parm1)
{
  register long reg0 __asm__("r0") = (long)(nbr);
  register long reg1 __asm__("r1") = (long)(parm1);

  __asm__ __volatile__
  (
    "svc %1"
    : "=r"(reg0)
    : "i"(0x00), "r"(reg0), "r"(reg1)
    : "memory"
  );

  return reg0;
}



static inline uintptr_t sys_call2(unsigned int nbr, uintptr_t parm1,
                                  uintptr_t parm2)
{
  register long reg0 __asm__("r0") = (long)(nbr);
  register long reg2 __asm__("r2") = (long)(parm2);
  register long reg1 __asm__("r1") = (long)(parm1);

  __asm__ __volatile__
  (
    "svc %1"
    : "=r"(reg0)
    : "i"(0x00), "r"(reg0), "r"(reg1), "r"(reg2)
    : "memory"
  );

  return reg0;
}



static inline uintptr_t sys_call3(unsigned int nbr, uintptr_t parm1,
                                  uintptr_t parm2, uintptr_t parm3)
{
  register long reg0 __asm__("r0") = (long)(nbr);
  register long reg3 __asm__("r3") = (long)(parm3);
  register long reg2 __asm__("r2") = (long)(parm2);
  register long reg1 __asm__("r1") = (long)(parm1);

  __asm__ __volatile__
  (
    "svc %1"
    : "=r"(reg0)
    : "i"(0x00), "r"(reg0), "r"(reg1), "r"(reg2), "r"(reg3)
    : "memory"
  );

  return reg0;
}






static inline uintptr_t sys_call4(unsigned int nbr, uintptr_t parm1,
                                  uintptr_t parm2, uintptr_t parm3,
                                  uintptr_t parm4)
{
  register long reg0 __asm__("r0") = (long)(nbr);
  register long reg4 __asm__("r4") = (long)(parm4);
  register long reg3 __asm__("r3") = (long)(parm3);
  register long reg2 __asm__("r2") = (long)(parm2);
  register long reg1 __asm__("r1") = (long)(parm1);

  __asm__ __volatile__
  (
    "svc %1"
    : "=r"(reg0)
    : "i"(0x00), "r"(reg0), "r"(reg1), "r"(reg2),
      "r"(reg3), "r"(reg4)
    : "memory"
  );

  return reg0;
}






static inline uintptr_t sys_call5(unsigned int nbr, uintptr_t parm1,
                                  uintptr_t parm2, uintptr_t parm3,
                                  uintptr_t parm4, uintptr_t parm5)
{
  register long reg0 __asm__("r0") = (long)(nbr);
  register long reg5 __asm__("r5") = (long)(parm5);
  register long reg4 __asm__("r4") = (long)(parm4);
  register long reg3 __asm__("r3") = (long)(parm3);
  register long reg2 __asm__("r2") = (long)(parm2);
  register long reg1 __asm__("r1") = (long)(parm1);

  __asm__ __volatile__
  (
    "svc %1"
    : "=r"(reg0)
    : "i"(0x00), "r"(reg0), "r"(reg1), "r"(reg2),
      "r"(reg3), "r"(reg4), "r"(reg5)
    : "memory"
  );

  return reg0;
}






static inline uintptr_t sys_call6(unsigned int nbr, uintptr_t parm1,
                                  uintptr_t parm2, uintptr_t parm3,
                                  uintptr_t parm4, uintptr_t parm5,
                                  uintptr_t parm6)
{
  register long reg0 __asm__("r0") = (long)(nbr);
  register long reg6 __asm__("r6") = (long)(parm6);
  register long reg5 __asm__("r5") = (long)(parm5);
  register long reg4 __asm__("r4") = (long)(parm4);
  register long reg3 __asm__("r3") = (long)(parm3);
  register long reg2 __asm__("r2") = (long)(parm2);
  register long reg1 __asm__("r1") = (long)(parm1);

  __asm__ __volatile__
  (
    "svc %1"
    : "=r"(reg0)
    : "i"(0x00), "r"(reg0), "r"(reg1), "r"(reg2),
      "r"(reg3), "r"(reg4), "r"(reg5), "r"(reg6)
    : "memory"
  );

  return reg0;
}
# 53 "/opt/nuttx-code/nuttx/include/arch/syscall.h" 2 3 4
# 46 "/opt/nuttx-code/nuttx/include/syscall.h" 2 3 4
# 6 "proxies/PROXY__exit.c" 2

void _exit(int parm1)
{
  (void)sys_call1((unsigned int)SYS__exit, (uintptr_t)parm1);
}
