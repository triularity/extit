/*
 * @(#) if/configurable_stdimpl/get_bool.c
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

#ifdef  EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_stdimpl_get_bool__1_0
(
	if_configurable_t *conf,
	if_configurable_propref_t *prop,
	extit_bool_t *valuep
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return if_configurable_stdimpl_get_bool__1_0_base(
		conf, conf, prop, valuep);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_stdimpl_get_bool__1_0_base
(
	if_configurable_t *conf,
	void *base,
	if_configurable_propref_t *prop,
	extit_bool_t *valuep
)
{
	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_BOOL:
			*valuep = *((extit_bool_t *) base);
			break;

		default:
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
