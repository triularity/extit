/*
 * @(#) extit/if/resolvable.h
 *
 * Resolvable Interface API.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__resolvable_h
#define	__extit__if__resolvable_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Resolvable Interface ID
 */
#define EXTIT_IF_RESOLVABLE_IID		"{7b1c1a0e-399b-11e6-9660-406186e454c1}/resolvable"

/*
 * Resolvable (v1.0)
 */
#define EXTIT_IF_RESOLVABLE_ABI_1_0	IV_VERSION(1,0)
typedef struct _extit_if_resolvable_1_0	extit_if_resolvable_1_0_t;


/*
 * ABI Version
 */
#define	EXTIT_IF_RESOLVABLE_ABI		EXTIT_IF_RESOLVABLE_ABI_1_0

#ifndef	EXTIT_IF_RESOLVABLE_ABI_TARGET
#define	EXTIT_IF_RESOLVABLE_ABI_TARGET	EXTIT_IF_RESOLVABLE_ABI
#endif

#if	EXTIT_IF_RESOLVABLE_ABI_TARGET == EXTIT_IF_RESOLVABLE_ABI_1_0
#define	extit_if_resolvable_t		extit_if_resolvable_1_0_t
#else
#error	Unsupported EXTIT_IF_RESOLVABLE_ABI_TARGET version
#endif


/*
 * Public API (v1.0)
 */
EXTIT_EXPORT
void *			EXTIT_DECL
			extit_if_resolvable_get_interface(
				extit_if_resolvable_t *resolvable,
				const char *id,
				iv_version_t version);

EXTIT_EXPORT
iv_version_t		EXTIT_DECL
			extit_if_resolvable_query_interface(
				extit_if_resolvable_t *resolvable,
				const char *id,
				iv_version_t base_version);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__resolvable_h */
