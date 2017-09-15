/*
 * @(#) extit/pmodule/module_create_plugin.c
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
extit_plugin_t *
EXTIT_DECL
extit_module_create_plugin
(
	extit_module_t *module
)
{
	unsigned int				flags;
	extit_plugin_t *			plugin;
	extit_pmodule_descriptor_1_0_t *	descriptor;
	extit_status_t				status;


	flags = module->flags;

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->abi_version) != 1)
		return NULL;
#endif

	descriptor = (extit_pmodule_descriptor_1_0_t *) module->descriptor;

	if(extit_refcount_add(&module->refcount) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"[extit:module] Excessive number of instances for plugin %s:%u.\n",
			descriptor->id,
			descriptor->id_version);

		return NULL;
	}

	if((plugin = malloc(sizeof(extit_plugin_t))) == NULL)
	{
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:module] Allocation failed creating instance for plugin %s:%u.\n",
				descriptor->id,
				descriptor->id_version);
		}

		/* no check - will always succeed */
		extit_refcount_release(&module->refcount);

		return NULL;
	}

	plugin->ctx = NULL;

	if(descriptor->ops->v0.op_create != NULL)
	{
		status = descriptor->ops->v0.op_create(
			descriptor, module->container, &plugin->ctx);

		if(status != EXTIT_STATUS_OK)
		{
			free(plugin);

			if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
			{
				fprintf(stderr,
					"[extit:module] Unable to create instance for plugin %s:%u, status = %u.\n",
					descriptor->id,
					descriptor->id_version,
					status);
			}

			/* no check - will always succeed */
			extit_refcount_release(&module->refcount);

			return NULL;
		}
	}

	plugin->module = module;

	return plugin;
}
