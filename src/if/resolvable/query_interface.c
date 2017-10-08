/*
 * @(#) if/resolvable/query_interface.c
 *
 * Resolvable Interface - query_interface@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
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


iv_version_t
EXTIT_DECL
if_resolvable_query_interface__1_0
(
	if_resolvable_t *resolvable,
	const char *id,
	iv_version_t base_version
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(resolvable->version, IF_RESOLVABLE_ABI_1_0))
		return IV_VERSION_NONE;
#endif

#define	IMPL(x)		((if_resolvable_1_0_t *) (x))

	return IMPL(resolvable)->ops->v0.op_query_interface(
		IMPL(resolvable), id, base_version);

#undef	IMPL
}
