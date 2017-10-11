/*
 * @(#) stdif/configurable/find_property.c
 *
 * Configurable Interface - find_property@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


stdif_configurable_propref_t *
EXTIT_DECL
stdif_configurable_find_property__1_0
(
	stdif_configurable_t *configurable,
	const char *id
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(configurable->version, STDIF_CONFIGURABLE_ABI_1_0))
		return NULL;
#endif

#define	IMPL(x)		((stdif_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_find_property(
		IMPL(configurable), id);

#undef	IMPL
}
