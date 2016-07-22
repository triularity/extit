/*
 * @(#) if/refcount/get.c
 *
 * Reference Count Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <if/refcount.h>
#include <if/refcount_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_refcount_t
EXTIT_DECL
if_refcount_get
(
	if_refcount_t *refcount
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(refcount->version, IF_REFCOUNT_ABI_1_0))
		return EXTIT_REFCOUNT_NONE;
#endif

	return IF_REFCOUNT_GET(refcount);
}
