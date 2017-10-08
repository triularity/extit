/*
 * @(#) util/refcount.c
 *
 * Reference Count utilities.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/util.h>


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


extit_bool_t
EXTIT_DECL
extit_refcount_isnone
(
	const extit_refcount_t *refcount
)
{
	return (*refcount == EXTIT_REFCOUNT_NONE) ? EXTIT_TRUE : EXTIT_FALSE;
}


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

