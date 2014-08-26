/*	$NetBSD: font_8x8.c,v 1.4 2005/12/11 12:16:54 christos Exp $	*/

/*
 *  Copyright (c) 1992, 1993, 1994 Hellmuth Michaelis and Joerg Wunsch
 *  
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. All advertising materials mentioning features or use of this software
 *     must display the following acknowledgement:
 * 	This product includes software developed by
 *	Hellmuth Michaelis and Joerg Wunsch
 *  4. The name authors may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Translated into compiler and human readable for for the Atari-TT port of
 * NetBSD by Leo Weppelman.
 *
 * Reorganized and edited some chars to fit the iso-8859-1 fontset
 * by Thomas Gerner
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: font_8x8.c,v 1.4 2005/12/11 12:16:54 christos Exp $");

#include <atari/dev/font.h>

char fontname_8x8[64] = "vt220iso.808";

extern unsigned char fontdata_8x8[];

font_info	font_info_8x8 = { 1, 8, 8, 6, 0, 255, &fontdata_8x8[0] };
				
unsigned char fontdata_8x8[] = {
/* 0x00 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x01 */ 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x3c, 0x18,
/* 0x02 */ 0x5a, 0x99, 0x42, 0x99, 0x5a, 0x81, 0x5a, 0x99,
/* 0x03 */ 0x44, 0x44, 0x7c, 0x44, 0x3e, 0x08, 0x08, 0x08,
/* 0x04 */ 0x7c, 0x40, 0x78, 0x40, 0x3e, 0x20, 0x3c, 0x20,
/* 0x05 */ 0x3c, 0x40, 0x40, 0x3c, 0x3c, 0x22, 0x3c, 0x26,
/* 0x06 */ 0x40, 0x40, 0x40, 0x7c, 0x3e, 0x20, 0x3c, 0x20,
/* 0x07 */ 0x38, 0x6c, 0x6c, 0x38, 0x00, 0x00, 0x00, 0x00,
/* 0x08 */ 0x30, 0x30, 0xfc, 0x30, 0x30, 0x00, 0xfc, 0x00,
/* 0x09 */ 0x64, 0x54, 0x4c, 0x44, 0x20, 0x20, 0x20, 0x3e,
/* 0x0a */ 0x44, 0x44, 0x28, 0x10, 0x3e, 0x08, 0x08, 0x08,
/* 0x0b */ 0x18, 0x18, 0x18, 0xf8, 0x00, 0x00, 0x00, 0x00,
/* 0x0c */ 0x00, 0x00, 0x00, 0xf8, 0x18, 0x18, 0x18, 0x18,
/* 0x0d */ 0x00, 0x00, 0x00, 0x1f, 0x18, 0x18, 0x18, 0x18,
/* 0x0e */ 0x18, 0x18, 0x18, 0x1f, 0x00, 0x00, 0x00, 0x00,
/* 0x0f */ 0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18,
/* 0x10 */ 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x11 */ 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x12 */ 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
/* 0x13 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00,
/* 0x14 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
/* 0x15 */ 0x18, 0x18, 0x18, 0x1f, 0x18, 0x18, 0x18, 0x18,
/* 0x16 */ 0x18, 0x18, 0x18, 0xf8, 0x18, 0x18, 0x18, 0x18,
/* 0x17 */ 0x18, 0x18, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00,
/* 0x18 */ 0x00, 0x00, 0x00, 0xff, 0x18, 0x18, 0x18, 0x18,
/* 0x19 */ 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
/* 0x1a */ 0x30, 0x18, 0x0c, 0x18, 0x30, 0xfe, 0x00, 0xfe,
/* 0x1b */ 0x18, 0x30, 0x60, 0x30, 0x18, 0xfe, 0x00, 0xfe,
/* 0x1c */ 0x00, 0xfe, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x00,
/* 0x1d */ 0x02, 0x04, 0x7e, 0x08, 0x10, 0x7e, 0x20, 0x40,
/* 0x1e */ 0x38, 0x6c, 0x64, 0xf0, 0x60, 0xe6, 0xfc, 0x00,
/* 0x1f */ 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
/*  ' ' */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  '!' */ 0x18, 0x3c, 0x3c, 0x18, 0x18, 0x00, 0x18, 0x00,
/*  '"' */ 0x6c, 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  '#' */ 0x6c, 0x6c, 0xfe, 0x6c, 0xfe, 0x6c, 0x6c, 0x00,
/*  '$' */ 0x30, 0x7c, 0xc0, 0x7c, 0x06, 0xfc, 0x30, 0x00,
/*  '%' */ 0x00, 0xc6, 0xcc, 0x18, 0x30, 0x66, 0xc6, 0x00,
/*  '&' */ 0x38, 0x6c, 0x38, 0x76, 0xdc, 0xce, 0x7b, 0x00,
/*  ''' */ 0x60, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  '(' */ 0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00,
/*  ')' */ 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x18, 0x30, 0x00,
/*  '*' */ 0x00, 0x6c, 0x38, 0xfe, 0x38, 0x6c, 0x00, 0x00,
/*  '+' */ 0x00, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x00, 0x00,
/*  ',' */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x60,
/*  '-' */ 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00,
/*  '.' */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00,
/*  '/' */ 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00,
/*  '0' */ 0x7c, 0xce, 0xde, 0xf6, 0xe6, 0xc6, 0x7c, 0x00,
/*  '1' */ 0x30, 0x70, 0xb0, 0x30, 0x30, 0x30, 0xfc, 0x00,
/*  '2' */ 0x78, 0xcc, 0x0c, 0x38, 0x60, 0xc0, 0xfc, 0x00,
/*  '3' */ 0x78, 0xcc, 0x0c, 0x38, 0x0c, 0xcc, 0x78, 0x00,
/*  '4' */ 0x1c, 0x3c, 0x6c, 0xcc, 0xfe, 0x0c, 0x1e, 0x00,
/*  '5' */ 0xfc, 0xc0, 0xf8, 0x0c, 0x0c, 0xcc, 0x78, 0x00,
/*  '6' */ 0x78, 0xcc, 0xc0, 0xf8, 0xcc, 0xcc, 0x78, 0x00,
/*  '7' */ 0xfc, 0xcc, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x00,
/*  '8' */ 0x78, 0xcc, 0xcc, 0x78, 0xcc, 0xcc, 0x78, 0x00,
/*  '9' */ 0x78, 0xcc, 0xcc, 0x7c, 0x0c, 0xcc, 0x78, 0x00,
/*  ':' */ 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00,
/*  ';' */ 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x60,
/*  '<' */ 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x00,
/*  '=' */ 0x00, 0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00,
/*  '>' */ 0x30, 0x18, 0x0c, 0x06, 0x0c, 0x18, 0x30, 0x00,
/*  '?' */ 0x3c, 0x66, 0x06, 0x0c, 0x18, 0x00, 0x18, 0x00,
/*  '@' */ 0x7c, 0xc6, 0xde, 0xde, 0xde, 0xc0, 0x7e, 0x00,
/*  'A' */ 0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00,
/*  'B' */ 0xfc, 0x66, 0x66, 0x7c, 0x66, 0x66, 0xfc, 0x00,
/*  'C' */ 0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00,
/*  'D' */ 0xf8, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0xf8, 0x00,
/*  'E' */ 0xfe, 0x62, 0x68, 0x78, 0x68, 0x62, 0xfe, 0x00,
/*  'F' */ 0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0xf0, 0x00,
/*  'G' */ 0x3c, 0x66, 0xc0, 0xc0, 0xce, 0x66, 0x3e, 0x00,
/*  'H' */ 0xcc, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0xcc, 0x00,
/*  'I' */ 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
/*  'J' */ 0x1e, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78, 0x00,
/*  'K' */ 0xe6, 0x6c, 0x78, 0x70, 0x78, 0x6c, 0xe6, 0x00,
/*  'L' */ 0xf0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x00,
/*  'M' */ 0xc6, 0xee, 0xfe, 0xd6, 0xc6, 0xc6, 0xc6, 0x00,
/*  'N' */ 0xc6, 0xe6, 0xf6, 0xde, 0xce, 0xc6, 0xc6, 0x00,
/*  'O' */ 0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00,
/*  'P' */ 0xfc, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xf0, 0x00,
/*  'Q' */ 0x78, 0xcc, 0xcc, 0xcc, 0xdc, 0x78, 0x1c, 0x00,
/*  'R' */ 0xfc, 0x66, 0x66, 0x7c, 0x6c, 0x66, 0xe6, 0x00,
/*  'S' */ 0x78, 0xcc, 0xc0, 0x78, 0x0c, 0xcc, 0x78, 0x00,
/*  'T' */ 0xfc, 0xb4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
/*  'U' */ 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x00,
/*  'V' */ 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00,
/*  'W' */ 0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xfe, 0xc6, 0x00,
/*  'X' */ 0xc6, 0xc6, 0x6c, 0x38, 0x38, 0x6c, 0xc6, 0x00,
/*  'Y' */ 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x30, 0x78, 0x00,
/*  'Z' */ 0xfc, 0xcc, 0x98, 0x30, 0x64, 0xcc, 0xfc, 0x00,
/*  '[' */ 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00,
/*  '\' */ 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02, 0x00,
/*  ']' */ 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00,
/*  '^' */ 0x10, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00,
/*  '_' */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
/*  '`' */ 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  'a' */ 0x00, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x76, 0x00,
/*  'b' */ 0xe0, 0x60, 0x60, 0x7c, 0x66, 0x66, 0xfc, 0x00,
/*  'c' */ 0x00, 0x00, 0x78, 0xcc, 0xc0, 0xcc, 0x78, 0x00,
/*  'd' */ 0x1c, 0x0c, 0x0c, 0x7c, 0xcc, 0xcc, 0x7e, 0x00,
/*  'e' */ 0x00, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00,
/*  'f' */ 0x38, 0x6c, 0x60, 0xf8, 0x60, 0x60, 0xf0, 0x00,
/*  'g' */ 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8,
/*  'h' */ 0xe0, 0x60, 0x6c, 0x76, 0x66, 0x66, 0xe6, 0x00,
/*  'i' */ 0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
/*  'j' */ 0x0c, 0x00, 0x1c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78,
/*  'k' */ 0xe0, 0x60, 0x66, 0x6c, 0x78, 0x6c, 0xe6, 0x00,
/*  'l' */ 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
/*  'm' */ 0x00, 0x00, 0xcc, 0xfe, 0xfe, 0xd6, 0xc6, 0x00,
/*  'n' */ 0x00, 0x00, 0xf8, 0xcc, 0xcc, 0xcc, 0xcc, 0x00,
/*  'o' */ 0x00, 0x00, 0x78, 0xcc, 0xcc, 0xcc, 0x78, 0x00,
/*  'p' */ 0x00, 0x00, 0xdc, 0x66, 0x66, 0x7c, 0x60, 0xf0,
/*  'q' */ 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0x1e,
/*  'r' */ 0x00, 0x00, 0xdc, 0x76, 0x60, 0x60, 0xf0, 0x00,
/*  's' */ 0x00, 0x00, 0x7c, 0xc0, 0x7c, 0x06, 0xfc, 0x00,
/*  't' */ 0x10, 0x30, 0x7c, 0x30, 0x30, 0x36, 0x1c, 0x00,
/*  'u' */ 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x00,
/*  'v' */ 0x00, 0x00, 0xc6, 0xc6, 0xc6, 0x7c, 0x38, 0x00,
/*  'w' */ 0x00, 0x00, 0xc6, 0xd6, 0xfe, 0xfe, 0x6c, 0x00,
/*  'x' */ 0x00, 0x00, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0x00,
/*  'y' */ 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8,
/*  'z' */ 0x00, 0x00, 0xfc, 0x98, 0x30, 0x64, 0xfc, 0x00,
/*  '{' */ 0x1c, 0x30, 0x30, 0xe0, 0x30, 0x30, 0x1c, 0x00,
/*  '|' */ 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00,
/*  '}' */ 0xe0, 0x30, 0x30, 0x1c, 0x30, 0x30, 0xe0, 0x00,
/*  '~' */ 0x76, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x7f */ 0x10, 0x38, 0x6c, 0x6c, 0xc6, 0xc6, 0xfe, 0x00,
/* 0x80 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x81 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x82 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x83 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x84 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x85 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x86 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x87 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x88 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x89 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x8a */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x8b */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x8c */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x8d */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x8e */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x8f */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x90 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x91 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x92 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x93 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x94 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x95 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x96 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x97 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x98 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x99 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x9a */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x9b */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x9c */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x9d */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x9e */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x9f */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xa0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xa1 */ 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00,
/* 0xa2 */ 0x18, 0x18, 0x7e, 0xc0, 0xc0, 0x7e, 0x18, 0x18,
/* 0xa3 */ 0x38, 0x6c, 0x64, 0xf0, 0x60, 0xe6, 0xfc, 0x00,
/* 0xa4 */ 0x00, 0xc3, 0xdb, 0x3c, 0x66, 0x3c, 0xdb, 0xc3,
/* 0xa5 */ 0xcc, 0xcc, 0x78, 0xfc, 0x30, 0xfc, 0x30, 0x30,
/* 0xa6 */ 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18,
/* 0xa7 */ 0x7e, 0xc3, 0xfc, 0x66, 0x66, 0x3f, 0xc3, 0x7e,
/* 0xa8 */ 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xa9 */ 0x7c, 0x82, 0x9a, 0xa2, 0xa2, 0x9a, 0x82, 0x7c,
/* 0xaa */ 0x3c, 0x6c, 0x6c, 0x3e, 0x00, 0x7e, 0x00, 0x00,
/* 0xab */ 0x00, 0x33, 0x66, 0xcc, 0x66, 0x33, 0x00, 0x00,
/* 0xac */ 0x00, 0x00, 0x00, 0xfc, 0x0c, 0x0c, 0x00, 0x00,
/* 0xad */ 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00,
/* 0xae */ 0x7c, 0x82, 0xba, 0xaa, 0xb2, 0xaa, 0x82, 0x7c,
/* 0xaf */ 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb0 */ 0x38, 0x6c, 0x6c, 0x38, 0x00, 0x00, 0x00, 0x00,
/* 0xb1 */ 0x30, 0x30, 0xfc, 0x30, 0x30, 0x00, 0xfc, 0x00,
/* 0xb2 */ 0x70, 0x18, 0x30, 0x60, 0x78, 0x00, 0x00, 0x00,
/* 0xb3 */ 0x70, 0x18, 0x30, 0x18, 0x70, 0x00, 0x00, 0x00,
/* 0xb4 */ 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb5 */ 0x00, 0x66, 0x66, 0x66, 0x66, 0x7c, 0x60, 0xc0,
/* 0xb6 */ 0x7f, 0xdb, 0xdb, 0x7b, 0x1b, 0x1b, 0x1b, 0x00,
/* 0xb7 */ 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
/* 0xb8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x78,
/* 0xb9 */ 0x38, 0x78, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00,
/* 0xba */ 0x38, 0x6c, 0x6c, 0x38, 0x00, 0x7c, 0x00, 0x00,
/* 0xbb */ 0x00, 0xcc, 0x66, 0x33, 0x66, 0xcc, 0x00, 0x00,
/* 0xbc */ 0xc3, 0xc6, 0xcc, 0xdb, 0x37, 0x6f, 0xcf, 0x03,
/* 0xbd */ 0xc3, 0xc6, 0xcc, 0xde, 0x33, 0x66, 0xcc, 0x0f,
/* 0xbe */ 0xc3, 0x66, 0xcc, 0x5b, 0xb7, 0x6f, 0xcf, 0x03,
/* 0xbf */ 0x30, 0x00, 0x30, 0x60, 0xc0, 0xcc, 0x78, 0x00,
/* 0xc0 */ 0xe0, 0x38, 0x6c, 0xc6, 0xfe, 0xc6, 0xc6, 0x00,
/* 0xc1 */ 0x0e, 0x38, 0x6c, 0xc6, 0xfe, 0xc6, 0xc6, 0x00,
/* 0xc2 */ 0x7c, 0x82, 0x38, 0x6c, 0xc6, 0xfe, 0xc6, 0x00,
/* 0xc3 */ 0xfe, 0x00, 0x38, 0x6c, 0xc6, 0xfe, 0xc6, 0x00,
/* 0xc4 */ 0xc6, 0x38, 0x6c, 0xc6, 0xfe, 0xc6, 0xc6, 0x00,
/* 0xc5 */ 0x30, 0x30, 0x00, 0x78, 0xcc, 0xfc, 0xcc, 0x00,
/* 0xc6 */ 0x3e, 0x6c, 0xcc, 0xfe, 0xcc, 0xcc, 0xce, 0x00,
/* 0xc7 */ 0x78, 0xcc, 0xc0, 0xcc, 0x78, 0x18, 0x0c, 0x78,
/* 0xc8 */ 0xe0, 0x00, 0xfc, 0x60, 0x78, 0x60, 0xfc, 0x00,
/* 0xc9 */ 0x1c, 0x00, 0xfc, 0x60, 0x78, 0x60, 0xfc, 0x00,
/* 0xca */ 0x78, 0x00, 0xfc, 0x60, 0x78, 0x60, 0xfc, 0x00,
/* 0xcb */ 0xcc, 0x00, 0xfc, 0x60, 0x78, 0x60, 0xfc, 0x00,
/* 0xcc */ 0x70, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x3c, 0x00,
/* 0xcd */ 0x0e, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x3c, 0x00,
/* 0xce */ 0x7e, 0x81, 0x3c, 0x18, 0x18, 0x18, 0x3c, 0x00,
/* 0xcf */ 0x66, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x3c, 0x00,
/* 0xd0 */ 0xfc, 0x66, 0x66, 0xf6, 0x66, 0x66, 0xfc, 0x00,
/* 0xd1 */ 0xfc, 0x00, 0xcc, 0xec, 0xfc, 0xdc, 0xcc, 0x00,
/* 0xd2 */ 0x70, 0x00, 0x18, 0x3c, 0x66, 0x3c, 0x18, 0x00,
/* 0xd3 */ 0x0e, 0x00, 0x18, 0x3c, 0x66, 0x3c, 0x18, 0x00,
/* 0xd4 */ 0x3c, 0x42, 0x18, 0x3c, 0x66, 0x3c, 0x18, 0x00,
/* 0xd5 */ 0x7e, 0x00, 0x18, 0x3c, 0x66, 0x3c, 0x18, 0x00,
/* 0xd6 */ 0xc3, 0x18, 0x3c, 0x66, 0x66, 0x3c, 0x18, 0x00,
/* 0xd7 */ 0x00, 0x82, 0x44, 0x28, 0x10, 0x28, 0x44, 0x82,
/* 0xd8 */ 0x00, 0x02, 0x7c, 0xce, 0xd6, 0xe6, 0x7c, 0x80,
/* 0xd9 */ 0xe0, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x00,
/* 0xda */ 0x1c, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x00,
/* 0xdb */ 0x78, 0x84, 0x00, 0xcc, 0xcc, 0xcc, 0x78, 0x00,
/* 0xdc */ 0xcc, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x00,
/* 0xdd */ 0x1c, 0x00, 0xcc, 0xcc, 0x78, 0x30, 0x78, 0x00,
/* 0xde */ 0xf0, 0x60, 0x78, 0x6c, 0x78, 0x60, 0xf0, 0x00,
/* 0xdf */ 0x00, 0x78, 0xcc, 0xf8, 0xcc, 0xf8, 0xc0, 0xc0,
/* 0xe0 */ 0xe0, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x7e, 0x00,
/* 0xe1 */ 0x1c, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x7e, 0x00,
/* 0xe2 */ 0x7e, 0xc3, 0x3c, 0x06, 0x3e, 0x66, 0x3f, 0x00,
/* 0xe3 */ 0xfe, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x7e, 0x00,
/* 0xe4 */ 0xcc, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x7e, 0x00,
/* 0xe5 */ 0x30, 0x30, 0x78, 0x0c, 0x7c, 0xcc, 0x7e, 0x00,
/* 0xe6 */ 0x00, 0x00, 0x7f, 0x0c, 0x7f, 0xcc, 0x7f, 0x00,
/* 0xe7 */ 0x00, 0x00, 0x78, 0xc0, 0xc0, 0x78, 0x0c, 0x38,
/* 0xe8 */ 0xe0, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00,
/* 0xe9 */ 0x1c, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00,
/* 0xea */ 0x7e, 0xc3, 0x3c, 0x66, 0x7e, 0x60, 0x3c, 0x00,
/* 0xeb */ 0xcc, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00,
/* 0xec */ 0xe0, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
/* 0xed */ 0x38, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
/* 0xee */ 0x7c, 0xc6, 0x38, 0x18, 0x18, 0x18, 0x3c, 0x00,
/* 0xef */ 0xcc, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
/* 0xf0 */ 0x00, 0x7c, 0x30, 0x78, 0xcc, 0xcc, 0x78, 0x00,
/* 0xf1 */ 0x00, 0xf8, 0x00, 0xf8, 0xcc, 0xcc, 0xcc, 0x00,
/* 0xf2 */ 0x00, 0xe0, 0x00, 0x78, 0xcc, 0xcc, 0x78, 0x00,
/* 0xf3 */ 0x00, 0x1c, 0x00, 0x78, 0xcc, 0xcc, 0x78, 0x00,
/* 0xf4 */ 0x78, 0xcc, 0x00, 0x78, 0xcc, 0xcc, 0x78, 0x00,
/* 0xf5 */ 0x00, 0xfc, 0x00, 0x78, 0xcc, 0xcc, 0x78, 0x00,
/* 0xf6 */ 0x00, 0xcc, 0x00, 0x78, 0xcc, 0xcc, 0x78, 0x00,
/* 0xf7 */ 0x30, 0x30, 0x00, 0xfc, 0x00, 0x30, 0x30, 0x00,
/* 0xf8 */ 0x02, 0x3a, 0x6c, 0xd6, 0xd6, 0x6c, 0xb8, 0x80,
/* 0xf9 */ 0x00, 0xe0, 0x00, 0xcc, 0xcc, 0xcc, 0x7e, 0x00,
/* 0xfa */ 0x00, 0x1c, 0x00, 0xcc, 0xcc, 0xcc, 0x7e, 0x00,
/* 0xfb */ 0x78, 0xcc, 0x00, 0xcc, 0xcc, 0xcc, 0x7e, 0x00,
/* 0xfc */ 0x00, 0xcc, 0x00, 0xcc, 0xcc, 0xcc, 0x7e, 0x00,
/* 0xfd */ 0x00, 0x1c, 0x00, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8,
/* 0xfe */ 0x00, 0xc0, 0xc0, 0xf8, 0xcc, 0xf8, 0xc0, 0xc0,
/* 0xff */ 0x00, 0xcc, 0x00, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8
};
