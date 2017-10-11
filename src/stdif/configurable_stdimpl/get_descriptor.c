/*
 * @(#) stdif/configurable_stdimpl/get_descriptor.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


const stdif_configurable_descriptor_t *
EXTIT_DECL
stdif_configurable_stdimpl_get_descriptor__1_0
(
	stdif_configurable_1_0_t *conf
)
{
#define	IMPL(x)		((stdif_configurable_stdimpl_1_0_t *) (x))

	return IMPL(conf)->descriptor;

#undef	IMPL
}
