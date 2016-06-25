/*
 * @(#) container/plugin_getFlags.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/container.h>

#include "container_impl.h"


EXTIT_EXPORT
unsigned int
EXTIT_DECL
extit_plugin_getFlags
(
	extit_plugin_t *plugin
)
{
	return plugin->flags;
}
