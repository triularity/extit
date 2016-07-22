/*
 * @(#) if/refcount.h
 *
 * Reference Count Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__refcount_h
#define	__if__refcount_h

#include <iv/base.h>
#include <extit/base.h>
#include <extit/util.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_refcount_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


/*
 * Reference Count Interface ID
 */
#define IF_REFCOUNT_IID			"{e8fc9c0b-30fa-11e6-9b95-406186e454c1}/refcount"

/*
 * Reference Count (v1.0)
 */
#define IF_REFCOUNT_ABI_1_0		IV_VERSION(1,0)
typedef struct _if_refcount_1_0		if_refcount_1_0_t;


/*
 * ABI Version
 */
#ifndef	IF_REFCOUNT_ABI_TARGET
#define	IF_REFCOUNT_ABI_TARGET		IF_REFCOUNT_ABI_1_0
#endif

#if	IF_REFCOUNT_ABI_TARGET == IF_REFCOUNT_ABI_1_0
#define	if_refcount_t			if_refcount_1_0_t
#else
#error	Unsupported IF_REFCOUNT_ABI_TARGET version
#endif


/*
 * Public API (v1.0)
 */
LIBAPI
extit_status_t		EXTIT_DECL
			if_refcount_add(
				if_refcount_t *refcount);

LIBAPI
extit_refcount_t	EXTIT_DECL
			if_refcount_get(
				if_refcount_t *refcount);

LIBAPI
extit_status_t		EXTIT_DECL
			if_refcount_release(
				if_refcount_t *refcount);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__refcount_h */
