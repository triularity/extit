/*
 * @(#) stdif/configurable_stdimpl/reset.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


static
extit_status_t
reset_prop
(
	stdif_configurable_1_0_t *conf,
	stdif_configurable_propref_t *prop
)
{
	extit_status_t	status;


	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_DATA:
			status = conf->ops->v0.op_set_data(
				conf,
				prop,
				prop->definition.spec.type_data.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_BOOL:
			status = conf->ops->v0.op_set_bool(
				conf,
				prop,
				prop->definition.spec.type_bool.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_DOUBLE:
			status = conf->ops->v0.op_set_double(
				conf,
				prop,
				prop->definition.spec.type_double.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_ENUM32:
			status = conf->ops->v0.op_set_enum32(
				conf,
				prop,
				prop->definition.spec.type_enum32.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_FLOAT:
			status = conf->ops->v0.op_set_float(
				conf,
				prop,
				prop->definition.spec.type_float.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_FUNCTION:
			status = conf->ops->v0.op_set_function(
				conf,
				prop,
				prop->definition.spec.type_function.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT8:
			status = conf->ops->v0.op_set_int8(
				conf,
				prop,
				prop->definition.spec.type_int8.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT16:
			status = conf->ops->v0.op_set_int16(
				conf,
				prop,
				prop->definition.spec.type_int16.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT32:
			status = conf->ops->v0.op_set_int32(
				conf,
				prop,
				prop->definition.spec.type_int32.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT64:
			status = conf->ops->v0.op_set_int64(
				conf,
				prop,
				prop->definition.spec.type_int64.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT8:
			status = conf->ops->v0.op_set_uint8(
				conf,
				prop,
				prop->definition.spec.type_uint8.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT16:
			status = conf->ops->v0.op_set_uint16(
				conf,
				prop,
				prop->definition.spec.type_uint16.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT32:
			status = conf->ops->v0.op_set_uint32(
				conf,
				prop,
				prop->definition.spec.type_uint32.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT64:
			status = conf->ops->v0.op_set_uint64(
				conf,
				prop,
				prop->definition.spec.type_uint64.def_value);
			break;

		case STDIF_CONFIGURABLE_TYPE_UTF8:
			status = conf->ops->v0.op_set_utf8(
				conf,
				prop,
				prop->definition.spec.type_utf8.def_value);
			break;

		default:
                	return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return status;
}


extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_reset__1_0
(
	stdif_configurable_1_0_t *conf
)
{
	const stdif_configurable_descriptor_t *	descriptor;
	const stdif_configurable_propdef_t **	props;
	uint32_t				count;
	extit_status_t				status;


	descriptor = conf->ops->v0.op_get_descriptor(conf);

	props = descriptor->properties;
	count = descriptor->count;

	while(count-- != 0)
	{
		if((status = reset_prop(
		 conf, (stdif_configurable_propref_t *) *props))
		 != EXTIT_STATUS_OK)
		{
			return status;
		}

		props++;
	}

	return EXTIT_STATUS_OK;
}
