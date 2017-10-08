/*
 * @(#) if/resolvable.h
 *
 * Resolvable Interface.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__resolvable_h
#define	__if__resolvable_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	if_resolvable_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Resolvable Interface ID
 */
#define IF_RESOLVABLE_IID		"{c1c017b1-44d5-11e6-9660-406186e454c1}/resolvable"


/*
 * Resolvable (base)
 */
typedef struct _if_resolvable		if_resolvable_t;


/*
 * Resolvable (v1.0)
 */
#define IF_RESOLVABLE_ABI_1_0		IV_VERSION(1,0)

typedef struct _if_resolvable_1_0	if_resolvable_1_0_t;

LIBAPI
void *			EXTIT_DECL
			if_resolvable_get_interface__1_0(
				if_resolvable_t *resolvable,
				const char *id,
				iv_version_t version);

LIBAPI
iv_version_t		EXTIT_DECL
			if_resolvable_query_interface__1_0(
				if_resolvable_t *resolvable,
				const char *id,
				iv_version_t base_version);


/*
 * ABI Version
 */
#ifndef	IF_RESOLVABLE_ABI_TARGET
#define	IF_RESOLVABLE_ABI_TARGET	IF_RESOLVABLE_ABI_1_0
#endif

#if	IV_VERSION_MAJOR(IF_RESOLVABLE_ABI_TARGET) == 1
#define	if_resolvable_get_interface	if_resolvable_get_interface__1_0
#define	if_resolvable_query_interface	if_resolvable_query_interface__1_0
#endif	/* IV_VERSION_MAJOR(IF_RESOLVABLE_ABI_TARGET) == 1 */

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__if__resolvable_h */
