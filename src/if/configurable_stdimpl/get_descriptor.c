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


const if_configurable_descriptor_t *
EXTIT_DECL
if_configurable_stdimpl_get_descriptor__1_0
(
	if_configurable_1_0_t *conf
)
{
#define	IMPL(x)		((if_configurable_stdimpl_1_0_t *) (x))

	return IMPL(conf)->descriptor;

#undef	IMPL
}
