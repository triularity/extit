/*
 * @(#) if/configurable_stdimpl/set_enum32.c
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
#include <if/configurable_util.h>


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_set_enum32__1_0
(
	if_configurable_1_0_t *conf,
	if_configurable_propref_t *prop,
	uint32_t value
)
{
	return if_configurable_stdimpl_set_enum32__1_0_base(
		conf, conf, prop, value);
}


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_set_enum32__1_0_base
(
	if_configurable_1_0_t *conf,
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
		prop->update_notifier((if_configurable_t *) conf, prop);

	return EXTIT_STATUS_OK;
}
