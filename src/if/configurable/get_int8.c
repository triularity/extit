/*
 * @(#) if/configurable/get_int8.c
 *
 * Configurable Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
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
if_configurable_get_int8
(
	if_configurable_t *configurable,
	if_configurable_propref_t *prop,
	int8_t *valuep
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(configurable->version, IF_CONFIGURABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return IF_CONFIGURABLE_GET_INT8(configurable, prop, valuep);
}
