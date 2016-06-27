/*
 * @(#) container/plugin_ping.c
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

#include "container_impl.h"


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_plugin_ping
(
	extit_plugin_t *plugin
)
{
	unsigned int			flags;
	extit_module_t *		module;
	extit_spi_descriptor_1_0_t *	descriptor;
	extit_spi_param_ping_t		params;
	extit_status_t			status;


	flags = plugin->flags;
	module = plugin->module;

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->api_version) != 1)
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

	params.spi_ctx = plugin->spi_ctx;

	status = descriptor->handler(
			module->api_version,
			module->container,
			EXTIT_SPI_CMD_PING,
			&params,
			flags);

	if(status == EXTIT_STATUS_NOTIMPLEMENTED)
	{
		status = EXTIT_STATUS_OK;

#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		{
			fprintf(stderr,
 				"[extit:plugin] Ping not implemented\n");
		}
#endif	/* EXTIT_DEBUG */
	}

	return status;
}
