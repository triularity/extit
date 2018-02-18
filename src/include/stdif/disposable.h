/*
 * @(#) stdif/disposable.h
 *
 * Disposable Interface.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__disposable_h
#define	__stdif__disposable_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	stdif_disposable_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Disposable Interface ID
 */
#define STDIF_DISPOSABLE_IID		"disposable@{c1c017b1-44d5-11e6-9660-406186e454c1}"


/*
 * Disposable (base)
 */
typedef struct _stdif_disposable	stdif_disposable_t;


/*
 * Disposable (v1.0)
 */
#define STDIF_DISPOSABLE_ABI_1_0	IV_VERSION(1,0)

typedef struct _stdif_disposable_1_0	stdif_disposable_1_0_t;

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_disposable_free__1_0(
				stdif_disposable_t *disposable);


/*
 * ABI Version
 */
#ifndef	STDIF_DISPOSABLE_ABI_TARGET
#define	STDIF_DISPOSABLE_ABI_TARGET	STDIF_DISPOSABLE_ABI_1_0
#endif

#if	IV_VERSION_MAJOR(STDIF_DISPOSABLE_ABI_TARGET) == 1
#define	stdif_disposable_free		stdif_disposable_free__1_0
#endif

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__stdif__disposable_h */
