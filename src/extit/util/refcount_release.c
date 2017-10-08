/*
 * @(#) extit/util/refcount_release.c
 *
 * Decrease a reference count.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/util.h>


extit_status_t
EXTIT_DECL
extit_refcount_release
(
	extit_refcount_t *refcount
)
{
	extit_refcount_t	count;


	if((count = *refcount) == EXTIT_REFCOUNT_NONE)
		return EXTIT_STATUS_INVALID;

	*refcount = --count;

	return EXTIT_STATUS_OK;
}
