/*
 * @(#) stdif/configurable_stdimpl/get_int32.c
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
stdif_configurable_stdimpl_get_int32__1_0
(
	stdif_configurable_1_0_t *conf,
	stdif_configurable_propref_t *prop,
	int32_t *valuep
)
{
	return stdif_configurable_stdimpl_get_int32__1_0_base(
		conf, conf, prop, valuep);
}


extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_int32__1_0_base
(
	stdif_configurable_1_0_t *conf,
	void *base,
	stdif_configurable_propref_t *prop,
	int32_t *valuep
)
{
	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_INT8:
			*valuep = *((int8_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT16:
			*valuep = *((int16_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT32:
		case STDIF_CONFIGURABLE_TYPE_ENUM32:
			*valuep = *((int32_t *) base);
			break;

		default:
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
