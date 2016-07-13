/*
 * @(#) if/configurable_stdimpl/get_int32.c
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
if_configurable_get_int32_stdimpl
(
	if_configurable_t *conf,
	if_configurable_propref_t *prop,
	int32_t *valuep
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return if_configurable_get_int32_stdimpl_base(
		conf, conf, prop, valuep);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_configurable_get_int32_stdimpl_base
(
	if_configurable_t *conf,
	void *base,
	if_configurable_propref_t *prop,
	int32_t *valuep
)
{
	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_INT8:
			*valuep = *((int8_t *) base);
			break;

		case IF_CONFIGURABLE_TYPE_INT16:
			*valuep = *((int16_t *) base);
			break;

		case IF_CONFIGURABLE_TYPE_INT32:
		case IF_CONFIGURABLE_TYPE_ENUM32:
			*valuep = *((int32_t *) base);
			break;

		default:
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
