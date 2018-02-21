/*
 * @(#) stdif/configurable_stdimpl/get_bool.c
 *
 * Configurable Interface - get_bool@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdbool.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


/**
 * Standard implementation to get a property value as a boolean.
 *
 * @note	The contents of memory referenced by @{param valuep}
 *		will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation returns the value at
 *		@{param conf} @{code +} @{param prop}@{code ->offset}
 *		of the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_BOOL}.
 *
 * @param	conf		The configurable instance.
 * @param	prop		The property reference.
 * @param	valuep		The address to store the value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_set_bool__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, bool)}
 * @see		@{func stdif_configurable_stdimpl_get_bool__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, bool *)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_bool__1_0
(
	stdif_configurable_1_0_t *conf,
	stdif_configurable_propref_t *prop,
	bool *valuep
)
{
	return stdif_configurable_stdimpl_get_bool__1_0_base(
		conf, conf, prop, valuep);
}


/**
 * Standard implementation helper to get a property value as a boolean.
 *
 * @note	The contents of memory referenced by @{param valuep}
 *		will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation returns the value at
 *		@{param base} @{code +} @{param prop}@{code ->offset}
 *		of the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_BOOL}.
 *
 * @param	conf		The configurable instance.
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
 * @see		@{func stdif_configurable_stdimpl_set_bool__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, bool)}
 * @see		@{func stdif_configurable_stdimpl_get_bool__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, bool *)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_bool__1_0_base
(
	stdif_configurable_1_0_t *conf,
	void *base,
	stdif_configurable_propref_t *prop,
	bool *valuep
)
{
	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_BOOL:
			*valuep = *((bool *) base);
			break;

		default:
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
