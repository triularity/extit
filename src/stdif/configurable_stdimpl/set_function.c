/*
 * @(#) stdif/configurable_stdimpl/set_function.c
 *
 * Configurable Interface - set_function@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


/**
 * Standard implementation to set a property value as a function pointer.
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	If the value set does not match the interface and version
 *		defined by the property then implementation is undefined.
 *
 * @note	This implementation stores @{param value} to
 *		@{param configurable} @{code +} @{param prop}@{code ->offset}
 *		as the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_FUNCTION}
 *
 * @param	configurable	The configurable instance.
 * @param	prop		The property reference.
 * @param	value		The new value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_get_function__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, extit_func_t *)}
 * @see		@{func stdif_configurable_stdimpl_set_function__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, extit_func_t)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_function__1_0
(
	stdif_configurable_1_0_t *configurable,
	stdif_configurable_propref_t *prop,
	extit_func_t value
)
{
	return stdif_configurable_stdimpl_set_function__1_0_base(
		configurable, configurable, prop, value);
}


/**
 * Standard implementation helper to set a property value as a function
 * pointer.
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	If the value set does not match the interface and version
 *		defined by the property then implementation is undefined.
 *
 * @note	This implementation stores @{param value} to
 *		@{param base} @{code +} @{param prop}@{code ->offset}
 *		as the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_FUNCTION}
 *
 * @param	configurable	The configurable instance.
 * @param	base		The base address.
 * @param	prop		The property reference.
 * @param	value		The new value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_get_function__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, extit_func_t *)}
 * @see		@{func stdif_configurable_stdimpl_set_function__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, extit_func_t)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_function__1_0_base
(
	stdif_configurable_1_0_t *configurable,
	void *base,
	stdif_configurable_propref_t *prop,
	extit_func_t value
)
{
	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_FUNCTION:
			*((extit_func_t *) base) = value;
			break;

		default:
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	if(prop->update_notifier != NULL)
	{
		prop->update_notifier(
			(stdif_configurable_t *) configurable, prop);
	}

	return EXTIT_STATUS_OK;
}
