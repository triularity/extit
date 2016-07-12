/*
 * @(#) extit/if_configurable_stdimpl/set_float.c
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
extit_if_configurable_set_float_stdimpl
(
	extit_if_configurable_t *conf,
	extit_if_configurable_propref_t *prop,
	float value
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, EXTIT_IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return extit_if_configurable_set_float_stdimpl_base(
		conf, prop, value);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_configurable_set_float_stdimpl_base
(
	void *base,
	extit_if_configurable_propref_t *prop,
	float value
)
{
	extit_if_configurable_propspec_double_t *	spec_double;
	extit_if_configurable_propspec_float_t *	spec_float;


	if(prop->setter != NULL)
		return prop->setter(base, prop, &value);

	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case EXTIT_IF_CONFIGURABLE_TYPE_DOUBLE:
			spec_double = &prop->definition.spec.type_double;

			if((value < spec_double->min_value)
			 || (value > spec_double->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((double *) base) = value;
			break;

		case EXTIT_IF_CONFIGURABLE_TYPE_FLOAT:
			spec_float = &prop->definition.spec.type_float;

			if((value < spec_float->min_value)
			 || (value > spec_float->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((float *) base) = value;
			break;

		default:
			return EXTIT_IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
