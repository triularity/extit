/*
 * @(#) stdif/resolvable/get_interface.c
 *
 * Resolvable Interface - get_interface@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <iv/base.h>
#include <extit/base.h>
#include <stdif/resolvable.h>
#include <stdif/resolvable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


void *
EXTIT_DECL
stdif_resolvable_get_interface__1_0
(
	stdif_resolvable_t *resolvable,
	const char *id,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(resolvable->version, STDIF_RESOLVABLE_ABI_1_0))
		return NULL;
#endif

#define	IMPL(x)		((stdif_resolvable_1_0_t *) (x))

	return IMPL(resolvable)->ops->v0.op_get_interface(
		IMPL(resolvable), id, version);

#undef	IMPL
}
