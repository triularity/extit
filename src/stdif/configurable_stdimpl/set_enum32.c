/*
 * @(#) stdif/configurable_stdimpl/set_enum32.c
 *
 * Configurable Interface - set_enum32@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>
#include <stdif/configurable_util.h>


/**
 * Standard implementation to set a property value as an enum32 choice.
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation stores @{param value} to
 *		@{param conf} @{code +} @{param prop}@{code ->offset}
 *		as the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_ENUM32}
 *
 * @param	conf		The configurable instance.
 * @param	prop		The property reference.
 * @param	value		The new value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible,
 *		or @{constant EXTIT_STATUS_INVALID} if the value is not
 *		a defined choice for that property.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_get_enum32__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, uint32_t *)}
 * @see		@{func stdif_configurable_stdimpl_set_enum32__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, uint32_t)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_enum32__1_0
(
	stdif_configurable_1_0_t *conf,
	stdif_configurable_propref_t *prop,
	uint32_t value
)
{
	return stdif_configurable_stdimpl_set_enum32__1_0_base(
		conf, conf, prop, value);
}


/**
 * Standard implementation helper to set a property value as an enum32 choice.
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation stores @{param value} to
 *		@{param base} @{code +} @{param prop}@{code ->offset}
 *		as the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_ENUM32}
 *
 * @param	conf		The configurable instance.
 * @param	base		The base address.
 * @param	prop		The property reference.
 * @param	value		The new value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible,
 *		or @{constant EXTIT_STATUS_INVALID} if the value is not
 *		a defined choice for that property.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_get_enum32__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, uint32_t *)}
 * @see		@{func stdif_configurable_stdimpl_set_enum32__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, uint32_t)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_enum32__1_0_base
(
	stdif_configurable_1_0_t *conf,
	void *base,
	stdif_configurable_propref_t *prop,
	uint32_t value
)
{
	stdif_configurable_propspec_enum32_t *	spec_enum32;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_ENUM32:
			spec_enum32 = &prop->definition.spec.type_enum32;

			if(stdif_configurable_enum32_find_by_value(
			 spec_enum32->choices, spec_enum32->choice_count,
			 value) == NULL)
			{
				return EXTIT_STATUS_INVALID;
			}

			*((uint32_t *) base) = value;
			break;

		default:
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	if(prop->update_notifier != NULL)
		prop->update_notifier((stdif_configurable_t *) conf, prop);

	return EXTIT_STATUS_OK;
}
