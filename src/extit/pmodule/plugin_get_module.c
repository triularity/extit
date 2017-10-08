/*
 * @(#) extit/pmodule/plugin_get_module.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "pmodule_internal.h"


extit_module_t *
EXTIT_DECL
extit_plugin_get_module
(
	extit_plugin_t *plugin
)
{
	return plugin->module;
}
