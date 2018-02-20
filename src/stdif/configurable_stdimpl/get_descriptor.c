/*
 * @(#) stdif/configurable_stdimpl/get_descriptor.c
 *
 * Configurable Interface - get_descriptor@1.0 standard implementation.
 *
 * Copyright (c) 2017-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


/**
 * Standard implementation to get the configurable descriptor.
 * This descriptor contains a list of all properties supported by this
 * configurable.
 *
 * @note	The definition returned is guaranteed to be valid as long
 *		as the @{param conf} is valid.
 *
 * @param	conf		The configurable instance.
 *
 * @return	The configurable descriptor.
 *
 * @since	1.0
 */
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
