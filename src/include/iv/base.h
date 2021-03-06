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
 * Interface Version
 */
typedef	uint32_t		iv_version_t;


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
