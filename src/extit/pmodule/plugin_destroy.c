/*
 * @(#) extit/pmodule/plugin_destroy.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
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

	if(extit_refcount_isnone(&module->refcount))
	{
		if((flags & EXTIT_FLAG_LOG) > EXTIT_FLAG_LOG_MINIMAL)
		{
			fprintf(stderr,
				"[extit:plugin] Attempting to destroy an instance for plugin %s:%u, which has no instances.\n",
				descriptor->id,
				descriptor->id_version);
		}

		return EXTIT_STATUS_INVALID;
	}

	if(descriptor->ops->v0.op_destroy != NULL)
	{
		status = descriptor->ops->v0.op_destroy(
			descriptor, module->container, plugin->ctx);

		if(status != EXTIT_STATUS_OK)
			return status;
	}

	/* no check - will always succeed */
	extit_refcount_release(&plugin->module->refcount);

	free(plugin);

	return EXTIT_STATUS_OK;
}
