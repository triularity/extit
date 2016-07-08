/*
 * @(#) extit/if/refcount.h
 *
 * Reference Count Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__refcount_h
#define	__extit__if__refcount_h

#include <iv/base.h>
#include <extit/base.h>
#include <extit/util.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Reference Count Interface ID
 */
#define EXTIT_IF_REFCOUNT_IID		"{e8fc9c0b-30fa-11e6-9b95-406186e454c1}/refcount"

/*
 * Reference Count (v1.0)
 */
#define EXTIT_IF_REFCOUNT_ABI_1_0	IV_VERSION(1,0)

typedef struct _extit_if_refcount_1_0	extit_if_refcount_1_0_t;


#ifndef	EXTIT_IF_REFCOUNT_ABI
#define	EXTIT_IF_REFCOUNT_ABI		EXTIT_IF_REFCOUNT_ABI_1_0
#endif

#if	EXTIT_IF_REFCOUNT_ABI == EXTIT_IF_REFCOUNT_ABI_1_0
#define	extit_if_refcount_t		extit_if_refcount_1_0_t
#else
#error	Unsupported EXTIT_IF_REFCOUNT_ABI
#endif


/*
 * Public API (v1.0)
 */
EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_if_refcount_add(
				extit_if_refcount_t *refcount);

EXTIT_EXPORT
extit_refcount_t	EXTIT_DECL
			extit_if_refcount_get(
				extit_if_refcount_t *refcount);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_if_refcount_release(
				extit_if_refcount_t *refcount);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__refcount_h */
