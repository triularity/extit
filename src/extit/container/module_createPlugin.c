/*
 * @(#) container/module_createPlugin.c
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
#include <extit/plugin_spi.h>
#include <extit/container.h>

#include "container_impl.h"


EXTIT_EXPORT
extit_plugin_t *
EXTIT_DECL
extit_module_createPlugin
(
	extit_module_t *module
)
{
	unsigned int			flags;
	extit_plugin_t *		plugin;
	extit_spi_descriptor_1_0_t *	descriptor;
	extit_spi_param_create_t	params;
	extit_status_t			status;


	flags = module->flags;

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->api_version) != 1)
		return NULL;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

#ifdef	EXTIT_PARANOID
	if(module->refcount >= 0xF0000000)
	{
		fprintf(stderr,
			"[extit:module] Excessive number of instances for plugin %s:%u.",
			descriptor->id,
			descriptor->id_version);

		return NULL;
	}
#endif

	if((plugin = malloc(sizeof(extit_plugin_t))) == NULL)
	{
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:module] Allocation failed creating instance for plugin %s:%u.",
				descriptor->id,
				descriptor->id_version);
		}

		return NULL;
	}

	params.spi_ctx = NULL;

	status = descriptor->handler(
			module->api_version,
			module->container,
			EXTIT_SPI_CMD_CREATE,
			&params,
			flags);

	if(status != EXTIT_STATUS_OK)
	{
		free(plugin);

		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:module] Unable to create instance for plugin %s:%u, status = %u.",
				descriptor->id,
				descriptor->id_version,
				status);
		}

		return NULL;
	}

	plugin->spi_ctx = params.spi_ctx;

	module->refcount++;
	plugin->module = module;
	plugin->state = 0;

	return plugin;
}
