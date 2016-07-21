/*
 * @(#) container/plugin_get_interface.c
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

#include "container_impl.h"


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
	unsigned int			flags;
	extit_module_t *		module;
	extit_spi_descriptor_1_0_t *	descriptor;
	extit_spi_param_get_interface_t	params;
	extit_status_t			status;


	flags = plugin->flags;
	module = plugin->module;

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->abi_version) != 1)
		return NULL;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

	params.spi_ctx = plugin->spi_ctx;
	params.id = id;
	params.version = version;

#ifdef	EXTIT_PARANOID
	params.interface_ptr = NULL;
#endif

	status = descriptor->handler(
			module->abi_version,
			module->container,
			EXTIT_SPI_CMD_GET_INTERFACE,
			&params,
			flags);

	return (status == EXTIT_STATUS_OK) ? params.interface_ptr : NULL;
}
