/*
 * @(#) if/referenced.h
 *
 * Referenced Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__referenced_h
#define	__if__referenced_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_referenced_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


/*
 * Referenced Interface ID
 */
#define IF_REFERENCED_IID		"{e8fc9c0b-30fa-11e6-9b95-406186e454c1}/referenced"

/*
 * Referenced (v1.0)
 */
#define IF_REFERENCED_ABI_1_0		IV_VERSION(1,0)
typedef struct _if_referenced_1_0	if_referenced_1_0_t;


/*
 * ABI Version
 */
#ifndef	IF_REFERENCED_ABI_TARGET
#define	IF_REFERENCED_ABI_TARGET	IF_REFERENCED_ABI_1_0
#endif

#if	IF_REFERENCED_ABI_TARGET == IF_REFERENCED_ABI_1_0
typedef	if_referenced_1_0_t		if_referenced_t;
#else
#error	Unsupported IF_REFERENCED_ABI_TARGET version
#endif


/*
 * Public API (v1.0)
 */
LIBAPI
extit_status_t		EXTIT_DECL
			if_referenced_add(
				if_referenced_t *referenced);

LIBAPI
extit_status_t		EXTIT_DECL
			if_referenced_release(
				if_referenced_t *referenced);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__referenced_h */
