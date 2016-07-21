/*
 * @(#) pmodule/plugin_query_interface.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/plugin_spi.h>
#include <extit/container.h>
#include <extit/pmodule.h>

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
	unsigned int				flags;
	extit_module_t *			module;
	extit_spi_descriptor_1_0_t *		descriptor;
	extit_spi_param_query_interface_t	params;
	extit_status_t				status;


	flags = plugin->flags;
	module = plugin->module;

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->abi_version) != 1)
		return IV_VERSION_NONE;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

	params.spi_ctx = plugin->spi_ctx;
	params.id = id;
	params.base_version = base_version;

#ifdef	EXTIT_PARANOID
	params.version = IV_VERSION_NONE;
#endif

	status = descriptor->handler(
			module->abi_version,
			module->container,
			EXTIT_SPI_CMD_QUERY_INTERFACE,
			&params,
			flags);

	if(status != EXTIT_STATUS_OK)
	{
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:plugin] Error querying interface %s:%u.%u for plugin %s:%u, status = %u.",
				id,
				IV_VERSION_MAJOR(base_version),
				IV_VERSION_MINOR(base_version),
				descriptor->id,
				descriptor->id_version,
				status);
		}

		return IV_VERSION_NONE;
	}

	return params.version;
}
