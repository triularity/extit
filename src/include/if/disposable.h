/*
 * @(#) if/disposable.h
 *
 * Disposable Interface.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__disposable_h
#define	__if__disposable_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	if_disposable_EXPORTS
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
#define IF_DISPOSABLE_IID		"{c1c017b1-44d5-11e6-9660-406186e454c1}/disposable"


/*
 * Disposable (base)
 */
typedef struct _if_disposable		if_disposable_t;


/*
 * Disposable (v1.0)
 */
#define IF_DISPOSABLE_ABI_1_0		IV_VERSION(1,0)

typedef struct _if_disposable_1_0	if_disposable_1_0_t;

LIBAPI
extit_status_t		EXTIT_DECL
			if_disposable_free__1_0(
				if_disposable_t *disposable);


/*
 * ABI Version
 */
#ifndef	IF_DISPOSABLE_ABI_TARGET
#define	IF_DISPOSABLE_ABI_TARGET	IF_DISPOSABLE_ABI_1_0
#endif

#if	IV_VERSION_MAJOR(IF_DISPOSABLE_ABI_TARGET) == 1
#define	if_disposable_free		if_disposable_free__1_0
#endif	/* IV_VERSION_MAJOR(IF_DISPOSABLE_ABI_TARGET) == 1 */

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__if__disposable_h */
