/*
 * @(#) extit/base.h
 *
 * ExtIt base declarations.
 *
 * Copyright (c) 2014, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__base_h
#define	__extit__base_h

/*
 * Interface Version
 */
typedef	unsigned int		extit_iv_t;

/*
 * Create an interface version
 */
#define	EXTIT_IV(major, minor)	((((major)&0xFFFF)<<16)|((minor)&0xFFFF))

/*
 * Get the major version number
 */
#define	EXTIT_IV_MAJOR(v)	(((v) >> 16) & 0xFFFF)

/*
 * Get the minor version number
 */
#define	EXTIT_IV_MINOR(v)	((v) & 0xFFFF)

/*
 * Unspecified interface version.
 */
#define	EXTIT_IV_NONE		EXTIT_IV(0, 0)


/*
 * ExtIt Library Version (v0.2.0)
 */
#define	EXTIT_LIB_VERSION_MAJOR		0
#define	EXTIT_LIB_VERSION_MINOR		2
#define	EXTIT_LIB_VERSION_PATCH		0
#define	EXTIT_LIB_VERSION		((EXTIT_LIB_VERSION_MAJOR << 16)|(EXTIT_LIB_VERSION_MINOR<<8)|EXTIT_LIB_VERSION_PATCH)


/*
 * ExtIt API Version (v1.0)
 */
#define	EXTIT_API_VERSION_MAJOR	1
#define	EXTIT_API_VERSION_MINOR	0
#define	EXTIT_API_VERSION		EXTIT_IV(EXTIT_API_VERSION_MAJOR, EXTIT_API_VERSION_MINOR)

#define	EXTIT_API_VERSION_1_0		EXTIT_IV(1,0)


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

#define	EXTIT_FLAG_CUSTOM		0xFF000000


/*
 * Status Codes (v1.0)
 */
#define	EXTIT_STATUS_OK			0
#define	EXTIT_STATUS_FAIL		1
#define	EXTIT_STATUS_NOMEM		2
#define	EXTIT_STATUS_INVALID		3
#define	EXTIT_STATUS_UNSUPPORTED	4
#define	EXTIT_STATUS_BUSY		5

#define	EXTIT_STATUS_CUSTOM_BASE	32768

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
 * Function Declaration (for call style)
 */
#ifndef	EXTIT_DECL
#define	EXTIT_DECL		__cdecl
#endif

#ifndef	EXTIT_DECL_VARGS
#define	EXTIT_DECL_VARGS	__cdecl
#endif

#endif	/* !__extit__base_h */
