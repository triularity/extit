/*
 * @(#) iv/base.h
 *
 * Interface Versioning base.
 *
 * Copyright (c) 2015-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__iv__base_h
#define	__iv__base_h

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Library version (v0.9.1)
 */
#define	IV_LIB_VERSION_MAJOR		0
#define	IV_LIB_VERSION_MINOR		9
#define	IV_LIB_VERSION_PATCH		1
#define	IV_LIB_VERSION			((IV_LIB_VERSION_MAJOR << 16)|(IV_LIB_VERSION_MINOR<<8)|IV_LIB_VERSION_PATCH)


/*
 * Interface Version
 */
typedef	uint32_t		iv_version_t;

/*
 * IV boolean
 * (These match C++'s true/false values for binary interoperability)
 */
typedef	enum _iv_bool
{
	IV_FALSE = 0,
	IV_TRUE = 1
} iv_bool_t;


/*
 * Create an interface version
 */
#define	IV_VERSION(major, minor) \
				((((major) & 0xFFFF) << 16)|((minor) & 0xFFFF))

/*
 * Get the major version number
 */
#define	IV_VERSION_MAJOR(v)	(((v) >> 16) & 0xFFFF)

/*
 * Get the minor version number
 */
#define	IV_VERSION_MINOR(v)	((v) & 0xFFFF)

/*
 * Unspecified interface version.
 */
#define	IV_VERSION_NONE		IV_VERSION(0, 0)


/*
 * DLL Export Modifier
 */
#if	defined(IV_LINK_SHARED) && defined(_WIN32)
#define	IV_EXPORT		__declspec(dllexport)
#define	IV_IMPORT		__declspec(dllimport)
#else
#define	IV_EXPORT		/* */
#define	IV_IMPORT		/* */
#endif


/*
 * Function Declaration (for call style)
 */
#ifndef	IV_DECL
#define	IV_DECL			/* __cdecl */
#endif

#ifndef	IV_DECL_VARGS
#define	IV_DECL_VARGS		/* __cdecl */
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* !__iv__base_h */
