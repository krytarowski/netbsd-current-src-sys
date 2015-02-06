/*
 * Copyright (c) 2015 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Kamil Rytarowski.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 2012-2015 Xi Wang. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Brief history notes:
 * This work by Kamil Rytarowski for the NetBSD system reuses ideas from
 * the libo library by Xi Wang [ https://github.com/xiw/libo ]
 *
 * All of the code except OVERFLOW_GENERIC() was written by Kamil Rytarowski.
 */

#include <sys/param.h>
#include <sys/types.h>
#include <sys/cdefs.h>

#ifndef _SYS_OVERFLOW_H_
#define _SYS_OVERFLOW_H_

__BEGIN_DECLS
int overflow_add_char(char *r, char a, char b);
int overflow_add_schar(signed char *r, signed char a, signed char b);
int overflow_add_shrt(short *r, short a, short b);
int overflow_add_int(int *r, int a, int b);
int overflow_add_long(long *r, long a, long b);
int overflow_add_llong(long long *r, long long a, long long b);
int overflow_add_uchar(unsigned char *r, unsigned char a, unsigned char b);
int overflow_add_ushrt(unsigned short *r, unsigned short a, unsigned short b);
int overflow_add_uint(unsigned int *r, unsigned int a, unsigned int b);
int overflow_add_ulong(unsigned long *r, unsigned long a, unsigned long b);
int overflow_add_ullong(unsigned long long *r, unsigned long long a,
                        unsigned long long b);

int overflow_sub_char(char *r, char a, char b);
int overflow_sub_schar(signed char *r, signed char a, signed char b);
int overflow_sub_shrt(short *r, short a, short b);
int overflow_sub_int(int *r, int a, int b);
int overflow_sub_long(long *r, long a, long b);
int overflow_sub_llong(long long *r, long long a, long long b);
int overflow_sub_uchar(unsigned char *r, unsigned char a, unsigned char b);
int overflow_sub_ushrt(unsigned short *r, unsigned short a, unsigned short b);
int overflow_sub_uint(unsigned int *r, unsigned int a, unsigned int b);
int overflow_sub_ulong(unsigned long *r, unsigned long a, unsigned long b);
int overflow_sub_ullong(unsigned long long *r, unsigned long long a,
                        unsigned long long b);

int overflow_mul_char(char *r, char a, char b);
int overflow_mul_schar(signed char *r, signed char a, signed char b);
int overflow_mul_shrt(short *r, short a, short b);
int overflow_mul_int(int *r, int a, int b);
int overflow_mul_long(long *r, long a, long b);
int overflow_mul_llong(long long *r, long long a, long long b);
int overflow_mul_uchar(unsigned char *r, unsigned char a, unsigned char b);
int overflow_mul_ushrt(unsigned short *r, unsigned short a, unsigned short b);
int overflow_mul_uint(unsigned int *r, unsigned int a, unsigned int b);
int overflow_mul_ulong(unsigned long *r, unsigned long a, unsigned long b);
int overflow_mul_ullong(unsigned long long *r, unsigned long long a,
                        unsigned long long b);

int overflow_div_char(char *r, char a, char b);
int overflow_div_schar(signed char *r, signed char a, signed char b);
int overflow_div_shrt(short *r, short a, short b);
int overflow_div_int(int *r, int a, int b);
int overflow_div_long(long *r, long a, long b);
int overflow_div_llong(long long *r, long long a, long long b);
int overflow_div_uchar(unsigned char *r, unsigned char a, unsigned char b);
int overflow_div_ushrt(unsigned short *r, unsigned short a, unsigned short b);
int overflow_div_uint(unsigned int *r, unsigned int a, unsigned int b);
int overflow_div_ulong(unsigned long *r, unsigned long a, unsigned long b);
int overflow_div_ullong(unsigned long long *r, unsigned long long a,
                        unsigned long long b);

/* Check for C11 capable compiler */
#if defined(__has_feature)
#if __has_feature(c_generic_selections)
#define __has_c_generic_selections 1
#endif
#endif


#if __has_c_generic_selections \
     || __GNUC_PREREQ__(4,9) \
     || ((__STDC_VERSION__ - 0) > 201112L)

#define overflow_add(r, a, b) _Generic((r),				\
	char *: overflow_add_char,					\
	signed char*: overflow_add_schar,				\
	short*: overflow_add_shrt,					\
	int*: overflow_add_int,						\
	long*: overflow_add_long,					\
	long long*: overflow_add_llong,					\
	unsigned char*: overflow_add_uchar,				\
	unsigned short*: overflow_add_ushrt,				\
	unsigned int*: overflow_add_uint,				\
	unsigned long*: overflow_add_ulong,				\
	unsigned long long*: overflow_add_ullong) ((r), (a), (b))

#define overflow_sub(r, a, b) _Generic((r),				\
	char *: overflow_sub_char,					\
	signed char*: overflow_sub_schar,				\
	short*: overflow_sub_shrt,					\
	int*: overflow_sub_int,						\
	long*: overflow_sub_long,					\
	long long*: overflow_sub_llong,					\
	unsigned char*: overflow_sub_uchar,				\
	unsigned short*: overflow_sub_ushrt,				\
	unsigned int*: overflow_sub_uint,				\
	unsigned long*: overflow_sub_ulong,				\
	unsigned long long*: overflow_sub_ullong) ((r), (a), (b))

#define overflow_mul(r, a, b) _Generic((r),				\
	char *: overflow_mul_char,					\
	signed char*: overflow_mul_schar,				\
	short*: overflow_mul_shrt,					\
	int*: overflow_mul_int,						\
	long*: overflow_mul_long,					\
	long long*: overflow_mul_llong,					\
	unsigned char*: overflow_mul_uchar,				\
	unsigned short*: overflow_mul_ushrt,				\
	unsigned int*: overflow_mul_uint,				\
	unsigned long*: overflow_mul_ulong,				\
	unsigned long long*: overflow_mul_ullong) ((r), (a), (b))

#define overflow_div(r, a, b) _Generic((r),				\
	char *: overflow_div_char,					\
	signed char*: overflow_div_schar,				\
	short*: overflow_div_shrt,					\
	int*: overflow_div_int,						\
	long*: overflow_div_long,					\
	long long*: overflow_div_llong,					\
	unsigned char*: overflow_div_uchar,				\
	unsigned short*: overflow_div_ushrt,				\
	unsigned int*: overflow_div_uint,				\
	unsigned long*: overflow_div_ulong,				\
	unsigned long long*: overflow_div_ullong) ((r), (a), (b))

/* We assume that old Clang GCC are supported with these extensions */
#elif (defined(__clang__) || defined(__GNUC__))

#define OVERFLOW_GENERIC(op, r, a, b)					\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), char),		\
	overflow_##op##_char((char *)r, a, b),				\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), signed char),	\
	overflow_##op##_schar((signed char *)r, a, b),			\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), short),		\
	overflow_##op##_shrt((short *)r, a, b),				\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), int),		\
	overflow_##op##_int((int *)r, a, b),				\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), long),		\
	overflow_##op##_long((long *)r, a, b),				\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), long long),		\
	overflow_##op##_llong((long long *)r, a, b),			\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), unsigned char),	\
	overflow_##op##_uchar((unsigned char *)r, a, b),		\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), unsigned short),	\
	overflow_##op##_ushrt((unsigned short *)r, a, b),		\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), unsigned int),	\
	overflow_##op##_uint((unsigned int *)r, a, b),			\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), unsigned long),	\
	overflow_##op##_ulong((unsigned long *)r, a, b),		\
	__builtin_choose_expr(						\
	__builtin_types_compatible_p(typeof(*(r)), unsigned long long),	\
	overflow_##op##_ullong((unsigned long long *)r, a, b),		\
	(void)0)))))))))))

#define overflow_add(r, a, b)	OVERFLOW_GENERIC(add, (r), (a), (b))
#define overflow_sub(r, a, b)	OVERFLOW_GENERIC(sub, (r), (a), (b))
#define overflow_mul(r, a, b)	OVERFLOW_GENERIC(mul, (r), (a), (b))
#define overflow_div(r, a, b)	OVERFLOW_GENERIC(div, (r), (a), (b))

#else /* dump implementation */

/* Security sensitive code should check for OVERFLOW_FUNCS_DUMMY */
#define OVERFLOW_FUNCS_DUMMY 1

#define overflow_add(r, a, b)	(((*r) = (a) + (b)),0)
#define overflow_sub(r, a, b)	(((*r) = (a) - (b)),0)
#define overflow_mul(r, a, b)	(((*r) = (a) * (b)),0)
#define overflow_div(r, a, b)	(((*r) = (a) / (b)),0)

#endif

/* Cleanup */

#ifdef __has_c_generic_selections
#undef __has_c_generic_selections
#endif
__END_DECLS

#endif	/* _SYS_OVERFLOW_H_ */
