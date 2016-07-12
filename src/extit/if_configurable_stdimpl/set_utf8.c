/*
 * @(#) extit/if_configurable_stdimpl/set_utf8.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

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
extit_if_configurable_set_utf8_stdimpl
(
	extit_if_configurable_t *conf,
	extit_if_configurable_propref_t *prop,
	const char *value
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, EXTIT_IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return extit_if_configurable_set_utf8_stdimpl_base(
		conf, prop, value);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_configurable_set_utf8_stdimpl_base
(
	void *base,
	extit_if_configurable_propref_t *prop,
	const char *value
)
{
	size_t		len;
	char *		new_utf8;
	char *		old_utf8;


	if(prop->setter != NULL)
		return prop->setter(base, prop, &value);

	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case EXTIT_IF_CONFIGURABLE_TYPE_UTF8:
			if(value != NULL)
			{
				len = strlen(value) + 1;

				if((new_utf8 = malloc(len)) == NULL)
					return EXTIT_STATUS_NOMEM;

				memcpy(new_utf8, value, len);
			}
			else
			{
				new_utf8 = NULL;
			}

			if((old_utf8 = *((char **) base)) != NULL)
				free(old_utf8);

			*((char **) base) = new_utf8;
			break;

		default:
			return EXTIT_IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
