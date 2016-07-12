/*
 * @(#) extit/if/configurable_stdimpl/get_utf8.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/if/configurable.h>
#include <extit/if/configurable_impl.h>
#include <extit/if/configurable_stdimpl.h>

#ifdef  EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_configurable_get_utf8_stdimpl
(
	extit_if_configurable_t *conf,
	extit_if_configurable_propref_t *prop,
	const char **valuep
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, EXTIT_IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return extit_if_configurable_get_utf8_stdimpl_base(
		conf, prop, valuep);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_configurable_get_utf8_stdimpl_base
(
	void *base,
	extit_if_configurable_propref_t *prop,
	const char **valuep
)
{
	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case EXTIT_IF_CONFIGURABLE_TYPE_UTF8:
			*valuep = *((char **) base);
			break;

		default:
			return EXTIT_IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
