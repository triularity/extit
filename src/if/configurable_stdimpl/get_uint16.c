/*
 * @(#) if/configurable_stdimpl/get_uint16.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
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
if_configurable_get_uint16_stdimpl
(
	if_configurable_t *conf,
	if_configurable_propref_t *prop,
	uint16_t *valuep
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return if_configurable_get_uint16_stdimpl_base(conf, prop, valuep);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_get_uint16_stdimpl_base
(
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
