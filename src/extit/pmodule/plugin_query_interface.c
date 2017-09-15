/*
 * @(#) extit/pmodule/plugin_query_interface.c
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
iv_version_t
EXTIT_DECL
extit_plugin_query_interface
(
	extit_plugin_t *plugin,
	const char *id,
	iv_version_t base_version
)
{
	extit_module_t *			module;
	extit_pmodule_descriptor_1_0_t *	descriptor;


	module = plugin->module;

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->abi_version) != 1)
		return IV_VERSION_NONE;
#endif

	descriptor = (extit_pmodule_descriptor_1_0_t *) module->descriptor;

	if(descriptor->ops->v0.op_query_interface == NULL)
		return IV_VERSION_NONE;

	return descriptor->ops->v0.op_query_interface(
		descriptor,
		module->container,
		plugin->ctx,
		id,
		base_version);
}
