/*
 * @(#) stdif/resolvable.h
 *
 * Resolvable Interface.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__resolvable_h
#define	__stdif__resolvable_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	stdif_resolvable_EXPORTS
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
#define STDIF_RESOLVABLE_IID		"resolvable@{c1c017b1-44d5-11e6-9660-406186e454c1}"


/*
 * Resolvable (base)
 */
typedef struct _stdif_resolvable	stdif_resolvable_t;


/*
 * Resolvable (v1.0)
 */
#define STDIF_RESOLVABLE_ABI_1_0	IV_VERSION(1,0)

typedef struct _stdif_resolvable_1_0	stdif_resolvable_1_0_t;

LIBAPI
void *			EXTIT_DECL
			stdif_resolvable_get_interface__1_0(
				stdif_resolvable_t *resolvable,
				const char *id,
				iv_version_t version);

LIBAPI
iv_version_t		EXTIT_DECL
			stdif_resolvable_query_interface__1_0(
				stdif_resolvable_t *resolvable,
				const char *id,
				iv_version_t base_version);


/*
 * ABI Version
 */
#ifndef	STDIF_RESOLVABLE_ABI_TARGET
#define	STDIF_RESOLVABLE_ABI_TARGET	STDIF_RESOLVABLE_ABI_1_0
#endif

#if	IV_VERSION_MAJOR(STDIF_RESOLVABLE_ABI_TARGET) == 1
#define	stdif_resolvable_get_interface	stdif_resolvable_get_interface__1_0
#define	stdif_resolvable_query_interface	stdif_resolvable_query_interface__1_0
#endif

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__stdif__resolvable_h */
