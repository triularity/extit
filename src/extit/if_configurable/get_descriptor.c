/*
 * @(#) extit/if_configurable/get_descriptor.c
 *
 * Configurable Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <extit/if/configurable.h>
#include <extit/if/configurable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
const extit_if_configurable_descriptor_t *
EXTIT_DECL
extit_if_configurable_get_descriptor
(
	extit_if_configurable_t *configurable
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(configurable->version, EXTIT_IF_CONFIGURABLE_ABI_1_0))
		return NULL;
#endif

	return configurable->descriptor;
}
