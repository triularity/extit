/*
 * @(#) pmodule/plugin_get_interface.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>
#include <extit/pmodule_impl.h>

#include "pmodule_internal.h"


EXTIT_EXPORT
void *
EXTIT_DECL
extit_plugin_get_interface
(
	extit_plugin_t *plugin,
	const char *id,
	iv_version_t version
)
{
	extit_module_t *			module;
	extit_pmodule_descriptor_1_0_t *	descriptor;


	module = plugin->module;

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->abi_version) != 1)
		return NULL;
#endif

	descriptor = (extit_pmodule_descriptor_1_0_t *) module->descriptor;

	if(descriptor->ops->v0.op_get_interface == NULL)
		return NULL;

	return descriptor->ops->v0.op_get_interface(
		descriptor, module->container, plugin->ctx, id, version);
}
