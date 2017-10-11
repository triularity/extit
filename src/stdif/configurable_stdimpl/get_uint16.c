/*
 * @(#) if/configurable_stdimpl/get_uint16.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>
#include <if/configurable_stdimpl.h>


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_get_uint16__1_0
(
	if_configurable_1_0_t *conf,
	if_configurable_propref_t *prop,
	uint16_t *valuep
)
{
	return if_configurable_stdimpl_get_uint16__1_0_base(
		conf, conf, prop, valuep);
}


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_get_uint16__1_0_base
(
	if_configurable_1_0_t *conf,
	void *base,
	if_configurable_propref_t *prop,
	uint16_t *valuep
)
{
	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_UINT8:
			*valuep = *((uint8_t *) base);
			break;

		case IF_CONFIGURABLE_TYPE_UINT16:
			*valuep = *((uint16_t *) base);
			break;

		default:
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}