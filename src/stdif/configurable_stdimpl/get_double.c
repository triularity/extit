/*
 * @(#) stdif/configurable_stdimpl/get_double.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_double__1_0
(
	stdif_configurable_1_0_t *conf,
	stdif_configurable_propref_t *prop,
	double *valuep
)
{
	return stdif_configurable_stdimpl_get_double__1_0_base(
		conf, conf, prop, valuep);
}


extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_double__1_0_base
(
	stdif_configurable_1_0_t *conf,
	void *base,
	stdif_configurable_propref_t *prop,
	double *valuep
)
{
	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_DOUBLE:
			*valuep = *((double *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_FLOAT:
			*valuep = *((float *) base);
			break;

		default:
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
