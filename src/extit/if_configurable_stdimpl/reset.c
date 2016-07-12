/*
 * @(#) extit/if/configurable_stdimpl/reset.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/if/configurable.h>
#include <extit/if/configurable_impl.h>
#include <extit/if/configurable_stdimpl.h>

#ifdef  EXTIT_PARANOID
#include <iv/util.h>
#endif


static
extit_status_t
reset_prop
(
	extit_if_configurable_t *conf,
	extit_if_configurable_propref_t *prop
)
{
	extit_status_t	status;


	switch(prop->definition.type)
	{
		case EXTIT_IF_CONFIGURABLE_TYPE_CUSTOM:
			status = EXTIT_IF_CONFIGURABLE_SET_CUSTOM(
				conf,
				prop,
				prop->definition.spec.type_custom.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_BOOL:
			status = EXTIT_IF_CONFIGURABLE_SET_BOOL(
				conf,
				prop,
				prop->definition.spec.type_bool.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_DOUBLE:
			status = EXTIT_IF_CONFIGURABLE_SET_DOUBLE(
				conf,
				prop,
				prop->definition.spec.type_double.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_ENUM32:
			status = EXTIT_IF_CONFIGURABLE_SET_ENUM32(
				conf,
				prop,
				prop->definition.spec.type_enum32.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_FLOAT:
			status = EXTIT_IF_CONFIGURABLE_SET_FLOAT(
				conf,
				prop,
				prop->definition.spec.type_float.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_INT8:
			status = EXTIT_IF_CONFIGURABLE_SET_INT8(
				conf,
				prop,
				prop->definition.spec.type_int8.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_INT16:
			status = EXTIT_IF_CONFIGURABLE_SET_INT16(
				conf,
				prop,
				prop->definition.spec.type_int16.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_INT32:
			status = EXTIT_IF_CONFIGURABLE_SET_INT32(
				conf,
				prop,
				prop->definition.spec.type_int32.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_INT64:
			status = EXTIT_IF_CONFIGURABLE_SET_INT64(
				conf,
				prop,
				prop->definition.spec.type_int64.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_UINT8:
			status = EXTIT_IF_CONFIGURABLE_SET_UINT8(
				conf,
				prop,
				prop->definition.spec.type_uint8.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_UINT16:
			status = EXTIT_IF_CONFIGURABLE_SET_UINT16(
				conf,
				prop,
				prop->definition.spec.type_uint16.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_UINT32:
			status = EXTIT_IF_CONFIGURABLE_SET_UINT32(
				conf,
				prop,
				prop->definition.spec.type_uint32.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_UINT64:
			status = EXTIT_IF_CONFIGURABLE_SET_UINT64(
				conf,
				prop,
				prop->definition.spec.type_uint64.def_value);
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_UTF8:
			status = EXTIT_IF_CONFIGURABLE_SET_UTF8(
				conf,
				prop,
				prop->definition.spec.type_utf8.def_value);
			break;

		default:
                	return EXTIT_IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return status;
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_configurable_reset_stdimpl
(
	extit_if_configurable_t *conf
)
{
	const extit_if_configurable_descriptor_t *	descriptor;
	const extit_if_configurable_propdef_t **	props;
	uint32_t					count;
	extit_status_t					status;


#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, EXTIT_IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	descriptor = conf->descriptor;

	props = descriptor->properties;
	count = descriptor->count;

	while(count-- != 0)
	{
		if((status = reset_prop(
		 conf, (extit_if_configurable_propref_t *) *props))
		 != EXTIT_STATUS_OK)
		{
			return status;
		}

		props++;
	}

	return EXTIT_STATUS_OK;
}
