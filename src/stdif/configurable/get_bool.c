/*
 * @(#) stdif/configurable/get_bool.c
 *
 * Configurable Interface - get_bool@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdbool.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


/**
 * Get a property value as a boolean.
 *
 * This is a convenience function that calls
 * @{param configurable}@{code ->ops->v0.op_get_bool( ... )}
 *
 * @note	The contents of memory referenced by @{param valuep}
 *		will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @param	configurable	The configurable instance.
 * @param	prop		The property reference.
 * @param	valuep		The address to store the value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible.
 *
 * @since	1.0
 *
 * @see         @{func stdif_configurable_set_bool__1_0(stdif_configurable_t *, stdif_configurable_propref_t *, bool)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_get_bool__1_0
(
	stdif_configurable_t *configurable,
	stdif_configurable_propref_t *prop,
	bool *valuep
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(configurable->version, STDIF_CONFIGURABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_get_bool(
		IMPL(configurable), prop, valuep);

#undef	IMPL
}
