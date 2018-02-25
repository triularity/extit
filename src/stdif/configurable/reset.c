/*
 * @(#) stdif/configurable/reset.c
 *
 * Configurable Interface - reset@1.0 wrapper.
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
 * Reset all properties to their default values.
 *
 * This is a convenience function that calls
 * @{param configurable}@{code ->ops->v0.op_reset( ... )}
 *
 * @note	The @{param configurable} may be left in a partially reset
 *		state if this function fails.
 *
 * @param	configurable	The configurable instance.
 *
 * @return	@{constant EXTIT_STATUS_OK} all properties where reset
 *		successfully, otherwise a @{constant EXTIT_STATUS_}*
 *		value returned by the failing property setter.
 *
 * @since	1.0
 */
extit_status_t
EXTIT_DECL
stdif_configurable_reset__1_0
(
	stdif_configurable_t *configurable
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(configurable->version, STDIF_CONFIGURABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_reset(IMPL(configurable));

#undef	IMPL
}
