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
#include <extit/plugin_spi.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "pmodule_internal.h"


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_plugin_destroy
(
	extit_plugin_t *plugin
)
{
	unsigned int			flags;
	extit_module_t *		module;
	extit_spi_descriptor_1_0_t *	descriptor;
	extit_spi_param_destroy_t	params;
	extit_status_t			status;


	flags = plugin->flags;
	module = plugin->module;

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->abi_version) != 1)
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

#ifdef	EXTIT_PARANOID
	if(module->refcount == EXTIT_REFCOUNT_NONE)
	{
		fprintf(stderr,
			"[extit:plugin] Attempting to destroy an instance for plugin %s:%u, which has no instances.",
			descriptor->id,
			descriptor->id_version);

		return EXTIT_STATUS_INVALID;
	}
#endif	/* EXTIT_PARANOID */

	if(plugin->state & EXTIT_INSTANCE_STATE_ACTIVE)
	{
		status = extit_plugin_deactivate(plugin);

		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:plugin] Implicitly deactivaing instance for plugin %s:%u on destroy.",
				descriptor->id,
				descriptor->id_version);
		}

		if(status != EXTIT_STATUS_OK)
		{
			fprintf(stderr,
				"[extit:plugin] Unable to deactive instance for plugin %s:%u on destroy.",
				descriptor->id,
				descriptor->id_version);

			return status;
		}
	}

	params.spi_ctx = plugin->spi_ctx;

	status = descriptor->handler(
			module->abi_version,
			module->container,
			EXTIT_SPI_CMD_DESTROY,
			&params,
			flags);

	if(status == EXTIT_STATUS_OK)
	{
		extit_refcount_release(&plugin->module->refcount);
		free(plugin);
	}

	return status;
}
