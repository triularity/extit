/*
 * @(#) container/module_bind.c
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

#include "container_impl.h"


#ifndef	MIN
#define	MIN(a,b)	(((a)<(b))?(a):(b))
#endif


EXTIT_EXPORT
extit_module_t *
EXTIT_DECL
extit_module_bind
(
	const extit_container_t *container,
	const void *descriptor,
	unsigned int flags
)
{
	const extit_spi_descriptor_base_t *	descriptor_base;
	const extit_spi_descriptor_1_0_t *	descriptor_1_0;
	iv_version_t				abi_version;
	extit_status_t				status;
	extit_module_t *			module;


	descriptor_base = (const extit_spi_descriptor_base_t *) descriptor;

	/*
	 * Validate structure
	 */
	if(descriptor_base->magic != EXTIT_SPI_MAGIC)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
		"[extit:module] Invalid plugin descriptor, magic = %08x.\n",
				descriptor_base->magic);
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:module] Found descriptor (v%u.%u).\n",
			IV_VERSION_MAJOR(descriptor_base->extit_version),
			IV_VERSION_MINOR(descriptor_base->extit_version));
	}
#endif	/* EXTIT_DEBUG */

	/*
	 * Supported plugin version?
	 */
	if(IV_VERSION_MAJOR(descriptor_base->extit_version) != 1)
		return NULL;

	abi_version =
		MIN(container->version,
			MIN(descriptor_base->extit_version,
				EXTIT_ABI_VERSION));

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:module] Using ABI v%u.%u.\n",
			IV_VERSION_MAJOR(abi_version),
			IV_VERSION_MINOR(abi_version));
	}
#endif	/* EXTIT_DEBUG */

	descriptor_1_0 = (extit_spi_descriptor_1_0_t *) descriptor_base;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:module] Found valid plugin: %s (%s).\n",
			descriptor_1_0->name,
			descriptor_1_0->version);

		fprintf(stderr,
			"[extit:module] Plugin ID: %s:0x%08x.\n",
			descriptor_1_0->id,
			descriptor_1_0->id_version);
	}
#endif	/* EXTIT_DEBUG */

	status = descriptor_1_0->handler(
			abi_version,
			container,
			EXTIT_SPI_CMD_PROBE,
			NULL,
			flags);

#ifdef	EXTIT_DEBUG
	if(status == EXTIT_STATUS_NOTIMPLEMENTED)
	{
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		{
			fprintf(stderr,
 				"[extit:module] Probe not implemented\n");
		}
	}
#endif	/* EXTIT_DEBUG */

	if((status != EXTIT_STATUS_OK)
	 && (status != EXTIT_STATUS_NOTIMPLEMENTED))
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
 				"[extit:module] Probe failed, status = %u.\n",
				status);
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

	if((module = calloc(1, sizeof(extit_module_t))) == NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:module] Memory allocation failed.\n");
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

	module->refcount = EXTIT_REFCOUNT_NONE;
	module->flags = flags;
	module->abi_version = abi_version;
	module->container = container;
	module->descriptor = descriptor_base;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[extit:module] Loaded plugin: %s (%s).\n",
			descriptor_1_0->name,
			descriptor_1_0->version);
	}
#endif	/* EXTIT_DEBUG */

	return module;
}
