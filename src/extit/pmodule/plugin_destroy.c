/*
 * @(#) pmodule/plugin_destroy.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/util.h>
#include <extit/container.h>
#include <extit/pmodule.h>
#include <extit/pmodule_impl.h>

#include "pmodule_internal.h"


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_plugin_destroy
(
	extit_plugin_t *plugin
)
{
	unsigned int				flags;
	extit_module_t *			module;
	extit_pmodule_descriptor_1_0_t *	descriptor;
	extit_status_t				status;


	flags = plugin->flags;
	module = plugin->module;

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->abi_version) != 1)
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	descriptor = (extit_pmodule_descriptor_1_0_t *) module->descriptor;

#ifdef	EXTIT_PARANOID
	if(module->refcount == EXTIT_REFCOUNT_NONE)
	{
		fprintf(stderr,
			"[extit:plugin] Attempting to destroy an instance for plugin %s:%u, which has no instances.\n",
			descriptor->id,
			descriptor->id_version);

		return EXTIT_STATUS_INVALID;
	}
#endif	/* EXTIT_PARANOID */

	if(descriptor->ops->op_destroy != NULL)
	{
		status = descriptor->ops->op_destroy(
			descriptor, module->container, plugin->ctx);

		if(status != EXTIT_STATUS_OK)
			return status;
	}

	status = extit_refcount_release(&plugin->module->refcount);

#ifdef	EXTIT_DEBUG
	if((status != EXTIT_STATUS_OK) && (status != EXTIT_STATUS_BUSY))
	{
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_NORMAL)
		{
			fprintf(stderr,
			 "[extit:plugin] Refcount error, status = %u.\n",
				status);
		}
	}
#endif	/* EXTIT_DEBUG */

	free(plugin);

	return EXTIT_STATUS_OK;
}
