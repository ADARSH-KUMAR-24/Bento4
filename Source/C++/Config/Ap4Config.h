/*****************************************************************
|
|    AP4 - Target Platform and Compiler Configuration
|
|    Copyright 2002-2006 Gilles Boccon-Gibod
|
|
|    This file is part of Bento4/AP4 (MP4 Atom Processing Library).
|
|    Unless you have obtained Bento4 under a difference license,
|    this version of Bento4 is Bento4|GPL.
|    Bento4|GPL is free software; you can redistribute it and/or modify
|    it under the terms of the GNU General Public License as published by
|    the Free Software Foundation; either version 2, or (at your option)
|    any later version.
|
|    Bento4|GPL is distributed in the hope that it will be useful,
|    but WITHOUT ANY WARRANTY; without even the implied warranty of
|    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|    GNU General Public License for more details.
|
|    You should have received a copy of the GNU General Public License
|    along with Bento4|GPL; see the file COPYING.  If not, write to the
|    Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
|    02111-1307, USA.
|
 ****************************************************************/
/**
 * @file
 * @brief Platform Configuration
 */
#ifndef _AP4_CONFIG_H_
#define _AP4_CONFIG_H_

/*----------------------------------------------------------------------
|   defaults
+---------------------------------------------------------------------*/
#define AP4_CONFIG_HAVE_STDIO_H
#define AP4_CONFIG_HAVE_ASSERT_H
#define AP4_CONFIG_HAVE_STRING_H

#define AP4_CONFIG_HAVE_SNPRINTF
#define AP4_CONFIG_HAVE_VSNPRINTF

/*----------------------------------------------------------------------
|   byte order
+---------------------------------------------------------------------*/
// define AP4_PLATFORM_BYTE_ORDER to one of these two choices
#define AP4_PLATFORM_BYTE_ORDER_BIG_ENDIAN    0
#define AP4_PLATFORM_BYTE_ORDER_LITTLE_ENDIAN 1

#if !defined(AP4_PLATFORM_BYTE_ORDER)
#if defined(__ppc__)
#define AP4_PLATFORM_BYTE_ORDER AP4_PLATFORM_BYTE_ORDER_BIG_ENDIAN
#elif defined(__i386__)
#define AP4_PLATFORM_BYTE_ORDER AP4_PLATFORM_BYTE_ORDER_LITTLE_ENDIAN
#endif
#endif

/*----------------------------------------------------------------------
|   Win32 specifics
+---------------------------------------------------------------------*/
#if defined(_MSC_VER)
#define AP4_CONFIG_HAVE_INT64
#define AP4_CONFIG_INT64_TYPE __int64
#if (_MSC_VER >= 1400)
#define AP4_CONFIG_HAVE_FOPEN_S
#define AP4_snprintf(s,c,f,...) _snprintf_s(s,c,_TRUNCATE,f,__VA_ARGS__)
#define AP4_vsnprintf(s,c,f,a)  _vsnprintf_s(s,c,_TRUNCATE,f,a)
#define fileno _fileno
#else
#define AP4_snprintf   _snprintf
#define AP4_vsnprintf  _vsnprintf
#endif
#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#endif
#endif

/*----------------------------------------------------------------------
|    defaults
+---------------------------------------------------------------------*/
/* some compilers (ex: MSVC 8) deprecate those, so we rename them */
#if !defined(AP4_snprintf)
#define AP4_snprintf snprintf
#endif
#if !defined(AP4_vsnprintf)
#define AP4_vsnprintf vsnprintf
#endif

#endif // _AP4_CONFIG_H_