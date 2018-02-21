/*
 * @(#) stdif/configurable_stdimpl/set_utf8.c
 *
 * Configurable Interface - set_utf8@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


/**
 * Standard implementation to set a property value as a UTF-8 string.
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation calls @{func free(void *)} with the
 *		@{type char *} value at @{param configurable} @{code +}
 *		@{param prop}@{code ->offset}, if non-@{code NULL},
 *		then stores the copy of the @{param value} string there.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_UTF8}
 *
 * @param	configurable	The configurable instance.
 * @param	prop		The property reference.
 * @param	value		The new value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible.
 *		or @{constant EXTIT_STATUS_NOMEM} if memory allocation failed.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_get_utf8__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, const char **)}
 * @see		@{func stdif_configurable_stdimpl_set_utf8__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, const char *)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_utf8__1_0
(
	stdif_configurable_1_0_t *configurable,
	stdif_configurable_propref_t *prop,
	const char *value
)
{
	return stdif_configurable_stdimpl_set_utf8__1_0_base(
		configurable, conf, prop, value);
}


/**
 * Standard implementation helper to set a property value as a UTF-8 string.
 *
 * @note	The property will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation calls @{func free(void *)} with the
 *		@{type char *} value at @{param base} @{code +}
 *		@{param prop}@{code ->offset}, if non-@{code NULL},
 *		then stores the copy of the @{param value} string there.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_UTF8}
 *
 * @param	configurable	The configurable instance.
 * @param	base		The base address.
 * @param	prop		The property reference.
 * @param	value		The new value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible.
 *		or @{constant EXTIT_STATUS_NOMEM} if memory allocation failed.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_get_utf8__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, const char **)}
 * @see		@{func stdif_configurable_stdimpl_set_utf8__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, const char *)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_set_utf8__1_0_base
(
	stdif_configurable_1_0_t *configurable,
	void *base,
	stdif_configurable_propref_t *prop,
	const char *value
)
{
	size_t		len;
	char *		new_utf8;
	char *		old_utf8;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_UTF8:
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
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	if(prop->update_notifier != NULL)
	{
		prop->update_notifier(
			(stdif_configurable_t *) configurable, prop);
	}

	return EXTIT_STATUS_OK;
}
