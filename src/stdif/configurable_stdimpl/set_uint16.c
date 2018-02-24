/*
 * @(#) stdif/configurable_stdimpl/set_uint16.c
 *
 * Configurable Interface - set_uint16@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>
#include <stdif/configurable_util.h>


/**
 * Standard implementation to set a property value as an unsigned
 * 16-bit integer.
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation stores @{param value} to
 *		@{param configurable} @{code +} @{param prop}@{code ->offset}
 *		as the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_ENUM32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT8},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT16},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT64},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT8},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT16},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT64}.
 *
 * @param	configurable	The configurable instance.
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
 * @see		@{func stdif_configurable_stdimpl_get_uint16__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, uint16_t *)}
 * @see		@{func stdif_configurable_stdimpl_set_uint16__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, uint16_t)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_uint16__1_0
(
	stdif_configurable_1_0_t *configurable,
	stdif_configurable_propref_t *prop,
	uint16_t value
)
{
	return stdif_configurable_stdimpl_set_uint16__1_0_base(
		configurable, configurable, prop, value);
}


/**
 * Standard implementation helper to set a property value as an unsigned
 * 16-bit integer.
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation stores @{param value} to
 *		@{param base} @{code +} @{param prop}@{code ->offset}
 *		as the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_ENUM32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT8},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT16},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT64},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT8},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT16},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT64}.
 *
 * @param	configurable	The configurable instance.
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
 * @see		@{func stdif_configurable_stdimpl_get_uint16__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, uint16_t *)}
 * @see		@{func stdif_configurable_stdimpl_set_uint16__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, uint16_t)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_uint16__1_0_base
(
	stdif_configurable_1_0_t *configurable,
	void *base,
	stdif_configurable_propref_t *prop,
	uint16_t value
)
{
	stdif_configurable_propspec_enum32_t *	spec_enum32;
	stdif_configurable_propspec_int8_t *	spec_int8;
	stdif_configurable_propspec_int16_t *	spec_int16;
	stdif_configurable_propspec_int32_t *	spec_int32;
	stdif_configurable_propspec_int64_t *	spec_int64;
	stdif_configurable_propspec_uint8_t *	spec_uint8;
	stdif_configurable_propspec_uint16_t *	spec_uint16;
	stdif_configurable_propspec_uint32_t *	spec_uint32;
	stdif_configurable_propspec_uint64_t *	spec_uint64;
	int8_t		value_i8;
	int16_t		value_i16;
	int32_t		value_i32;
	int64_t		value_i64;


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

		case STDIF_CONFIGURABLE_TYPE_INT8:
			if(value > (uint16_t) INT8_MAX)
				return EXTIT_STATUS_INVALID;

			value_i8 = (int8_t) value;

			spec_int8 = &prop->definition.spec.type_int8;

			if((value_i8 < spec_int8->min_value)
			 || (value_i8 > spec_int8->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((int8_t *) base) = value_i8;
			break;

		case STDIF_CONFIGURABLE_TYPE_INT16:
			if(value > (uint16_t) INT16_MAX)
				return EXTIT_STATUS_INVALID;

			value_i16 = (int16_t) value;

			spec_int16 = &prop->definition.spec.type_int16;

			if((value_i16 < spec_int16->min_value)
			 || (value_i16 > spec_int16->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((int16_t *) base) = value_i16;
			break;

		case STDIF_CONFIGURABLE_TYPE_INT32:
			value_i32 = (int32_t) value;

			spec_int32 = &prop->definition.spec.type_int32;

			if((value_i32 < spec_int32->min_value)
			 || (value_i32 > spec_int32->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((int32_t *) base) = value_i32;
			break;

		case STDIF_CONFIGURABLE_TYPE_INT64:
			value_i64 = (int64_t) value;

			spec_int64 = &prop->definition.spec.type_int64;

			if((value_i64 < spec_int64->min_value)
			 || (value_i64 > spec_int64->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((int64_t *) base) = value_i64;
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT8:
			spec_uint8 = &prop->definition.spec.type_uint8;

			if((value < spec_uint8->min_value)
			 || (value > spec_uint8->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((uint8_t *) base) = (uint8_t) value;
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT16:
			spec_uint16 = &prop->definition.spec.type_uint16;

			if((value < spec_uint16->min_value)
			 || (value > spec_uint16->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((uint16_t *) base) = value;
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT32:
			spec_uint32 = &prop->definition.spec.type_uint32;

			if((value < spec_uint32->min_value)
			 || (value > spec_uint32->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((uint32_t *) base) = value;
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT64:
			spec_uint64 = &prop->definition.spec.type_uint64;

			if((value < spec_uint64->min_value)
			 || (value > spec_uint64->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((uint64_t *) base) = value;
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
