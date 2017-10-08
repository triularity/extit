/*
 * @(#) if/configurable_stdimpl/get_utf8.c
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
if_configurable_stdimpl_get_utf8__1_0
(
	if_configurable_1_0_t *conf,
	if_configurable_propref_t *prop,
	const char **valuep
)
{
	return if_configurable_stdimpl_get_utf8__1_0_base(
		conf, conf, prop, valuep);
}


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_get_utf8__1_0_base
(
	if_configurable_1_0_t *conf,
	void *base,
	if_configurable_propref_t *prop,
	const char **valuep
)
{
	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_UTF8:
			*valuep = *((char **) base);
			break;

		default:
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
