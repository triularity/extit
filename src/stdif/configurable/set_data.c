/*
 * @(#) stdif/configurable/set_data.c
 *
 * Configurable Interface - set_data@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>

#ifdef	STDIF_PARANOID
#include <iv/util.h>
#endif


/**
 * Set a property value as a data pointer.
 *
 * This is a convenience function that calls
 * @{param configurable}@{code ->ops->v0.op_set_data( ... )}
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	If @{param value} does not match the interface and version
 *		defined by the property then usage will be undefined.
 *
 * @note	Unless otherwise specified by the object implementing
 *		the @{param configurable}, the pointer reference will
 *		persist and should remain valid until the property value
 *		is changed or the instance is destroyed.
 *
 * @param	configurable	The configurable instance.
 * @param	prop		The property reference.
 * @param	value		The new value, or @{constant NULL}.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_get_data__1_0(stdif_configurable_t *, stdif_configurable_propref_t *, void **)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_set_data__1_0
(
	stdif_configurable_t *configurable,
	stdif_configurable_propref_t *prop,
	void *value
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(configurable->version, STDIF_CONFIGURABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_set_data(
		IMPL(configurable), prop, value);

#undef	IMPL
}
