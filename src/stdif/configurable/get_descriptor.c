/*
 * @(#) stdif/configurable/get_descriptor.c
 *
 * Configurable Interface - get_descriptor@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>

#ifdef	STDIF_PARANOID
#include <iv/util.h>
#endif


/**
 * Get the configurable descriptor.
 * This descriptor contains a list of all properties supported by this
 * configurable.
 *
 * This is a convenience function that calls
 * @{param configurable}@{code ->ops->v0.op_get_descriptor( ... )}
 *
 * @note	The definition returned is guaranteed to be valid as long
 *		as the @{param configurable} is valid.
 *
 * @param	configurable	The configurable instance.
 *
 * @return	The configurable descriptor.
 *
 * @since	1.0
 */
const stdif_configurable_descriptor_t *
EXTIT_DECL
stdif_configurable_get_descriptor__1_0
(
	stdif_configurable_t *configurable
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(configurable->version, STDIF_CONFIGURABLE_ABI_1_0))
		return NULL;
#endif

#define	IMPL(x)		((stdif_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_get_descriptor(
		IMPL(configurable));

#undef	IMPL
}
