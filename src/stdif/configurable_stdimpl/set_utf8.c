/*
 * @(#) stdif/configurable_stdimpl/set_utf8.c
 *
 * Configurable Interface - set_utf8@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string.h>

#include <iv/base.h>
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
 * @note	Unless otherwise specified by the object implementing
 *		the @{param configurable}, the pointer reference will
 *		persist and should remain valid until the property value
 *		is changed or the instance is destroyed.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_DATA},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UTF8}.
 *
 * @note	If the property is @{constant STDIF_CONFIGURABLE_TYPE_DATA}
 *		then its @{member stdif_configurable_propspec_data_t.iid} and
 *		@{member stdif_configurable_propspec_data_t.version} fields
 *		must be set to @{constant STDIF_CONFIGURABLE_UTF8_IID} and
 *		@{constant STDIF_CONFIGURABLE_UTF8_1_0}, respectively,
 *		or @{constant EXTIT_STATUS_INVALID} will be returned.
 *
 * @param	configurable	The configurable instance.
 * @param	prop		The property reference.
 * @param	value		The new value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible,
 *		or @{constant EXTIT_STATUS_INVALID} if the value is not
 *		a defined choice for that property.
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
		configurable, configurable, prop, value);
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
 *		@{constant STDIF_CONFIGURABLE_TYPE_DATA},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UTF8}.
 *
 * @note	If the property is @{constant STDIF_CONFIGURABLE_TYPE_DATA}
 *		then its @{member stdif_configurable_propspec_data_t.iid} and
 *		@{member stdif_configurable_propspec_data_t.version} fields
 *		must be set to @{constant STDIF_CONFIGURABLE_UTF8_IID} and
 *		@{constant STDIF_CONFIGURABLE_UTF8_1_0}, respectively,
 *		or @{constant EXTIT_STATUS_INVALID} will be returned.
 *
 * @param	configurable	The configurable instance.
 * @param	base		The base address.
 * @param	prop		The property reference.
 * @param	value		The new value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible,
 *		or @{constant EXTIT_STATUS_INVALID} if the value is not
 *		a defined choice for that property.
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
	stdif_configurable_propspec_data_t *	spec_data;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_DATA:
			spec_data = &prop->definition.spec.type_data;

			if(spec_data->iid == NULL)
				return EXTIT_STATUS_INVALID;

			if((strcmp(spec_data->iid,
			 STDIF_CONFIGURABLE_UTF8_IID) != 0)
			 || (spec_data->version
			  != STDIF_CONFIGURABLE_UTF8_1_0))
			{
				return EXTIT_STATUS_INVALID;
			}

			*((const char **) base) = value;
			break;

		case STDIF_CONFIGURABLE_TYPE_UTF8:
			*((const char **) base) = value;
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
