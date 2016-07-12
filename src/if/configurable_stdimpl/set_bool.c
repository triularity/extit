/*
 * @(#) if/configurable_stdimpl/set_bool.c
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
if_configurable_set_bool_stdimpl
(
	if_configurable_t *conf,
	if_configurable_propref_t *prop,
	extit_bool_t value
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return if_configurable_set_bool_stdimpl_base(conf, prop, value);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_set_bool_stdimpl_base
(
	void *base,
	if_configurable_propref_t *prop,
	extit_bool_t value
)
{
	if(prop->setter != NULL)
		return prop->setter(base, prop, &value);

	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_BOOL:
			*((extit_bool_t *) base) = value;
			break;

		default:
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
