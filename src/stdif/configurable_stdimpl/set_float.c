/*
 * @(#) stdif/configurable_stdimpl/set_float.c
 *
 * Configurable Interface - set_float@1.0 standard implementation.
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
 * Standard implementation to set a property value as a 32-bit floating point.
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation stores @{param value} to
 *		@{param conf} @{code +} @{param prop}@{code ->offset}
 *		as the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_DOUBLE},
 *		@{constant STDIF_CONFIGURABLE_TYPE_FLOAT}
 *
 * @param	conf		The configurable instance.
 * @param	prop		The property reference.
 * @param	value		The new value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible,
 *		or @{constant EXTIT_STATUS_INVALID} if the value is out
 *		of valid range for that property.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_get_float__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, float *)}
 * @see		@{func stdif_configurable_stdimpl_set_float__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, float)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_float__1_0
(
	stdif_configurable_1_0_t *conf,
	stdif_configurable_propref_t *prop,
	float value
)
{
	return stdif_configurable_stdimpl_set_float__1_0_base(
		conf, conf, prop, value);
}


/**
 * Standard implementation helper to set a property value as a 32-bit
 * floating point.
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation stores @{param value} to
 *		@{param base} @{code +} @{param prop}@{code ->offset}
 *		as the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_DOUBLE},
 *		@{constant STDIF_CONFIGURABLE_TYPE_FLOAT}
 *
 * @param	conf		The configurable instance.
 * @param	base		The base address.
 * @param	prop		The property reference.
 * @param	value		The new value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible,
 *		or @{constant EXTIT_STATUS_INVALID} if the value is out
 *		of valid range for that property.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_get_float__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, float *)}
 * @see		@{func stdif_configurable_stdimpl_set_float__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, float)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_float__1_0_base
(
	stdif_configurable_1_0_t *conf,
	void *base,
	stdif_configurable_propref_t *prop,
	float value
)
{
	stdif_configurable_propspec_double_t *	spec_double;
	stdif_configurable_propspec_float_t *	spec_float;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_DOUBLE:
			spec_double = &prop->definition.spec.type_double;

			if((value < spec_double->min_value)
			 || (value > spec_double->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((double *) base) = value;
			break;

		case STDIF_CONFIGURABLE_TYPE_FLOAT:
			spec_float = &prop->definition.spec.type_float;

			if((value < spec_float->min_value)
			 || (value > spec_float->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((float *) base) = value;
			break;

		default:
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	if(prop->update_notifier != NULL)
		prop->update_notifier((stdif_configurable_t *) conf, prop);

	return EXTIT_STATUS_OK;
}
