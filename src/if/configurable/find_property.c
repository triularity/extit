/*
 * @(#) if/configurable/find_property.c
 *
 * Configurable Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
if_configurable_propref_t *
EXTIT_DECL
if_configurable_find_property
(
	if_configurable_t *configurable,
	const char *id
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(configurable->version, IF_CONFIGURABLE_ABI_1_0))
		return NULL;
#endif

	return IF_CONFIGURABLE_FIND_PROPERTY(configurable, id);
}
