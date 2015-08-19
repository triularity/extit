/*
 * @(#) extit/base.h
 *
 * ExtIt base declarations.
 *
 * Copyright (c) 2014, 2015, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__base_h
#define	__extit__base_h

#include <iv/base.h>

/*
 * ExtIt Library Version (v0.4.0)
 */
#define	EXTIT_LIB_VERSION_MAJOR		0
#define	EXTIT_LIB_VERSION_MINOR		4
#define	EXTIT_LIB_VERSION_PATCH		0
#define	EXTIT_LIB_VERSION		((EXTIT_LIB_VERSION_MAJOR << 16)|(EXTIT_LIB_VERSION_MINOR<<8)|EXTIT_LIB_VERSION_PATCH)


#ifdef	EXTIT_COMPAT
typedef	iv_version_t		extit_iv_t;

#define	EXTIT_IV(major, minor)		IV_VERSION((major), (minor))
#define	EXTIT_IV_MAJOR(v)		IV_VERSION_MAJOR(v)
#define	EXTIT_IV_MINOR(v)		IV_VERSION_MINOR(v)
#define	EXTIT_IV_NONE			IV_VERSION_NONE
#endif	/* EXTIT_COMPAT */


/*
 * ExtIt API Version (v1.0)
 */
#define	EXTIT_API_VERSION_MAJOR	1
#define	EXTIT_API_VERSION_MINOR	0
#define	EXTIT_API_VERSION		IV_VERSION(EXTIT_API_VERSION_MAJOR, EXTIT_API_VERSION_MINOR)

#define	EXTIT_API_VERSION_1_0		IV_VERSION(1,0)


/*
 * Default Target Version
 */
#ifndef	EXTIT_API_TARGET
#define	EXTIT_API_TARGET		EXTIT_API_VERSION
#endif


/*
 * Flags (v1.0)
 */
#define	EXTIT_FLAG_LOG			0x00000003
#define	EXTIT_FLAG_LOG_MINIMAL		0x00000000
#define	EXTIT_FLAG_LOG_NORMAL		0x00000001
#define	EXTIT_FLAG_LOG_DEBUG		0x00000002
#define	EXTIT_FLAG_LOG_TRACE		0x00000003


/*
 * Status Codes (v1.0)
 */
#define	EXTIT_STATUS_OK			0
#define	EXTIT_STATUS_FAIL		1
#define	EXTIT_STATUS_NOMEM		2
#define	EXTIT_STATUS_INVALID		3
#define	EXTIT_STATUS_UNSUPPORTED	4
#define	EXTIT_STATUS_BUSY		5

#define	EXTIT_STATUS_CUSTOM_MASK	0x8000

typedef	unsigned int		extit_status_t;


/*
 * DLL Export Modifier
 */
#ifdef	_WIN32
#ifdef	EXTIT_DLL_BUILD
#define	EXTIT_EXPORT		__declspec(dllimport)
#else
#define	EXTIT_EXPORT		__declspec(dllexport)
#endif
#else
#define	EXTIT_EXPORT
#endif


/*
 * Structure Packing
 */
#ifndef	EXTIT_PACK
#define	EXTIT_PACK		/* */
#endif


/*
 * Function Declaration (for call style)
 */
#ifndef	EXTIT_DECL
#define	EXTIT_DECL		/* __cdecl */
#endif

#ifndef	EXTIT_DECL_VARGS
#define	EXTIT_DECL_VARGS	/* __cdecl */
#endif

#endif	/* !__extit__base_h */
