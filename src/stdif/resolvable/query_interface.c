/*
 * @(#) stdif/resolvable/query_interface.c
 *
 * Resolvable Interface - query_interface@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <iv/base.h>
#include <extit/base.h>
#include <stdif/resolvable.h>
#include <stdif/resolvable_impl.h>

#ifdef	STDIF_PARANOID
#include <iv/util.h>
#endif


/**
 * Query a supported interface version.
 *
 * This is a convenience function that calls
 * @{param resolvable}@{code ->ops->v0.op_query_interface( ... )}
 *
 * @param	resolvable	The resolvable instance.
 * @param	id		The interface ID (IID).
 * @param	base_version	The base interface version.
 *
 * @return	The highest supported version that is compatible with
 * 		the @{param base_version}, or @{constant IV_VERSION_NONE}
 *		if none found or an error occured.
 *
 * @since	1.0
 */
iv_version_t
EXTIT_DECL
stdif_resolvable_query_interface__1_0
(
	stdif_resolvable_t *resolvable,
	const char *id,
	iv_version_t base_version
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(resolvable->version, STDIF_RESOLVABLE_ABI_1_0))
		return IV_VERSION_NONE;
#endif

#define	IMPL(x)		((stdif_resolvable_1_0_t *) (x))

	return IMPL(resolvable)->ops->v0.op_query_interface(
		IMPL(resolvable), id, base_version);

#undef	IMPL
}
