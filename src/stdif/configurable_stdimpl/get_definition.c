/*
 * @(#) stdif/configurable_stdimpl/get_definition.c
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


const stdif_configurable_propdef_t *
EXTIT_DECL
stdif_configurable_stdimpl_get_definition__1_0
(
	stdif_configurable_1_0_t *conf,
	stdif_configurable_propref_t *prop
)
{
	return &prop->definition;
}
