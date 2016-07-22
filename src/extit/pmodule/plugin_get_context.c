/*
 * @(#) pmodule/plugin_get_context.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "pmodule_internal.h"


EXTIT_EXPORT
void *
EXTIT_DECL
extit_plugin_get_context
(
	extit_plugin_t *plugin
)
{
	return plugin->ctx;
}
