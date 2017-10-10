/*
 * @(#) if/configurable_util/fprint_property.c
 *
 * Print a configurable interface property value.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <iv/base.h>
#include <extit/platform.h>

#include <if/configurable.h>
#include <if/configurable_impl.h>
#include <if/configurable_util.h>


extit_status_t
EXTIT_DECL
_if_configurable_fprint_property
(
	FILE *fp,
	if_configurable_t *conf,
	if_configurable_type_t type,
	const char *id
)
{
	if_configurable_propref_t *	prop;
	if_configurable_1_0_t *		conf_1_0;


	/*
	 * For now, just 1.0 supported
	 */
	if(conf->version != IF_CONFIGURABLE_ABI_1_0)
		return EXTIT_STATUS_UNSUPPORTED;

	conf_1_0 = (if_configurable_1_0_t *) conf;

	if((prop = conf_1_0->ops->v0.op_find_property(conf_1_0, id)) == NULL)
		return EXTIT_STATUS_NOTFOUND;

	return _if_configurable_fprint_property__1_0(fp, conf_1_0, type, prop);
}


extit_status_t
EXTIT_DECL
_if_configurable_fprint_property__1_0
(
	FILE *fp,
	if_configurable_1_0_t *conf,
	if_configurable_type_t type,
	if_configurable_propref_t *prop
)
{
	extit_status_t	status;


	switch(type)
	{
		case IF_CONFIGURABLE_TYPE_BOOL:
		{
			extit_bool_t	value;


			if((status = conf->ops->v0.op_get_bool(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%s",
				value ? "EXTIT_TRUE" : "EXTIT_FALSE");

			break;
		}

		case IF_CONFIGURABLE_TYPE_DATA:
		{
			void *		value;


			if((status = conf->ops->v0.op_get_data(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "0x%0*" PRIxPTR,
				(int) sizeof(uintptr_t) * 2,
				(uintptr_t) value);

			break;
		}

		case IF_CONFIGURABLE_TYPE_DOUBLE:
		{
			double		value;


			if((status = conf->ops->v0.op_get_double(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%f", value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_ENUM32:
		{
			uint32_t	value;


			if((status = conf->ops->v0.op_get_enum32(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%xxxxx", value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_FLOAT:
		{
			float		value;


			if((status = conf->ops->v0.op_get_float(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%f", value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_FUNCTION:
		{
			extit_func_t	value;


			if((status = conf->ops->v0.op_get_function(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "0x%0*" PRIxPTR,
				(int) sizeof(extit_func_t) * 2,
				(uintptr_t) value);

			break;
		}

		case IF_CONFIGURABLE_TYPE_INT8:
		{
			int8_t		value;


			if((status = conf->ops->v0.op_get_int8(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%d", value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_INT16:
		{
			int16_t		value;


			if((status = conf->ops->v0.op_get_int16(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%d", value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_INT32:
		{
			int32_t		value;


			if((status = conf->ops->v0.op_get_int32(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%" PRId32, value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_INT64:
		{
			int64_t		value;


			if((status = conf->ops->v0.op_get_int64(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%" PRId64, value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_UINT8:
		{
			uint8_t		value;


			if((status = conf->ops->v0.op_get_uint8(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%u", value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_UINT16:
		{
			uint16_t	value;


			if((status = conf->ops->v0.op_get_uint16(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%u", value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_UINT32:
		{
			uint32_t	value;


			if((status = conf->ops->v0.op_get_uint32(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%" PRIu32, value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_UINT64:
		{
			uint64_t	value;


			if((status = conf->ops->v0.op_get_uint64(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%" PRIu64, value);
			break;
		}

		case IF_CONFIGURABLE_TYPE_UTF8:
		{
			const char *	value;


			if((status = conf->ops->v0.op_get_utf8(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			if(value != NULL)
			{
				_if_configurable_fprint_utf8(
					fp, value, EXTIT_TRUE);
			}
			else
			{
				fprintf(fp, "NULL");
			}

			break;
		}

		default:
			return EXTIT_STATUS_UNSUPPORTED;
	}

	return EXTIT_STATUS_OK;
}
