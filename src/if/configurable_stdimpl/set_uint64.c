/*
 * @(#) if/configurable_stdimpl/set_uint64.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
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
if_configurable_set_uint64_stdimpl
(
	if_configurable_t *conf,
	if_configurable_propref_t *prop,
	uint64_t value
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return if_configurable_set_uint64_stdimpl_base(
		conf, conf, prop, value);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_set_uint64_stdimpl_base
(
	if_configurable_t *conf,
	void *base,
	if_configurable_propref_t *prop,
	uint64_t value
)
{
	if_configurable_propspec_uint64_t *	spec_uint64;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_UINT64:
			spec_uint64 = &prop->definition.spec.type_uint64;

			if((value < spec_uint64->min_value)
			 || (value > spec_uint64->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((uint64_t *) base) = value;
			break;

		default:
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	if(prop->update_notifier != NULL)
		prop->update_notifier(conf, prop);

	return EXTIT_STATUS_OK;
}
