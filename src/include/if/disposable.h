/*
 * @(#) if/disposable.h
 *
 * Disposable Interface.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__disposable_h
#define	__if__disposable_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_disposable_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


/*
 * Disposable Interface ID
 */
#define IF_DISPOSABLE_IID		"{c20950b5-310a-11e6-9b95-406186e454c1}/disposable"

/*
 * Disposable (v1.0)
 */
#define IF_DISPOSABLE_ABI_1_0		IV_VERSION(1,0)
typedef struct _if_disposable_1_0	if_disposable_1_0_t;


/*
 * ABI Version
 */
#ifndef	IF_DISPOSABLE_ABI_TARGET
#define	IF_DISPOSABLE_ABI_TARGET	IF_DISPOSABLE_ABI_1_0
#endif

#if	IF_DISPOSABLE_ABI_TARGET == IF_DISPOSABLE_ABI_1_0
typedef	if_disposable_1_0_t		if_disposable_t;
#else
#error	Unsupported IF_DISPOSABLE_ABI_TARGET version
#endif


/*
 * Public API (v1.0)
 */
LIBAPI
extit_status_t		EXTIT_DECL
			if_disposable_free__1_0(
				if_disposable_t *disposable);


#if	IV_VERSION_MAJOR(IF_DISPOSABLE_ABI_TARGET) == 1
#define	if_disposable_free(disposable)	\
			if_disposable_free__1_0((disposable))
#endif	/* IV_VERSION_MAJOR(IF_DISPOSABLE_ABI_TARGET) == 1 */

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__disposable_h */
