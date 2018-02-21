/*
 * @(#) stdif/configurable_stdimpl/reset.c
 *
 * Configurable Interface - reset@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


/**
 * Reset a property to its default value.
 *
 * @param	configurable	The configurable instance.
 * @param	prop		The property reference.
 *
 * @return	@{constant EXTIT_STATUS_OK} all properties where reset
 *		successfully, otherwise a @{constant EXTIT_STATUS_}*
 *		value returned by the failing property setter.
 *
 * @since	1.0
 */
static
extit_status_t
reset_prop
(
	stdif_configurable_1_0_t *configurable,
	stdif_configurable_propref_t *prop
)
{
	extit_status_t	status;


	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_DATA:
			status = configurable->ops->v0.op_set_data(
				configurable,
				prop,
				prop->definition.spec.type_data.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_BOOL:
			status = configurable->ops->v0.op_set_bool(
				configurable,
				prop,
				prop->definition.spec.type_bool.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_DOUBLE:
			status = configurable->ops->v0.op_set_double(
				configurable,
				prop,
				prop->definition.spec.type_double.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_ENUM32:
			status = configurable->ops->v0.op_set_enum32(
				configurable,
				prop,
				prop->definition.spec.type_enum32.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_FLOAT:
			status = configurable->ops->v0.op_set_float(
				configurable,
				prop,
				prop->definition.spec.type_float.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_FUNCTION:
			status = configurable->ops->v0.op_set_function(
				configurable,
				prop,
				prop->definition.spec.type_function.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT8:
			status = configurable->ops->v0.op_set_int8(
				configurable,
				prop,
				prop->definition.spec.type_int8.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT16:
			status = configurable->ops->v0.op_set_int16(
				configurable,
				prop,
				prop->definition.spec.type_int16.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT32:
			status = configurable->ops->v0.op_set_int32(
				configurable,
				prop,
				prop->definition.spec.type_int32.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT64:
			status = configurable->ops->v0.op_set_int64(
				configurable,
				prop,
				prop->definition.spec.type_int64.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT8:
			status = configurable->ops->v0.op_set_uint8(
				configurable,
				prop,
				prop->definition.spec.type_uint8.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT16:
			status = configurable->ops->v0.op_set_uint16(
				configurable,
				prop,
				prop->definition.spec.type_uint16.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT32:
			status = configurable->ops->v0.op_set_uint32(
				configurable,
				prop,
				prop->definition.spec.type_uint32.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT64:
			status = configurable->ops->v0.op_set_uint64(
				configurable,
				prop,
				prop->definition.spec.type_uint64.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_UTF8:
			status = configurable->ops->v0.op_set_utf8(
				configurable,
				prop,
				prop->definition.spec.type_utf8.def_value);
			break;

		default:
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return status;
}


/**
 * Standard implementation to reset all properties to their default values.
 *
 * @note	This implementation iterates though all the properties in
 *		the @{param configurable}'s descriptor and call the appropriete
 *		type setter with that property's default value.
 *
 * @note	The @{param configurable} may be left in a partially reset
 *		state if this function fails.
 *
 * @param	configurable	The configurable instance.
 *
 * @return	@{constant EXTIT_STATUS_OK} all properties where reset
 *		successfully, otherwise a @{constant EXTIT_STATUS_}*
 *		value returned by the failing property setter.
 *
 * @since	1.0
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_reset__1_0
(
	stdif_configurable_1_0_t *configurable
)
{
	const stdif_configurable_descriptor_t *	descriptor;
	const stdif_configurable_propdef_t **	props;
	uint32_t				count;
	extit_status_t				status;


	descriptor = configurable->ops->v0.op_get_descriptor(configurable);

	props = descriptor->properties;
	count = descriptor->count;

	while(count-- != 0)
	{
		if((status = reset_prop(
		 configurable, (stdif_configurable_propref_t *) *props))
		 != EXTIT_STATUS_OK)
		{
			return status;
		}

		props++;
	}

	return EXTIT_STATUS_OK;
}
