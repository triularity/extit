/*
 * @(#) if/configurable/get_uint64.c
 *
 * Configurable Interface - get_uint64@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


extit_status_t
EXTIT_DECL
if_configurable_get_uint64__1_0
(
	if_configurable_t *configurable,
	if_configurable_propref_t *prop,
	uint64_t *valuep
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(configurable->version, IF_CONFIGURABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((if_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_get_uint64(
		IMPL(configurable), prop, valuep);

#undef	IMPL
}
