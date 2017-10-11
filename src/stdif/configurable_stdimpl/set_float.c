/*
 * @(#) stdif/configurable_stdimpl/set_float.c
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
