/*
 * @(#) extit/if/resolvable.c
 *
 * Resolvable Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/if/resolvable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
void *
EXTIT_DECL
extit_if_resolvable_get_interface
(
	extit_if_resolvable_t *resolvable,
	const char *id,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(resolvable->version, EXTIT_IF_RESOLVABLE_VERSION_1_0))
		return NULL;
#endif

	return EXTIT_IF_RESOLVABLE_GET_INTERFACE(resolvable, id, version);
}


EXTIT_EXPORT
iv_version_t
EXTIT_DECL
extit_if_resolvable_query_interface
(
	extit_if_resolvable_t *resolvable,
	const char *id,
	iv_version_t base_version
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(resolvable->version, EXTIT_IF_RESOLVABLE_VERSION_1_0))
		return IV_VERSION_NONE;
#endif

	return EXTIT_IF_RESOLVABLE_QUERY_INTERFACE(
		resolvable, id, base_version);
}
