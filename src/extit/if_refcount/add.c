/*
 * @(#) extit/if_refcount/add.c
 *
 * Reference Count Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/if/refcount.h>
#include <extit/if/refcount_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_refcount_add
(
	extit_if_refcount_t *refcount
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(refcount->version, EXTIT_IF_REFCOUNT_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IF_REFCOUNT_ADD(refcount);
}
