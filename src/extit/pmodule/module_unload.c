/*
 * @(#) pmodule/container_common.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>

#include <extit/base.h>
#include <extit/util.h>
#include <extit/plugin_spi.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "container_impl.h"


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
_extit_module_unload
(
	extit_module_t *module
)
{
	unsigned int			flags;
	extit_spi_descriptor_1_0_t *	descriptor;
	extit_status_t			status;


	flags = module->flags;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:module] Unloading module, ID: %s.\n",
			extit_module_get_id(module));
	}
#endif

	if(module->refcount != EXTIT_REFCOUNT_NONE)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
			 "[extit:module] Module is busy, refcount = %u.\n",
				module->refcount);
		}
#endif

		return EXTIT_STATUS_BUSY;
	}

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->abi_version) != 1)
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

	status = descriptor->handler(
			module->abi_version,
			module->container,
			EXTIT_SPI_CMD_UNLOAD,
			NULL,
			flags);

	if(status == EXTIT_STATUS_NOTIMPLEMENTED)
	{
		status = EXTIT_STATUS_OK;

#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		{
			fprintf(stderr,
 				"[extit:module] Unload not implemented\n");
		}
#endif	/* EXTIT_DEBUG */
	}

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
	{
		if(status != EXTIT_STATUS_OK)
		{
			fprintf(stderr,
 				"[extit:module] Unload failed, status = %u.\n",
				status);
		}
	}
#endif	/* EXTIT_DEBUG */

	return status;
}
