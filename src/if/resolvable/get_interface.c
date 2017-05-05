/*
 * @(#) if/resolvable/get_interface.c
 *
 * Resolvable Interface client API wrappers.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <iv/base.h>
#include <extit/base.h>
#include <if/resolvable.h>
#include <if/resolvable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
void *
EXTIT_DECL
if_resolvable_get_interface__1_0
(
	if_resolvable_t *resolvable,
	const char *id,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(resolvable->version, IF_RESOLVABLE_ABI_1_0))
		return NULL;
#endif

	return resolvable->ops->op_get_interface(resolvable, id, version);
}
