/*
 * @(#) if/configurable/get_uint16.c
 *
 * Configurable Interface client API wrappers.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_get_uint16__1_0
(
	if_configurable_t *configurable,
	if_configurable_propref_t *prop,
	uint16_t *valuep
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(configurable->version, IF_CONFIGURABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return configurable->ops->v0.op_get_uint16(configurable, prop, valuep);
}
