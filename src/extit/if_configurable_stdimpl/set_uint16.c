/*
 * @(#) extit/if/configurable_stdimpl/set_uint16.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <extit/if/configurable.h>
#include <extit/if/configurable_impl.h>
#include <extit/if/configurable_stdimpl.h>

#ifdef  EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_configurable_set_uint16_stdimpl
(
	extit_if_configurable_t *conf,
	extit_if_configurable_propref_t *prop,
	uint16_t value
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, EXTIT_IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return extit_if_configurable_set_uint16_stdimpl_base(
		conf, prop, value);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_configurable_set_uint16_stdimpl_base
(
	void *base,
	extit_if_configurable_propref_t *prop,
	uint16_t value
)
{
	extit_if_configurable_propspec_uint16_t *	spec_uint16;
	extit_if_configurable_propspec_uint32_t *	spec_uint32;
	extit_if_configurable_propspec_uint64_t *	spec_uint64;


	if(prop->setter != NULL)
		return prop->setter(base, prop, &value);

	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case EXTIT_IF_CONFIGURABLE_TYPE_UINT16:
			spec_uint16 = &prop->definition.spec.type_uint16;

			if((value < spec_uint16->min_value)
			 || (value > spec_uint16->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((uint16_t *) base) = value;
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_UINT32:
			spec_uint32 = &prop->definition.spec.type_uint32;

			if((value < spec_uint32->min_value)
			 || (value > spec_uint32->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((uint32_t *) base) = value;
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_UINT64:
			spec_uint64 = &prop->definition.spec.type_uint64;

			if((value < spec_uint64->min_value)
			 || (value > spec_uint64->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((uint64_t *) base) = value;
			break;

		default:
			return EXTIT_IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
