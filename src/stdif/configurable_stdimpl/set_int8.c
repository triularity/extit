/*
 * @(#) if/configurable_stdimpl/set_int8.c
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


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_set_int8__1_0
(
	if_configurable_1_0_t *conf,
	if_configurable_propref_t *prop,
	int8_t value
)
{
	return if_configurable_stdimpl_set_int8__1_0_base(
		conf, conf, prop, value);
}


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_set_int8__1_0_base
(
	if_configurable_1_0_t *conf,
	void *base,
	if_configurable_propref_t *prop,
	int8_t value
)
{
	if_configurable_propspec_int8_t *	spec_int8;
	if_configurable_propspec_int16_t *	spec_int16;
	if_configurable_propspec_int32_t *	spec_int32;
	if_configurable_propspec_int64_t *	spec_int64;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_INT8:
			spec_int8 = &prop->definition.spec.type_int8;

			if((value < spec_int8->min_value)
			 || (value > spec_int8->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((int8_t *) base) = value;
			break;

		case IF_CONFIGURABLE_TYPE_INT16:
			spec_int16 = &prop->definition.spec.type_int16;

			if((value < spec_int16->min_value)
			 || (value > spec_int16->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((int16_t *) base) = value;
			break;

		case IF_CONFIGURABLE_TYPE_INT32:
			spec_int32 = &prop->definition.spec.type_int32;

			if((value < spec_int32->min_value)
			 || (value > spec_int32->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((int32_t *) base) = value;
			break;

		case IF_CONFIGURABLE_TYPE_INT64:
			spec_int64 = &prop->definition.spec.type_int64;

			if((value < spec_int64->min_value)
			 || (value > spec_int64->max_value))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((int64_t *) base) = value;
			break;

		default:
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	if(prop->update_notifier != NULL)
		prop->update_notifier((if_configurable_t *) conf, prop);

	return EXTIT_STATUS_OK;
}