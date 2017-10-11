/*
 * @(#) stdif/configurable/get_data.c
 *
 * Configurable Interface - get_data@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


extit_status_t
EXTIT_DECL
stdif_configurable_get_data__1_0
(
	stdif_configurable_t *configurable,
	stdif_configurable_propref_t *prop,
	void **valuep
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(configurable->version, STDIF_CONFIGURABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_configurable_1_0_t *) (x))

	return IMPL(configurable)->ops->v0.op_get_data(
		IMPL(configurable), prop, valuep);

#undef	IMPL
}
