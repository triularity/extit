/*
 * @(#) util/refcount.c
 *
 * Reference Count utilities.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/util.h>


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_refcount_add
(
	extit_refcount_t *refcount
)
{
	extit_refcount_t	count;


	if((count = *refcount) == EXTIT_REFCOUNT_MAX)
		return EXTIT_STATUS_INVALID;

	*refcount = count + 1;

	return EXTIT_STATUS_OK;
}


EXTIT_EXPORT
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

	if(count != EXTIT_REFCOUNT_NONE)
		return EXTIT_STATUS_BUSY;
	else
		return EXTIT_STATUS_OK;
}
