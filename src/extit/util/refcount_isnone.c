/*
 * @(#) extit/util/refcount_isnone.c
 *
 * Check if there are no references.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/util.h>


extit_bool_t
EXTIT_DECL
extit_refcount_isnone
(
	const extit_refcount_t *refcount
)
{
	return (*refcount == EXTIT_REFCOUNT_NONE) ? EXTIT_TRUE : EXTIT_FALSE;
}
