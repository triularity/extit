/*
 * @(#) stdif/configurable_stdimpl/get_utf8.c
 *
 * Configurable Interface - get_utf8@1.0 standard implementation.
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
 * Standard implementation to get a property value as a UTF-8 string.
 *
 * @note	The contents of memory referenced by @{param valuep}
 *		will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation returns the @{type const char *} value at
 *		@{param configurable} @{code +} @{param prop}@{code ->offset}
 *		of the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_DATA},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UTF8}.
 *
 * @param	configurable	The configurable instance.
 * @param	prop		The property reference.
 * @param	valuep		The address to store the value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_set_utf8__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, const char *)}
 * @see		@{func stdif_configurable_stdimpl_get_utf8__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, const char **)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_utf8__1_0
(
	stdif_configurable_1_0_t *configurable,
	stdif_configurable_propref_t *prop,
	const char **valuep
)
{
	return stdif_configurable_stdimpl_get_utf8__1_0_base(
		configurable, configurable, prop, valuep);
}


/**
 * Standard implementation helper to get a property value as a UTF-8 string.
 *
 * @note	The contents of memory referenced by @{param valuep}
 *		will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation returns the @{type const char *} value
 *		at @{param base} @{code +} @{param prop}@{code ->offset}.
 *		of the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_DATA},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UTF8}.
 *
 * @param	configurable	The configurable instance.
 * @param	base		The base address.
 * @param	prop		The property reference.
 * @param	valuep		The address to store the value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_set_utf8__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, const char *)}
 * @see		@{func stdif_configurable_stdimpl_get_utf8__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, const char **)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_utf8__1_0_base
(
	stdif_configurable_1_0_t *configurable,
	void *base,
	stdif_configurable_propref_t *prop,
	const char **valuep
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

			*valuep = *((const char **) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_UTF8:
			*valuep = *((char **) base);
			break;

		default:
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
