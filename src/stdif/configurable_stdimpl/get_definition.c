/*
 * @(#) stdif/configurable_stdimpl/get_definition.c
 *
 * Configurable Interface - get_definition@1.0 standard implementation.
 *
 * Copyright (c) 2017-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


/**
 * Standard implementation to get the property definition from a property
 * reference.
 *
 * @note	If @{param prop} was not obtained from this
 *		@{param configurable}, then the results are undefined.
 *
 * @note	The definition returned is guaranteed to be valid as long
 *		as the @{param configurable} is valid.
 *
 * @param	conf		The configurable instance.
 * @param	prop		The property reference.
 *
 * @return	The property definition.
 *
 * @since	1.0
 */
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
