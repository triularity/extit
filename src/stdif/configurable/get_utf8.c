/*
 * @(#) stdif/configurable/get_utf8.c
 *
 * Configurable Interface - get_utf8@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>

#ifdef	STDIF_PARANOID
#include <iv/util.h>
#endif


/**
 * Get a property value as a UTF8 string.
 * The string value can be @{constant NULL}.
 *
 * This is a convenience function that calls
 * @{param configurable}@{code ->ops->v0.op_get_utf8( ... )}
 *
 * @note	The contents of memory referenced by @{param valuep}
 *		will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	The string returned is owned by the @{param configurable}
 *		instance and should not be modified. It is only guaranteed
 *		to be valid while the instance exists and the property value
 *		is not changed.
 *
 * @param	configurable	The configurable instance.
 * @param	prop		The property reference.
 * @param	valuep		The address to store the value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible,
 *		or @{constant EXTIT_STATUS_INVALID} if the value is out
 *		of valid range for the return type.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_set_utf8__1_0(stdif_configurable_t *, stdif_configurable_propref_t *, const char *)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_get_utf8__1_0
(
	stdif_configurable_t *configurable,
	stdif_configurable_propref_t *prop,
	const char **valuep
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(configurable->version, STDIF_CONFIGURABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_get_utf8(
		IMPL(configurable), prop, valuep);

#undef	IMPL
}
