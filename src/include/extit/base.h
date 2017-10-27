/*
 * @(#) extit/base.h
 *
 * ExtIt base declarations.
 *
 * Copyright (c) 2014-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__base_h
#define	__extit__base_h

#ifdef	_WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <iv/base.h>

/*
 * ExtIt ABI Version (v1.0)
 */
#define	EXTIT_ABI_1_0		IV_VERSION(1,0)


/*
 * ExtIt function pointer
 */
#ifndef	EXTIT_HAVE_DLFUNC_T
#if	defined(__FreeBSD__)
#define	EXTIT_HAVE_DLFUNC_T
#endif
#endif

#ifdef	_WIN32
typedef FARPROC		extit_func_t;
#elif	defined(EXTIT_HAVE_DLFUNC_T)
typedef dlfunc_t	extit_func_t;
#else
struct __extit_dummyarg_
{
	int		nothing;
};

typedef void		(*extit_func_t)(struct __extit_dummyarg_);
#endif


/*
 * ABI Version
 */
#ifndef	EXTIT_ABI_TARGET
#define	EXTIT_ABI_TARGET		EXTIT_ABI_1_0
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
typedef enum _extit_status
{
	EXTIT_STATUS_OK			= 0,	/* Success */
	EXTIT_STATUS_FAIL		= 1,	/* General error */
	EXTIT_STATUS_NOMEM		= 2,	/* Memory allocation failed */
	EXTIT_STATUS_INVALID		= 3,	/* Invalid parameter/state */
	EXTIT_STATUS_UNSUPPORTED	= 4,	/* API/version not supported */
	EXTIT_STATUS_BUSY		= 5,	/* In use */
	EXTIT_STATUS_NOTIMPLEMENTED	= 6,	/* Function not implemented */
	EXTIT_STATUS_NOTFOUND		= 7,	/* Result not found */
	EXTIT_STATUS_NOPREREQ		= 8,	/* Pre-requirement missing */

	EXTIT_STATUS_CUSTOM_BASE	= 0x8000
} extit_status_t;


/*
 * DLL Export Modifier
 */
#if	defined(EXTIT_LINK_SHARED) && defined(_WIN32)
#define	EXTIT_EXPORT		__declspec(dllexport)
#define	EXTIT_IMPORT		__declspec(dllimport)
#define	EXTIT_IMPORT_STUB	/* */
#else
#define	EXTIT_EXPORT		/* */
#define	EXTIT_IMPORT		/* */
#define	EXTIT_IMPORT_STUB	/* */
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
