/*
 * @(#) extit/if/configurable/get_int64.c
 *
 * Configurable Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/if/configurable.h>
#include <extit/if/configurable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_configurable_get_int64
(
	extit_if_configurable_t *configurable,
	extit_if_configurable_propref_t *prop,
	int64_t *valuep
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(configurable->version, EXTIT_IF_CONFIGURABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IF_CONFIGURABLE_GET_INT64(configurable, prop, valuep);
}
