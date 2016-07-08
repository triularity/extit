/*
 * @(#) extit/if/resolvable/get_interface.c
 *
 * Resolvable Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/if/resolvable.h>
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
	if(!iv_matches(resolvable->version, EXTIT_IF_RESOLVABLE_ABI_1_0))
		return NULL;
#endif

	return EXTIT_IF_RESOLVABLE_GET_INTERFACE(resolvable, id, version);
}
