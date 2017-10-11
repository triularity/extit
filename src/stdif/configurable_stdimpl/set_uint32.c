/*
 * @(#) stdif/configurable_stdimpl/set_uint32.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>
#include <stdif/configurable_util.h>


extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_uint32__1_0
(
	stdif_configurable_1_0_t *conf,
	stdif_configurable_propref_t *prop,
	uint32_t value
)
{
	return stdif_configurable_stdimpl_set_uint32__1_0_base(
		conf, conf, prop, value);
}


extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_uint32__1_0_base
(
	stdif_configurable_1_0_t *conf,
	void *base,
	stdif_configurable_propref_t *prop,
	uint32_t value
)
{
	stdif_configurable_propspec_enum32_t *	spec_enum32;
	stdif_configurable_propspec_uint32_t *	spec_uint32;
	stdif_configurable_propspec_uint64_t *	spec_uint64;


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
		prop->update_notifier((stdif_configurable_t *) conf, prop);

	return EXTIT_STATUS_OK;
}
