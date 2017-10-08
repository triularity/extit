/*
 * @(#) if/configurable/get_function.c
 *
 * Configurable Interface - get_function@1.0 wrapper.
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
if_configurable_get_function__1_0
(
	if_configurable_t *configurable,
	if_configurable_propref_t *prop,
	extit_func_t *valuep
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(configurable->version, IF_CONFIGURABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((if_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_get_function(
		IMPL(configurable), prop, valuep);

#undef	IMPL
}
