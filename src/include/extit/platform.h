/*
 * @(#) extit/platform.h
 *
 * Platform specific portability definitions/macros.
 *
 * Copyright (c) 2014, 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__platform_h
#define	__extit__platform_h

#ifdef	_WIN32
#include <windows.h>

#define	EXTIT_STRCASECMP(a,b)		_stricmp((a),(b))
#define	EXTIT_STRNCASECMP(a,b,l)	_strnicmp((a),(b),(l))

#define	EXTIT_FN_STRCMP(a,b)		EXTIT_STRCASECMP((a),(b))
#define	EXTIT_FN_STRNCMP(a,b,l)		EXTIT_STRNCASECMP((a),(b),(l))

#ifdef	EXTIT_WCHAR
#define	EXTIT_WCSCASECMP(a,b)		_wcsicmp((a),(b))
#define	EXTIT_WCNSCASECMP(a,b,l)	_wcsnicmp((a),(b),(l))

#define	EXTIT_FN_WCSCMP(a,b)		EXTIT_WCSCASECMP((a),(b))
#define	EXTIT_FN_WCSNCMP(a,b,l)		EXTIT_WCNSCASECMP((a),(b),(l))
#endif	/* EXTIT_WCHAR */

#else	/* _WIN32 */
#include <strings.h>

#define	EXTIT_STRCASECMP(a,b)		strcasecmp((a),(b))
#define	EXTIT_STRNCASECMP(a,b,l)	strncasecmp((a),(b),(l))

#define	EXTIT_FN_STRCMP(a,b)		strcmp((a),(b))
#define	EXTIT_FN_STRNCMP(a,b,l)		strncmp((a),(b),(l))

#ifdef	EXTIT_WCHAR
#define	EXTIT_WCSCASECMP(a,b)		wcscasecmp((a),(b))
#define	EXTIT_WCNSCASECMP(a,b,l)	wcsncasecmp((a),(b),(l))

#define	EXTIT_FN_WCSCMP(a,b)		wcscmp((a),(b))
#define	EXTIT_FN_WCSNCMP(a,b,l)		wcsncmp((a),(b),(l))
#endif	/* EXTIT_WCHAR */

#endif	/* _WIN32 */

#endif	/* !__extit__platform_h */
