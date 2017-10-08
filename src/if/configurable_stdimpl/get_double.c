/*
 * @(#) if/configurable_stdimpl/get_double.c
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


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_get_double__1_0
(
	if_configurable_1_0_t *conf,
	if_configurable_propref_t *prop,
	double *valuep
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return if_configurable_stdimpl_get_double__1_0_base(
		conf, conf, prop, valuep);
}


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_get_double__1_0_base
(
	if_configurable_1_0_t *conf,
	void *base,
	if_configurable_propref_t *prop,
	double *valuep
)
{
	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_DOUBLE:
			*valuep = *((double *) base);
			break;

		case IF_CONFIGURABLE_TYPE_FLOAT:
			*valuep = *((float *) base);
			break;

		default:
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
