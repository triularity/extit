/*
 * @(#) if/configurable/get_descriptor.c
 *
 * Configurable Interface - get_descriptor@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


const if_configurable_descriptor_t *
EXTIT_DECL
if_configurable_get_descriptor__1_0
(
	if_configurable_t *configurable
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(configurable->version, IF_CONFIGURABLE_ABI_1_0))
		return NULL;
#endif

#define	IMPL(x)		((if_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_get_descriptor(
		IMPL(configurable));

#undef	IMPL
}
