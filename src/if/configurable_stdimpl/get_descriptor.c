/*
 * @(#) if/configurable_stdimpl/get_descriptor.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>
#include <if/configurable_stdimpl.h>

#ifdef  EXTIT_PARANOID
#include <iv/util.h>
#endif


const if_configurable_descriptor_t *
EXTIT_DECL
if_configurable_stdimpl_get_descriptor__1_0
(
	if_configurable_1_0_t *conf
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return NULL;
#endif

	return conf->descriptor;
}
