/*
 * @(#) container/plugin_getModule.c
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
extit_module_t *
EXTIT_DECL
extit_plugin_getModule
(
	extit_plugin_t *plugin
)
{
	return plugin->module;
}
