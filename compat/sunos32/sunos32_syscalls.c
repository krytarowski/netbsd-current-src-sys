/* $NetBSD: sunos32_syscalls.c,v 1.27 2013/11/07 19:39:58 njoly Exp $ */

/*
 * System call names.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from;	NetBSD: syscalls.master,v 1.22 2013/11/07 19:37:19 njoly Exp
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: sunos32_syscalls.c,v 1.27 2013/11/07 19:39:58 njoly Exp $");

#if defined(_KERNEL_OPT)
#if defined(_KERNEL_OPT)
#include "opt_sysv.h"
#include "opt_compat_sunos.h"
#endif
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/signal.h>
#include <sys/mount.h>
#include <sys/poll.h>
#include <sys/syscallargs.h>
#include <compat/sunos/sunos.h>
#include <compat/sunos/sunos_syscallargs.h>
#include <compat/netbsd32/netbsd32.h>
#include <compat/netbsd32/netbsd32_syscallargs.h>
#include <compat/sunos32/sunos32.h>
#include <compat/sunos32/sunos32_syscallargs.h>
#endif /* _KERNEL_OPT */

const char *const sunos32_syscallnames[] = {
	/*   0 */	"syscall",
	/*   1 */	"netbsd32_exit",
	/*   2 */	"fork",
	/*   3 */	"netbsd32_read",
	/*   4 */	"netbsd32_write",
	/*   5 */	"open",
	/*   6 */	"netbsd32_close",
	/*   7 */	"wait4",
	/*   8 */	"creat",
	/*   9 */	"netbsd32_link",
	/*  10 */	"netbsd32_unlink",
	/*  11 */	"execv",
	/*  12 */	"netbsd32_chdir",
	/*  13 */	"#13 (obsolete old_time)",
	/*  14 */	"mknod",
	/*  15 */	"netbsd32_chmod",
	/*  16 */	"netbsd32_chown",
	/*  17 */	"netbsd32_break",
	/*  18 */	"#18 (obsolete old_stat)",
	/*  19 */	"compat_43_netbsd32_olseek",
	/*  20 */	"getpid_with_ppid",
	/*  21 */	"#21 (obsolete sunos_old_mount)",
	/*  22 */	"#22 (unimplemented System V umount)",
	/*  23 */	"netbsd32_setuid",
	/*  24 */	"getuid_with_euid",
	/*  25 */	"stime",
	/*  26 */	"ptrace",
	/*  27 */	"#27 (unimplemented old_sunos_alarm)",
	/*  28 */	"#28 (unimplemented old_sunos_fstat)",
	/*  29 */	"#29 (unimplemented old_sunos_pause)",
	/*  30 */	"#30 (unimplemented old_sunos_utime)",
	/*  31 */	"#31 (unimplemented old_sunos_stty)",
	/*  32 */	"#32 (unimplemented old_sunos_gtty)",
	/*  33 */	"access",
	/*  34 */	"#34 (unimplemented old_sunos_nice)",
	/*  35 */	"#35 (unimplemented old_sunos_ftime)",
	/*  36 */	"sync",
	/*  37 */	"netbsd32_kill",
	/*  38 */	"stat",
	/*  39 */	"#39 (unimplemented sunos_setpgrp)",
	/*  40 */	"lstat",
	/*  41 */	"netbsd32_dup",
	/*  42 */	"pipe",
	/*  43 */	"#43 (unimplemented sunos_times)",
	/*  44 */	"netbsd32_profil",
	/*  45 */	"#45 (unimplemented)",
	/*  46 */	"netbsd32_setgid",
	/*  47 */	"getgid_with_egid",
	/*  48 */	"#48 (unimplemented sunos_ssig)",
	/*  49 */	"#49 (unimplemented reserved for USG)",
	/*  50 */	"#50 (unimplemented reserved for USG)",
	/*  51 */	"netbsd32_acct",
	/*  52 */	"#52 (unimplemented)",
	/*  53 */	"mctl",
	/*  54 */	"ioctl",
	/*  55 */	"reboot",
	/*  56 */	"#56 (obsolete sunos_owait3)",
	/*  57 */	"netbsd32_symlink",
	/*  58 */	"netbsd32_readlink",
	/*  59 */	"execve",
	/*  60 */	"netbsd32_umask",
	/*  61 */	"netbsd32_chroot",
	/*  62 */	"compat_43_netbsd32_fstat43",
	/*  63 */	"#63 (unimplemented)",
	/*  64 */	"ogetpagesize",
	/*  65 */	"omsync",
	/*  66 */	"vfork",
	/*  67 */	"#67 (obsolete vread)",
	/*  68 */	"#68 (obsolete vwrite)",
	/*  69 */	"netbsd32_sbrk",
	/*  70 */	"netbsd32_sstk",
	/*  71 */	"mmap",
	/*  72 */	"vadvise",
	/*  73 */	"netbsd32_munmap",
	/*  74 */	"netbsd32_mprotect",
	/*  75 */	"netbsd32_madvise",
	/*  76 */	"vhangup",
	/*  77 */	"#77 (unimplemented vlimit)",
	/*  78 */	"netbsd32_mincore",
	/*  79 */	"netbsd32_getgroups",
	/*  80 */	"netbsd32_setgroups",
	/*  81 */	"getpgrp",
	/*  82 */	"setpgrp",
	/*  83 */	"compat_50_netbsd32_setitimer",
	/*  84 */	"#84 (unimplemented sunos32_sys_wait)",
	/*  85 */	"compat_12_netbsd32_oswapon",
	/*  86 */	"compat_50_netbsd32_getitimer",
	/*  87 */	"compat_43_netbsd32_ogethostname",
	/*  88 */	"compat_43_netbsd32_osethostname",
	/*  89 */	"ogetdtablesize",
	/*  90 */	"netbsd32_dup2",
	/*  91 */	"#91 (unimplemented getdopt)",
	/*  92 */	"fcntl",
	/*  93 */	"compat_50_netbsd32_select",
	/*  94 */	"#94 (unimplemented setdopt)",
	/*  95 */	"netbsd32_fsync",
	/*  96 */	"netbsd32_setpriority",
	/*  97 */	"socket",
	/*  98 */	"netbsd32_connect",
	/*  99 */	"compat_43_netbsd32_oaccept",
	/* 100 */	"netbsd32_getpriority",
	/* 101 */	"compat_43_netbsd32_osend",
	/* 102 */	"compat_43_netbsd32_orecv",
	/* 103 */	"#103 (unimplemented old socketaddr)",
	/* 104 */	"netbsd32_bind",
	/* 105 */	"setsockopt",
	/* 106 */	"netbsd32_listen",
	/* 107 */	"#107 (unimplemented vtimes)",
	/* 108 */	"sigvec",
	/* 109 */	"compat_43_netbsd32_sigblock",
	/* 110 */	"compat_43_netbsd32_sigsetmask",
	/* 111 */	"sigsuspend",
	/* 112 */	"compat_43_netbsd32_osigstack",
	/* 113 */	"compat_43_netbsd32_orecvmsg",
	/* 114 */	"compat_43_netbsd32_osendmsg",
	/* 115 */	"#115 (obsolete vtrace)",
	/* 116 */	"compat_50_netbsd32_gettimeofday",
	/* 117 */	"compat_50_netbsd32_getrusage",
	/* 118 */	"netbsd32_getsockopt",
	/* 119 */	"#119 (unimplemented)",
	/* 120 */	"netbsd32_readv",
	/* 121 */	"netbsd32_writev",
	/* 122 */	"compat_50_netbsd32_settimeofday",
	/* 123 */	"netbsd32_fchown",
	/* 124 */	"netbsd32_fchmod",
	/* 125 */	"compat_43_netbsd32_orecvfrom",
	/* 126 */	"netbsd32_setreuid",
	/* 127 */	"netbsd32_setregid",
	/* 128 */	"netbsd32_rename",
	/* 129 */	"compat_43_netbsd32_otruncate",
	/* 130 */	"compat_43_netbsd32_oftruncate",
	/* 131 */	"netbsd32_flock",
	/* 132 */	"#132 (unimplemented)",
	/* 133 */	"netbsd32_sendto",
	/* 134 */	"netbsd32_shutdown",
	/* 135 */	"socketpair",
	/* 136 */	"netbsd32_mkdir",
	/* 137 */	"netbsd32_rmdir",
	/* 138 */	"compat_50_netbsd32_utimes",
	/* 139 */	"sigreturn",
	/* 140 */	"compat_50_netbsd32_adjtime",
	/* 141 */	"compat_43_netbsd32_ogetpeername",
	/* 142 */	"gethostid",
	/* 143 */	"#143 (unimplemented old sethostid)",
	/* 144 */	"getrlimit",
	/* 145 */	"setrlimit",
	/* 146 */	"compat_43_netbsd32_killpg",
	/* 147 */	"#147 (unimplemented)",
	/* 148 */	"#148 (unimplemented)",
	/* 149 */	"#149 (unimplemented)",
	/* 150 */	"compat_43_netbsd32_ogetsockname",
	/* 151 */	"#151 (unimplemented getmsg)",
	/* 152 */	"#152 (unimplemented putmsg)",
	/* 153 */	"netbsd32_poll",
	/* 154 */	"#154 (unimplemented)",
	/* 155 */	"#155 (unimplemented nfssvc)",
	/* 156 */	"compat_43_netbsd32_ogetdirentries",
	/* 157 */	"statfs",
	/* 158 */	"fstatfs",
	/* 159 */	"unmount",
	/* 160 */	"#160 (unimplemented async_daemon)",
	/* 161 */	"getfh",
	/* 162 */	"compat_09_netbsd32_ogetdomainname",
	/* 163 */	"compat_09_netbsd32_osetdomainname",
	/* 164 */	"#164 (unimplemented rtschedule)",
	/* 165 */	"quotactl",
	/* 166 */	"exportfs",
	/* 167 */	"mount",
	/* 168 */	"ustat",
#ifdef SYSVSEM
	/* 169 */	"osemsys",
#else
	/* 169 */	"#169 (unimplemented semsys)",
#endif
#ifdef SYSVMSG
	/* 170 */	"omsgsys",
#else
	/* 170 */	"#170 (unimplemented msgsys)",
#endif
#ifdef SYSVSHM
	/* 171 */	"oshmsys",
#else
	/* 171 */	"#171 (unimplemented shmsys)",
#endif
	/* 172 */	"auditsys",
	/* 173 */	"#173 (unimplemented rfssys)",
	/* 174 */	"getdents",
	/* 175 */	"setsid",
	/* 176 */	"netbsd32_fchdir",
	/* 177 */	"netbsd32_fchroot",
	/* 178 */	"#178 (unimplemented vpixsys)",
	/* 179 */	"#179 (unimplemented aioread)",
	/* 180 */	"#180 (unimplemented aiowrite)",
	/* 181 */	"#181 (unimplemented aiowait)",
	/* 182 */	"#182 (unimplemented aiocancel)",
	/* 183 */	"sigpending",
	/* 184 */	"#184 (unimplemented)",
	/* 185 */	"netbsd32_setpgid",
	/* 186 */	"netbsd32_pathconf",
	/* 187 */	"netbsd32_fpathconf",
	/* 188 */	"sysconf",
	/* 189 */	"uname",
	/* 190 */	"# filler",
	/* 191 */	"# filler",
	/* 192 */	"# filler",
	/* 193 */	"# filler",
	/* 194 */	"# filler",
	/* 195 */	"# filler",
	/* 196 */	"# filler",
	/* 197 */	"# filler",
	/* 198 */	"# filler",
	/* 199 */	"# filler",
	/* 200 */	"# filler",
	/* 201 */	"# filler",
	/* 202 */	"# filler",
	/* 203 */	"# filler",
	/* 204 */	"# filler",
	/* 205 */	"# filler",
	/* 206 */	"# filler",
	/* 207 */	"# filler",
	/* 208 */	"# filler",
	/* 209 */	"# filler",
	/* 210 */	"# filler",
	/* 211 */	"# filler",
	/* 212 */	"# filler",
	/* 213 */	"# filler",
	/* 214 */	"# filler",
	/* 215 */	"# filler",
	/* 216 */	"# filler",
	/* 217 */	"# filler",
	/* 218 */	"# filler",
	/* 219 */	"# filler",
	/* 220 */	"# filler",
	/* 221 */	"# filler",
	/* 222 */	"# filler",
	/* 223 */	"# filler",
	/* 224 */	"# filler",
	/* 225 */	"# filler",
	/* 226 */	"# filler",
	/* 227 */	"# filler",
	/* 228 */	"# filler",
	/* 229 */	"# filler",
	/* 230 */	"# filler",
	/* 231 */	"# filler",
	/* 232 */	"# filler",
	/* 233 */	"# filler",
	/* 234 */	"# filler",
	/* 235 */	"# filler",
	/* 236 */	"# filler",
	/* 237 */	"# filler",
	/* 238 */	"# filler",
	/* 239 */	"# filler",
	/* 240 */	"# filler",
	/* 241 */	"# filler",
	/* 242 */	"# filler",
	/* 243 */	"# filler",
	/* 244 */	"# filler",
	/* 245 */	"# filler",
	/* 246 */	"# filler",
	/* 247 */	"# filler",
	/* 248 */	"# filler",
	/* 249 */	"# filler",
	/* 250 */	"# filler",
	/* 251 */	"# filler",
	/* 252 */	"# filler",
	/* 253 */	"# filler",
	/* 254 */	"# filler",
	/* 255 */	"# filler",
};
