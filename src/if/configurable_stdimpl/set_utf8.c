/*
 * @(#) if/configurable_stdimpl/set_utf8.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>
#include <if/configurable_stdimpl.h>

#ifdef  EXTIT_PARANOID
#include <iv/util.h>
#endif


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_set_utf8__1_0
(
	if_configurable_1_0_t *conf,
	if_configurable_propref_t *prop,
	const char *value
)
{
#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return EXTIT_STATUS_UNSUPPORTED;
#endif

	return if_configurable_stdimpl_set_utf8__1_0_base(
		conf, conf, prop, value);
}


extit_status_t
EXTIT_DECL
if_configurable_stdimpl_set_utf8__1_0_base
(
	if_configurable_1_0_t *conf,
	void *base,
	if_configurable_propref_t *prop,
	const char *value
)
{
	size_t		len;
	char *		new_utf8;
	char *		old_utf8;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case IF_CONFIGURABLE_TYPE_UTF8:
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
			return IF_CONFIGURABLE_STATUS_MISMATCH;
	}

	if(prop->update_notifier != NULL)
		prop->update_notifier((if_configurable_t *) conf, prop);

	return EXTIT_STATUS_OK;
}
