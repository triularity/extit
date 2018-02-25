/*
 * @(#) stdif/configurable/get_definition.c
 *
 * Configurable Interface - get_definition@1.0 wrapper.
 *
 * Copyright (c) 2017-2018, Chad M. Fraleigh.  All rights reserved.
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
 * Get the property definition from a property reference.
 *
 * This is a convenience function that calls
 * @{param configurable}@{code ->ops->v0.op_get_definition( ... )}
 *
 * @note	If @{param prop} was not obtained from this
 *		@{param configurable}, then the results are undefined.
 *
 * @note	The definition returned is guaranteed to be valid as long
 *		as the @{param configurable} is valid.
 *
 * @param	configurable	The configurable instance.
 * @param	prop		The property reference.
 *
 * @return	The property definition.
 *
 * @since	1.0
 */
const stdif_configurable_propdef_t *
EXTIT_DECL
stdif_configurable_get_definition__1_0
(
	stdif_configurable_t *configurable,
	stdif_configurable_propref_t *prop
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(configurable->version, STDIF_CONFIGURABLE_ABI_1_0))
		return NULL;
#endif

#define	IMPL(x)		((stdif_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_get_definition(
		IMPL(configurable), prop);

#undef	IMPL
}
