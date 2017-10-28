/*
 * @(#) stdif/configurable_util/fprint_property.c
 *
 * Print a configurable interface property value.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

#include <iv/base.h>
#include <extit/platform.h>

#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_util.h>


extit_status_t
EXTIT_DECL
_stdif_configurable_fprint_property
(
	FILE *fp,
	stdif_configurable_t *conf,
	stdif_configurable_type_t type,
	const char *id
)
{
	stdif_configurable_propref_t *	prop;
	stdif_configurable_1_0_t *	conf_1_0;


	/*
	 * For now, just 1.0 supported
	 */
	if(conf->version != STDIF_CONFIGURABLE_ABI_1_0)
		return EXTIT_STATUS_UNSUPPORTED;

	conf_1_0 = (stdif_configurable_1_0_t *) conf;

	if((prop = conf_1_0->ops->v0.op_find_property(conf_1_0, id)) == NULL)
		return EXTIT_STATUS_NOTFOUND;

	return _stdif_configurable_fprint_property__1_0(fp, conf_1_0, type, prop);
}


extit_status_t
EXTIT_DECL
_stdif_configurable_fprint_property__1_0
(
	FILE *fp,
	stdif_configurable_1_0_t *conf,
	stdif_configurable_type_t type,
	stdif_configurable_propref_t *prop
)
{
	extit_status_t	status;


	switch(type)
	{
		case STDIF_CONFIGURABLE_TYPE_BOOL:
		{
			bool		value;


			if((status = conf->ops->v0.op_get_bool(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			fprintf(fp, "%s", value ? "true" : "false");

			break;
		}

		case STDIF_CONFIGURABLE_TYPE_DATA:
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

		case STDIF_CONFIGURABLE_TYPE_DOUBLE:
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

		case STDIF_CONFIGURABLE_TYPE_ENUM32:
		{
			uint32_t				value;
			const stdif_configurable_propdef_t *	propdef;
			const stdif_configurable_enum32_t *	enum32;


			if((status = conf->ops->v0.op_get_enum32(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			propdef = conf->ops->v0.op_get_definition(conf, prop);

			enum32 = stdif_configurable_enum32_find_by_value(
				propdef->spec.type_enum32.choices,
				propdef->spec.type_enum32.choice_count,
				value);

			if(enum32 != NULL)
				fprintf(fp, "%s", enum32->id);
			else
				fprintf(fp, "%" PRIu32 " (unmapped)", value);

			break;
		}

		case STDIF_CONFIGURABLE_TYPE_FLOAT:
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

		case STDIF_CONFIGURABLE_TYPE_FUNCTION:
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

		case STDIF_CONFIGURABLE_TYPE_INT8:
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

		case STDIF_CONFIGURABLE_TYPE_INT16:
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

		case STDIF_CONFIGURABLE_TYPE_INT32:
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

		case STDIF_CONFIGURABLE_TYPE_INT64:
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

		case STDIF_CONFIGURABLE_TYPE_UINT8:
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

		case STDIF_CONFIGURABLE_TYPE_UINT16:
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

		case STDIF_CONFIGURABLE_TYPE_UINT32:
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

		case STDIF_CONFIGURABLE_TYPE_UINT64:
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

		case STDIF_CONFIGURABLE_TYPE_UTF8:
		{
			const char *	value;


			if((status = conf->ops->v0.op_get_utf8(
			 conf, prop, &value)) != EXTIT_STATUS_OK)
			{
				return status;
			}

			if(value != NULL)
			{
				_stdif_configurable_fprint_utf8(
					fp, value, true);
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
