/*
 * @(#) if/configurable_stdimpl/set_double.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>
#include <if/configurable_stdimpl.h>

#ifdef  EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_stdimpl_set_double__1_0
(
	if_configurable_1_0_t *conf,
	if_configurable_propref_t *prop,
	double value
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return if_configurable_stdimpl_set_double__1_0_base(
		conf, conf, prop, value);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_stdimpl_set_double__1_0_base
(
	if_configurable_1_0_t *conf,
	void *base,
	if_configurable_propref_t *prop,
	double value
)
{
	if_configurable_propspec_double_t *	spec_double;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_DOUBLE:
			spec_double = &prop->definition.spec.type_double;

			if((value < spec_double->min_value)
			 || (value > spec_double->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((double *) base) = value;
			break;

		default:
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	if(prop->update_notifier != NULL)
		prop->update_notifier((if_configurable_t *) conf, prop);

	return EXTIT_STATUS_OK;
}
