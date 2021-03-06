/* Autogenerated syscall_lookup header file */

SYSCALL_LOOKUP1(_exit,	_exit,	1,	STUB__exit)
#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(accept,	accept,	3,	STUB_accept)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

#if defined(CONFIG_SCHED_ATEXIT)
SYSCALL_LOOKUP(atexit,	atexit,	1,	STUB_atexit)
#endif /* defined(CONFIG_SCHED_ATEXIT) */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(bchlib_read,	bchlib_read,	4,	STUB_bchlib_read)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(bchlib_setup,	bchlib_setup,	3,	STUB_bchlib_setup)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(bchlib_teardown,	bchlib_teardown,	1,	STUB_bchlib_teardown)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(bchlib_write,	bchlib_write,	4,	STUB_bchlib_write)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(bind,	bind,	3,	STUB_bind)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

#if defined(CONFIG_BUILTIN)
SYSCALL_LOOKUP(builtin_exec,	builtin_exec,	4,	STUB_builtin_exec)
#endif /* defined(CONFIG_BUILTIN) */

#if defined(CONFIG_BUILTIN)
SYSCALL_LOOKUP(builtin_for_index,	builtin_for_index,	1,	STUB_builtin_for_index)
#endif /* defined(CONFIG_BUILTIN) */

#if defined(CONFIG_BUILTIN)
SYSCALL_LOOKUP(builtin_getbuiltins,	builtin_getbuiltins,	2,	STUB_builtin_getbuiltins)
#endif /* defined(CONFIG_BUILTIN) */

#if defined(CONFIG_BUILTIN)
SYSCALL_LOOKUP(builtin_getname,	builtin_getname,	1,	STUB_builtin_getname)
#endif /* defined(CONFIG_BUILTIN) */

#if defined(CONFIG_BUILTIN) && defined(CONFIG_FS_BINFS)
SYSCALL_LOOKUP(builtin_initialize,	builtin_initialize,	0,	STUB_builtin_initialize)
#endif /* defined(CONFIG_BUILTIN) && defined(CONFIG_FS_BINFS) */

#if defined(CONFIG_BUILTIN)
SYSCALL_LOOKUP(builtin_isavail,	builtin_isavail,	1,	STUB_builtin_isavail)
#endif /* defined(CONFIG_BUILTIN) */

#if defined(CONFIG_BUILTIN)
SYSCALL_LOOKUP(builtin_setbuiltins,	builtin_setbuiltins,	2,	STUB_builtin_setbuiltins)
#endif /* defined(CONFIG_BUILTIN) */

#if defined(CONFIG_BUILTIN) && defined(CONFIG_FS_BINFS)
SYSCALL_LOOKUP(builtin_uninitialize,	builtin_uninitialize,	0,	STUB_builtin_uninitialize)
#endif /* defined(CONFIG_BUILTIN) && defined(CONFIG_FS_BINFS) */

#if !defined(CONFIG_DISABLE_ENVIRON)
SYSCALL_LOOKUP(clearenv,	clearenv,	0,	STUB_clearenv)
#endif /* !defined(CONFIG_DISABLE_ENVIRON) */

SYSCALL_LOOKUP(clock_getres,	clock_getres,	2,	STUB_clock_getres)
SYSCALL_LOOKUP(clock_gettime,	clock_gettime,	2,	STUB_clock_gettime)
SYSCALL_LOOKUP(clock_settime,	clock_settime,	2,	STUB_clock_settime)
SYSCALL_LOOKUP(clock_systimer,	clock_systimer,	0,	STUB_clock_systimer)
#if CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(close,	close,	1,	STUB_close)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(closedir,	closedir,	1,	STUB_closedir)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(connect,	connect,	3,	STUB_connect)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(dup,	dup,	1,	STUB_dup)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(dup2,	dup2,	2,	STUB_dup2)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_ELF)
SYSCALL_LOOKUP(elf_initialize,	elf_initialize,	0,	STUB_elf_initialize)
#endif /* !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_ELF) */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_ELF)
SYSCALL_LOOKUP(elf_uninitialize,	elf_uninitialize,	0,	STUB_elf_uninitialize)
#endif /* !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_ELF) */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS)
SYSCALL_LOOKUP(exec_getsymtab,	exec_getsymtab,	2,	STUB_exec_getsymtab)
#endif /* !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS) */

#if !defined(CONFIG_BINFMT_DISABLE)
SYSCALL_LOOKUP(exec_module,	exec_module,	1,	STUB_exec_module)
#endif /* !defined(CONFIG_BINFMT_DISABLE) */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS)
SYSCALL_LOOKUP(exec_setsymtab,	exec_setsymtab,	2,	STUB_exec_setsymtab)
#endif /* !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS) */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS)
SYSCALL_LOOKUP(execl,	execl,	2,	STUB_execl)
#endif /* !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS) */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS)
SYSCALL_LOOKUP(execv,	execv,	2,	STUB_execv)
#endif /* !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS) */

SYSCALL_LOOKUP(exit,	exit,	1,	STUB_exit)
#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(fcntl,	fcntl,	3,	STUB_fcntl)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0 && CONFIG_NFILE_STREAMS > 0
SYSCALL_LOOKUP(fs_fdopen,	fs_fdopen,	3,	STUB_fs_fdopen)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && CONFIG_NFILE_STREAMS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(fsync,	fsync,	1,	STUB_fsync)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

SYSCALL_LOOKUP(get_errno,	get_errno,	0,	STUB_get_errno)
#if !defined(CONFIG_DISABLE_ENVIRON)
SYSCALL_LOOKUP(getenv,	getenv,	1,	STUB_getenv)
#endif /* !defined(CONFIG_DISABLE_ENVIRON) */

SYSCALL_LOOKUP(getpid,	getpid,	0,	STUB_getpid)
#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(getsockopt,	getsockopt,	5,	STUB_getsockopt)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

SYSCALL_LOOKUP(gettimeofday,	gettimeofday,	2,	STUB_gettimeofday)
#if defined(CONFIG_NET_ICMP) && defined(CONFIG_NET_ICMP_PING) && !defined(CONFIG_DISABLE_CLOCK) && !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(icmp_ping,	icmp_ping,	5,	STUB_icmp_ping)
#endif /* defined(CONFIG_NET_ICMP) && defined(CONFIG_NET_ICMP_PING) && !defined(CONFIG_DISABLE_CLOCK) && !defined(CONFIG_DISABLE_SIGNALS) */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(ioctl,	ioctl,	3,	STUB_ioctl)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0 */

#if !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(kill,	kill,	2,	STUB_kill)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(listen,	listen,	2,	STUB_listen)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

#if !defined(CONFIG_BINFMT_DISABLE)
SYSCALL_LOOKUP(load_module,	load_module,	1,	STUB_load_module)
#endif /* !defined(CONFIG_BINFMT_DISABLE) */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(losetup,	losetup,	5,	STUB_losetup)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(loteardown,	loteardown,	1,	STUB_loteardown)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if defined(CONFIG_ARCH_LOWPUTC) || defined(CONFIG_SYSLOG)
SYSCALL_LOOKUP(lowsyslog,	lowsyslog,	2,	STUB_lowsyslog)
#endif /* defined(CONFIG_ARCH_LOWPUTC) || defined(CONFIG_SYSLOG) */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(lseek,	lseek,	3,	STUB_lseek)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(mkdir,	mkdir,	2,	STUB_mkdir)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if !defined(CONFIG_DISABLE_MOUNTPOINT) && CONFIG_NFILE_DESCRIPTORS > 0 && defined(CONFIG_FS_FAT)
SYSCALL_LOOKUP(mkfatfs,	mkfatfs,	2,	STUB_mkfatfs)
#endif /* !defined(CONFIG_DISABLE_MOUNTPOINT) && CONFIG_NFILE_DESCRIPTORS > 0 && defined(CONFIG_FS_FAT) */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(mkfifo,	mkfifo,	2,	STUB_mkfifo)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(mmap,	mmap,	6,	STUB_mmap)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if defined (CONFIG_MMCSD) && defined (CONFIG_MMCSD_SDIO)
SYSCALL_LOOKUP(mmcsd_slotinitialize,	mmcsd_slotinitialize,	2,	STUB_mmcsd_slotinitialize)
#endif /* defined (CONFIG_MMCSD) && defined (CONFIG_MMCSD_SDIO) */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) && defined(CONFIG_FS_READABLE)
SYSCALL_LOOKUP(mount,	mount,	5,	STUB_mount)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) && defined(CONFIG_FS_READABLE) */

#if !defined(CONFIG_DISABLE_MQUEUE)
SYSCALL_LOOKUP(mq_close,	mq_close,	1,	STUB_mq_close)
#endif /* !defined(CONFIG_DISABLE_MQUEUE) */

#if !defined(CONFIG_DISABLE_SIGNALS) && !defined(CONFIG_DISABLE_MQUEUE)
SYSCALL_LOOKUP(mq_notify,	mq_notify,	2,	STUB_mq_notify)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) && !defined(CONFIG_DISABLE_MQUEUE) */

#if !defined(CONFIG_DISABLE_MQUEUE)
SYSCALL_LOOKUP(mq_open,	mq_open,	3,	STUB_mq_open)
#endif /* !defined(CONFIG_DISABLE_MQUEUE) */

#if !defined(CONFIG_DISABLE_MQUEUE)
SYSCALL_LOOKUP(mq_receive,	mq_receive,	4,	STUB_mq_receive)
#endif /* !defined(CONFIG_DISABLE_MQUEUE) */

#if !defined(CONFIG_DISABLE_MQUEUE)
SYSCALL_LOOKUP(mq_send,	mq_send,	4,	STUB_mq_send)
#endif /* !defined(CONFIG_DISABLE_MQUEUE) */

#if !defined(CONFIG_DISABLE_MQUEUE)
SYSCALL_LOOKUP(mq_timedreceive,	mq_timedreceive,	5,	STUB_mq_timedreceive)
#endif /* !defined(CONFIG_DISABLE_MQUEUE) */

#if !defined(CONFIG_DISABLE_MQUEUE)
SYSCALL_LOOKUP(mq_timedsend,	mq_timedsend,	5,	STUB_mq_timedsend)
#endif /* !defined(CONFIG_DISABLE_MQUEUE) */

#if !defined(CONFIG_DISABLE_MQUEUE)
SYSCALL_LOOKUP(mq_unlink,	mq_unlink,	1,	STUB_mq_unlink)
#endif /* !defined(CONFIG_DISABLE_MQUEUE) */

#if !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(nanosleep,	nanosleep,	2,	STUB_nanosleep)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) */

#if defined(CONFIG_NET) && defined(CONFIG_NET_TCP)
SYSCALL_LOOKUP(net_clone,	net_clone,	2,	STUB_net_clone)
#endif /* defined(CONFIG_NET) && defined(CONFIG_NET_TCP) */

#if defined(CONFIG_NET) && defined(CONFIG_NET_TCP)
SYSCALL_LOOKUP(netdev_foreach,	netdev_foreach,	2,	STUB_netdev_foreach)
#endif /* defined(CONFIG_NET) && defined(CONFIG_NET_TCP) */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_NXFLAT)
SYSCALL_LOOKUP(nxflat_initialize,	nxflat_initialize,	0,	STUB_nxflat_initialize)
#endif /* !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_NXFLAT) */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_NXFLAT)
SYSCALL_LOOKUP(nxflat_uninitialize,	nxflat_uninitialize,	0,	STUB_nxflat_uninitialize)
#endif /* !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_NXFLAT) */

#if defined(CONFIG_SCHED_ONEXIT)
SYSCALL_LOOKUP(on_exit,	on_exit,	2,	STUB_on_exit)
#endif /* defined(CONFIG_SCHED_ONEXIT) */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(open,	open,	3,	STUB_open)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(opendir,	opendir,	1,	STUB_opendir)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(pipe,	pipe,	1,	STUB_pipe)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if !defined(CONFIG_DISABLE_POLL) && (CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0)
SYSCALL_LOOKUP(poll,	poll,	3,	STUB_poll)
#endif /* !defined(CONFIG_DISABLE_POLL) && (CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0) */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS) && !defined(CONFIG_BINFMT_EXEPATH)
SYSCALL_LOOKUP(posix_spawn,	posix_spawn,	6,	STUB_posix_spawn)
#endif /* !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS) && !defined(CONFIG_BINFMT_EXEPATH) */

#if !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS) && defined(CONFIG_BINFMT_EXEPATH)
SYSCALL_LOOKUP(posix_spawnp,	posix_spawnp,	6,	STUB_posix_spawnp)
#endif /* !defined(CONFIG_BINFMT_DISABLE) && defined(CONFIG_LIBC_EXECFUNCS) && defined(CONFIG_BINFMT_EXEPATH) */

#if CONFIG_TASK_NAME_SIZE > 0
SYSCALL_LOOKUP(prctl,	prctl,	2,	STUB_prctl)
#endif /* CONFIG_TASK_NAME_SIZE > 0 */

#if defined(CONFIG_NET) && defined(CONFIG_NET_TCP)
SYSCALL_LOOKUP(psock_close,	psock_close,	1,	STUB_psock_close)
#endif /* defined(CONFIG_NET) && defined(CONFIG_NET_TCP) */

#if defined(CONFIG_NET) && defined(CONFIG_NET_TCP)
SYSCALL_LOOKUP(psock_recvfrom,	psock_recvfrom,	6,	STUB_psock_recvfrom)
#endif /* defined(CONFIG_NET) && defined(CONFIG_NET_TCP) */

#if defined(CONFIG_NET) && defined(CONFIG_NET_TCP)
SYSCALL_LOOKUP(psock_send,	psock_send,	4,	STUB_psock_send)
#endif /* defined(CONFIG_NET) && defined(CONFIG_NET_TCP) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_barrier_destroy,	pthread_barrier_destroy,	1,	STUB_pthread_barrier_destroy)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_barrier_init,	pthread_barrier_init,	3,	STUB_pthread_barrier_init)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_barrier_wait,	pthread_barrier_wait,	1,	STUB_pthread_barrier_wait)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_cancel,	pthread_cancel,	1,	STUB_pthread_cancel)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_cond_broadcast,	pthread_cond_broadcast,	1,	STUB_pthread_cond_broadcast)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_cond_destroy,	pthread_cond_destroy,	1,	STUB_pthread_cond_destroy)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_cond_init,	pthread_cond_init,	2,	STUB_pthread_cond_init)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_cond_signal,	pthread_cond_signal,	1,	STUB_pthread_cond_signal)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_SIGNALS) && !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_cond_timedwait,	pthread_cond_timedwait,	3,	STUB_pthread_cond_timedwait)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) && !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_cond_wait,	pthread_cond_wait,	2,	STUB_pthread_cond_wait)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_create,	pthread_create,	4,	STUB_pthread_create)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_detach,	pthread_detach,	1,	STUB_pthread_detach)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_exit,	pthread_exit,	1,	STUB_pthread_exit)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_getschedparam,	pthread_getschedparam,	3,	STUB_pthread_getschedparam)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_getspecific,	pthread_getspecific,	1,	STUB_pthread_getspecific)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_join,	pthread_join,	2,	STUB_pthread_join)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_key_create,	pthread_key_create,	2,	STUB_pthread_key_create)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_key_delete,	pthread_key_delete,	1,	STUB_pthread_key_delete)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_SIGNALS) && !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_kill,	pthread_kill,	2,	STUB_pthread_kill)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) && !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_mutex_destroy,	pthread_mutex_destroy,	1,	STUB_pthread_mutex_destroy)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_mutex_init,	pthread_mutex_init,	2,	STUB_pthread_mutex_init)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_mutex_lock,	pthread_mutex_lock,	1,	STUB_pthread_mutex_lock)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_mutex_trylock,	pthread_mutex_trylock,	1,	STUB_pthread_mutex_trylock)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_mutex_unlock,	pthread_mutex_unlock,	1,	STUB_pthread_mutex_unlock)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_once,	pthread_once,	2,	STUB_pthread_once)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_setcancelstate,	pthread_setcancelstate,	2,	STUB_pthread_setcancelstate)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_setschedparam,	pthread_setschedparam,	3,	STUB_pthread_setschedparam)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_setschedprio,	pthread_setschedprio,	2,	STUB_pthread_setschedprio)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_setspecific,	pthread_setspecific,	2,	STUB_pthread_setspecific)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_SIGNALS) && !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_sigmask,	pthread_sigmask,	3,	STUB_pthread_sigmask)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) && !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_PTHREAD)
SYSCALL_LOOKUP(pthread_yield,	pthread_yield,	0,	STUB_pthread_yield)
#endif /* !defined(CONFIG_DISABLE_PTHREAD) */

#if !defined(CONFIG_DISABLE_ENVIRON)
SYSCALL_LOOKUP(putenv,	putenv,	1,	STUB_putenv)
#endif /* !defined(CONFIG_DISABLE_ENVIRON) */

#if defined(CONFIG_FS_WRITABLE)
SYSCALL_LOOKUP(ramdisk_register,	ramdisk_register,	5,	STUB_ramdisk_register)
#endif /* defined(CONFIG_FS_WRITABLE) */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(read,	read,	3,	STUB_read)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(readdir,	readdir,	1,	STUB_readdir)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(recv,	recv,	4,	STUB_recv)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(recvfrom,	recvfrom,	6,	STUB_recvfrom)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

SYSCALL_LOOKUP(register_driver,	register_driver,	4,	STUB_register_driver)
#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(rename,	rename,	2,	STUB_rename)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(rewinddir,	rewinddir,	1,	STUB_rewinddir)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(rmdir,	rmdir,	1,	STUB_rmdir)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if !defined(CONFIG_FS_WRITABLE)
SYSCALL_LOOKUP(romdisk_register,	romdisk_register,	4,	STUB_romdisk_register)
#endif /* !defined(CONFIG_FS_WRITABLE) */

SYSCALL_LOOKUP(sched_foreach,	sched_foreach,	2,	STUB_sched_foreach)
SYSCALL_LOOKUP(sched_getparam,	sched_getparam,	2,	STUB_sched_getparam)
SYSCALL_LOOKUP(sched_getscheduler,	sched_getscheduler,	1,	STUB_sched_getscheduler)
#if CONFIG_NFILE_DESCRIPTORS > 0 && CONFIG_NFILE_STREAMS > 0
SYSCALL_LOOKUP(sched_getstreams,	sched_getstreams,	0,	STUB_sched_getstreams)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && CONFIG_NFILE_STREAMS > 0 */

SYSCALL_LOOKUP(sched_lock,	sched_lock,	0,	STUB_sched_lock)
SYSCALL_LOOKUP(sched_lockcount,	sched_lockcount,	0,	STUB_sched_lockcount)
SYSCALL_LOOKUP(sched_rr_get_interval,	sched_rr_get_interval,	2,	STUB_sched_rr_get_interval)
SYSCALL_LOOKUP(sched_setparam,	sched_setparam,	2,	STUB_sched_setparam)
SYSCALL_LOOKUP(sched_setscheduler,	sched_setscheduler,	3,	STUB_sched_setscheduler)
SYSCALL_LOOKUP(sched_unlock,	sched_unlock,	0,	STUB_sched_unlock)
SYSCALL_LOOKUP(sched_yield,	sched_yield,	0,	STUB_sched_yield)
#if defined (CONFIG_MMCSD) && defined (CONFIG_MMCSD_SDIO)
SYSCALL_LOOKUP(sdio_initialize,	sdio_initialize,	1,	STUB_sdio_initialize)
#endif /* defined (CONFIG_MMCSD) && defined (CONFIG_MMCSD_SDIO) */

#if defined (CONFIG_MMCSD) && defined (CONFIG_MMCSD_SDIO)
SYSCALL_LOOKUP(sdio_mediachange,	sdio_mediachange,	2,	STUB_sdio_mediachange)
#endif /* defined (CONFIG_MMCSD) && defined (CONFIG_MMCSD_SDIO) */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(seekdir,	seekdir,	2,	STUB_seekdir)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if !defined(CONFIG_DISABLE_POLL) && (CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0)
SYSCALL_LOOKUP(select,	select,	5,	STUB_select)
#endif /* !defined(CONFIG_DISABLE_POLL) && (CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0) */

SYSCALL_LOOKUP(sem_close,	sem_close,	1,	STUB_sem_close)
SYSCALL_LOOKUP(sem_destroy,	sem_destroy,	1,	STUB_sem_destroy)
SYSCALL_LOOKUP(sem_open,	sem_open,	3,	STUB_sem_open)
SYSCALL_LOOKUP(sem_post,	sem_post,	1,	STUB_sem_post)
SYSCALL_LOOKUP(sem_timedwait,	sem_timedwait,	2,	STUB_sem_timedwait)
SYSCALL_LOOKUP(sem_trywait,	sem_trywait,	1,	STUB_sem_trywait)
SYSCALL_LOOKUP(sem_unlink,	sem_unlink,	1,	STUB_sem_unlink)
SYSCALL_LOOKUP(sem_wait,	sem_wait,	1,	STUB_sem_wait)
#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(send,	send,	4,	STUB_send)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

#if CONFIG_NFILE_DESCRIPTORS > 0 && defined(CONFIG_NET_SENDFILE)
SYSCALL_LOOKUP(sendfile,	sendfile,	4,	STUB_sendfile)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && defined(CONFIG_NET_SENDFILE) */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(sendto,	sendto,	6,	STUB_sendto)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

SYSCALL_LOOKUP(set_errno,	set_errno,	1,	STUB_set_errno)
#if !defined(CONFIG_DISABLE_ENVIRON)
SYSCALL_LOOKUP(setenv,	setenv,	3,	STUB_setenv)
#endif /* !defined(CONFIG_DISABLE_ENVIRON) */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(setsockopt,	setsockopt,	5,	STUB_setsockopt)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

#if !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(sigaction,	sigaction,	3,	STUB_sigaction)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) */

#if !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(sigpending,	sigpending,	1,	STUB_sigpending)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) */

#if !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(sigprocmask,	sigprocmask,	3,	STUB_sigprocmask)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) */

#if !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(sigqueue,	sigqueue,	3,	STUB_sigqueue)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) */

#if !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(sigsuspend,	sigsuspend,	1,	STUB_sigsuspend)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) */

#if !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(sigtimedwait,	sigtimedwait,	3,	STUB_sigtimedwait)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) */

#if !defined(CONFIG_DISABLE_SIGNALS)
SYSCALL_LOOKUP(sigwaitinfo,	sigwaitinfo,	2,	STUB_sigwaitinfo)
#endif /* !defined(CONFIG_DISABLE_SIGNALS) */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET)
SYSCALL_LOOKUP(socket,	socket,	3,	STUB_socket)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 && defined(CONFIG_NET) */

#if defined(CONFIG_NET) && defined(CONFIG_NET_TCP)
SYSCALL_LOOKUP(sockfd_socket,	sockfd_socket,	1,	STUB_sockfd_socket)
#endif /* defined(CONFIG_NET) && defined(CONFIG_NET_TCP) */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(stat,	stat,	2,	STUB_stat)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(statfs,	statfs,	2,	STUB_statfs)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if defined(CONFIG_SYSLOG_ENABLE)
SYSCALL_LOOKUP(syslog_enable,	syslog_enable,	1,	STUB_syslog_enable)
#endif /* defined(CONFIG_SYSLOG_ENABLE) */

SYSCALL_LOOKUP(task_create,	task_create,	5,	STUB_task_create)
SYSCALL_LOOKUP(task_delete,	task_delete,	1,	STUB_task_delete)
SYSCALL_LOOKUP(task_restart,	task_restart,	1,	STUB_task_restart)
SYSCALL_LOOKUP(task_spawn,	task_spawn,	7,	STUB_task_spawn)
#if CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(telldir,	telldir,	1,	STUB_telldir)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 */

#if !defined(CONFIG_DISABLE_POSIX_TIMERS)
SYSCALL_LOOKUP(timer_create,	timer_create,	3,	STUB_timer_create)
#endif /* !defined(CONFIG_DISABLE_POSIX_TIMERS) */

#if !defined(CONFIG_DISABLE_POSIX_TIMERS)
SYSCALL_LOOKUP(timer_delete,	timer_delete,	1,	STUB_timer_delete)
#endif /* !defined(CONFIG_DISABLE_POSIX_TIMERS) */

#if !defined(CONFIG_DISABLE_POSIX_TIMERS)
SYSCALL_LOOKUP(timer_getoverrun,	timer_getoverrun,	1,	STUB_timer_getoverrun)
#endif /* !defined(CONFIG_DISABLE_POSIX_TIMERS) */

#if !defined(CONFIG_DISABLE_POSIX_TIMERS)
SYSCALL_LOOKUP(timer_gettime,	timer_gettime,	2,	STUB_timer_gettime)
#endif /* !defined(CONFIG_DISABLE_POSIX_TIMERS) */

#if !defined(CONFIG_DISABLE_POSIX_TIMERS)
SYSCALL_LOOKUP(timer_settime,	timer_settime,	4,	STUB_timer_settime)
#endif /* !defined(CONFIG_DISABLE_POSIX_TIMERS) */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(umount,	umount,	1,	STUB_umount)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT)
SYSCALL_LOOKUP(unlink,	unlink,	1,	STUB_unlink)
#endif /* CONFIG_NFILE_DESCRIPTORS > 0 && !defined(CONFIG_DISABLE_MOUNTPOINT) */

#if !defined(CONFIG_BINFMT_DISABLE)
SYSCALL_LOOKUP(unload_module,	unload_module,	1,	STUB_unload_module)
#endif /* !defined(CONFIG_BINFMT_DISABLE) */

SYSCALL_LOOKUP(unregister_driver,	unregister_driver,	1,	STUB_unregister_driver)
#if !defined(CONFIG_DISABLE_ENVIRON)
SYSCALL_LOOKUP(unsetenv,	unsetenv,	1,	STUB_unsetenv)
#endif /* !defined(CONFIG_DISABLE_ENVIRON) */

SYSCALL_LOOKUP(up_assert,	up_assert,	2,	STUB_up_assert)
#if defined(CONFIG_DEBUG) && defined(CONFIG_DEBUG_STACK)
SYSCALL_LOOKUP(up_check_tcbstack,	up_check_tcbstack,	1,	STUB_up_check_tcbstack)
#endif /* defined(CONFIG_DEBUG) && defined(CONFIG_DEBUG_STACK) */

#if defined(CONFIG_HAVE_CXX) && defined(CONFIG_HAVE_CXXINITIALIZE)
SYSCALL_LOOKUP(up_cxxinitialize,	up_cxxinitialize,	0,	STUB_up_cxxinitialize)
#endif /* defined(CONFIG_HAVE_CXX) && defined(CONFIG_HAVE_CXXINITIALIZE) */

SYSCALL_LOOKUP(up_progmem_erasepage,	up_progmem_erasepage,	1,	STUB_up_progmem_erasepage)
SYSCALL_LOOKUP(up_progmem_getaddr,	up_progmem_getaddr,	1,	STUB_up_progmem_getaddr)
SYSCALL_LOOKUP(up_progmem_getpage,	up_progmem_getpage,	1,	STUB_up_progmem_getpage)
SYSCALL_LOOKUP(up_progmem_ispageerased,	up_progmem_ispageerased,	1,	STUB_up_progmem_ispageerased)
SYSCALL_LOOKUP(up_progmem_isuniform,	up_progmem_isuniform,	0,	STUB_up_progmem_isuniform)
SYSCALL_LOOKUP(up_progmem_pagesize,	up_progmem_pagesize,	1,	STUB_up_progmem_pagesize)
SYSCALL_LOOKUP(up_progmem_write,	up_progmem_write,	3,	STUB_up_progmem_write)
#if defined(CONFIG_USBHOST)
SYSCALL_LOOKUP(usbhost_connection_enumerate,	usbhost_connection_enumerate,	2,	STUB_usbhost_connection_enumerate)
#endif /* defined(CONFIG_USBHOST) */

#if defined(CONFIG_USBHOST)
SYSCALL_LOOKUP(usbhost_connection_wait,	usbhost_connection_wait,	2,	STUB_usbhost_connection_wait)
#endif /* defined(CONFIG_USBHOST) */

#if defined(CONFIG_USBHOST) && defined(CONFIG_USBHOST_EPASS3003)
SYSCALL_LOOKUP(usbhost_epass3003init,	usbhost_epass3003init,	0,	STUB_usbhost_epass3003init)
#endif /* defined(CONFIG_USBHOST) && defined(CONFIG_USBHOST_EPASS3003) */

#if defined(CONFIG_USBHOST)
SYSCALL_LOOKUP(usbhost_initialize,	usbhost_initialize,	1,	STUB_usbhost_initialize)
#endif /* defined(CONFIG_USBHOST) */

#if defined(CONFIG_USBHOST) && defined(CONFIG_USBHOST_HIDKBD)
SYSCALL_LOOKUP(usbhost_kbdinit,	usbhost_kbdinit,	0,	STUB_usbhost_kbdinit)
#endif /* defined(CONFIG_USBHOST) && defined(CONFIG_USBHOST_HIDKBD) */

#if defined(CONFIG_USBHOST_TRACE)
SYSCALL_LOOKUP(usbhost_trdump,	usbhost_trdump,	0,	STUB_usbhost_trdump)
#endif /* defined(CONFIG_USBHOST_TRACE) */

#if defined(CONFIG_ARCH_HAVE_VFORK)
SYSCALL_LOOKUP(vfork,	vfork,	0,	STUB_vfork)
#endif /* defined(CONFIG_ARCH_HAVE_VFORK) */

#if defined(CONFIG_SCHED_WAITPID) && defined(CONFIG_SCHED_HAVE_PARENT)
SYSCALL_LOOKUP(wait,	wait,	1,	STUB_wait)
#endif /* defined(CONFIG_SCHED_WAITPID) && defined(CONFIG_SCHED_HAVE_PARENT) */

#if defined(CONFIG_SCHED_WAITPID) && defined(CONFIG_SCHED_HAVE_PARENT)
SYSCALL_LOOKUP(waitid,	waitid,	4,	STUB_waitid)
#endif /* defined(CONFIG_SCHED_WAITPID) && defined(CONFIG_SCHED_HAVE_PARENT) */

#if defined(CONFIG_SCHED_WAITPID)
SYSCALL_LOOKUP(waitpid,	waitpid,	3,	STUB_waitpid)
#endif /* defined(CONFIG_SCHED_WAITPID) */

#if CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0
SYSCALL_LOOKUP(write,	write,	3,	STUB_write)
#endif /* CONFIG_NSOCKET_DESCRIPTORS > 0 || CONFIG_NFILE_DESCRIPTORS > 0 */

