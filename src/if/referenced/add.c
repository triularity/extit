/*
 * @(#) if/referenced/add.c
 *
 * Referenced Interface client API wrappers.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <if/referenced.h>
#include <if/referenced_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_referenced_add__1_0
(
	if_referenced_t *referenced
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(referenced->version, IF_REFERENCED_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return referenced->ops->op_add(referenced);
}
