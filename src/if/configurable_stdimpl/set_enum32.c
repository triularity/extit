/*
 * @(#) if/configurable_stdimpl/set_enum32.c
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
#include <if/configurable_util.h>

#ifdef  EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_set_enum32_stdimpl
(
	if_configurable_t *conf,
	if_configurable_propref_t *prop,
	uint32_t value
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return if_configurable_set_enum32_stdimpl_base(
		conf, conf, prop, value);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_set_enum32_stdimpl_base
(
	if_configurable_t *conf,
	void *base,
	if_configurable_propref_t *prop,
	uint32_t value
)
{
	if_configurable_propspec_enum32_t *	spec_enum32;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_ENUM32:
			spec_enum32 = &prop->definition.spec.type_enum32;

			if(if_configurable_enum32_find_by_value(
			 spec_enum32->choices, spec_enum32->choice_count,
			 value) == NULL)
			{
				return EXTIT_STATUS_INVALID;
			}

			*((uint32_t *) base) = value;
			break;

		default:
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	if(prop->update_notifier != NULL)
		prop->update_notifier(conf, prop);

	return EXTIT_STATUS_OK;
}
