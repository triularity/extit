/*
 * @(#) if/resolvable.h
 *
 * Resolvable Interface API.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__resolvable_h
#define	__if__resolvable_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_resolvable_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


/*
 * Resolvable Interface ID
 */
#define IF_RESOLVABLE_IID		"{7b1c1a0e-399b-11e6-9660-406186e454c1}/resolvable"


/*
 * Resolvable (base)
 */
typedef struct _if_resolvable		if_resolvable_t;


/*
 * Resolvable (v1.0)
 */
#define IF_RESOLVABLE_ABI_1_0		IV_VERSION(1,0)

typedef struct _if_resolvable_1_0	if_resolvable_1_0_t;


/*
 * Public API (v1.0)
 */
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

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__resolvable_h */
