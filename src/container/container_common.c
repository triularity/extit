/*
 * @(#) container/container_common.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2014, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>

#include <extit/base.h>
#include <extit/plugin_spi.h>
#include <extit/container.h>

#include "container_impl.h"


#ifndef	MIN
#define	MIN(a,b)	(((a)<(b))?(a):(b))
#endif


EXTIT_EXPORT
void *
EXTIT_DECL
extit_container_get_interface_default
(
	const extit_container_t *container,
	const char *name,
	extit_iv_t version
)
{
	return NULL;
}


EXTIT_EXPORT
void
EXTIT_DECL
extit_container_log_default
(
	const extit_container_t *container,
	const char *message
)
{
	fputs(message, stderr);
}


EXTIT_EXPORT
extit_iv_t
EXTIT_DECL
extit_container_query_interface_default
(
	const extit_container_t *container,
	const char *name,
	extit_iv_t base_version
)
{
	return EXTIT_IV_NONE;
}


EXTIT_EXPORT
extit_iv_t
EXTIT_DECL
extit_getVersion(void)
{
	return EXTIT_API_VERSION;
}


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
	extit_iv_t				api_version;
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
			EXTIT_IV_MAJOR(descriptor_base->extit_version),
			EXTIT_IV_MINOR(descriptor_base->extit_version));
	}
#endif	/* EXTIT_DEBUG */

	/*
	 * Supported plugin version?
	 */
	if(EXTIT_IV_MAJOR(descriptor_base->extit_version) != 1)
		return NULL;

	api_version =
		MIN(container->version,
			MIN(descriptor_base->extit_version,
				EXTIT_API_VERSION));

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:module] Using API v%u.%u.\n",
			EXTIT_IV_MAJOR(api_version),
			EXTIT_IV_MINOR(api_version));
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
			api_version,
			container,
			EXTIT_SPI_CMD_PROBE,
			NULL,
			flags);

	if(status != EXTIT_STATUS_OK)
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

	module->refcount = 0;
	module->flags = flags;
	module->api_version = api_version;
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
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return NULL;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

#ifdef	EXTIT_PARANOID
	if(module->refcount >= 0xF0000000)
	{
		fprintf(stderr,
			"Excessive number of instances for plugin %s:%u.",
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
		"Allocation failed creating instance for plugin %s:%u.",
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
		"Unable to create instance for plugin %s:%u, status = %u.",
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


EXTIT_EXPORT
extit_iv_t
EXTIT_DECL
extit_module_getAPIVersion
(
	extit_module_t *module
)
{
	return module->descriptor->extit_version;
}


EXTIT_EXPORT
extit_iv_t
EXTIT_DECL
extit_module_getEffectiveAPIVersion
(
	extit_module_t *module
)
{
	return module->api_version;
}


EXTIT_EXPORT
unsigned int
EXTIT_DECL
extit_module_getFlags
(
	extit_module_t *module
)
{
	return module->flags;
}


EXTIT_EXPORT
const char *
EXTIT_DECL
extit_module_getId
(
	extit_module_t *module
)
{
#ifdef	EXTIT_PARANOID
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return NULL;
#endif

	return ((extit_spi_descriptor_1_0_t *) module->descriptor)->id;
}


EXTIT_EXPORT
unsigned int
EXTIT_DECL
extit_module_getIdVersion
(
	extit_module_t *module
)
{
#ifdef	EXTIT_PARANOID
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return 0;
#endif

	return ((extit_spi_descriptor_1_0_t *) module->descriptor)->id_version;
}


EXTIT_EXPORT
const char *
EXTIT_DECL
extit_module_getName
(
	extit_module_t *module
)
{
#ifdef	EXTIT_PARANOID
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return NULL;
#endif

	return ((extit_spi_descriptor_1_0_t *) module->descriptor)->name;
}


EXTIT_EXPORT
const char *
EXTIT_DECL
extit_module_getVersion
(
	extit_module_t *module
)
{
#ifdef	EXTIT_PARANOID
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return NULL;
#endif

	return ((extit_spi_descriptor_1_0_t *) module->descriptor)->version;
}


EXTIT_EXPORT
void
EXTIT_DECL
extit_module_setFlags
(
	extit_module_t *module,
	unsigned int flags
)
{
	module->flags = flags;
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_plugin_activate
(
	extit_plugin_t *plugin
)
{
	unsigned int			flags;
	extit_module_t *		module;
	extit_spi_descriptor_1_0_t *	descriptor;
	extit_spi_param_activate_t	params;
	extit_status_t			status;


	flags = plugin->flags;
	module = plugin->module;

#ifdef	EXTIT_PARANOID
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

	if(plugin->state & EXTIT_INSTANCE_STATE_ACTIVE)
	{
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
	"Attempting to activate already active instance for plugin %s:%u.",
				descriptor->id,
				descriptor->id_version);
		}

		return EXTIT_STATUS_BUSY;
	}

	params.spi_ctx = plugin->spi_ctx;

	status = descriptor->handler(
			module->api_version,
			module->container,
			EXTIT_SPI_CMD_ACTIVATE,
			&params,
			flags);

	if(status == EXTIT_STATUS_OK)
		plugin->state |= EXTIT_INSTANCE_STATE_ACTIVE;

	return status;
}


EXTIT_EXPORT
void *
EXTIT_DECL
extit_plugin_getContext
(
	extit_plugin_t *plugin
)
{
	return plugin->spi_ctx;
}


EXTIT_EXPORT
unsigned int
EXTIT_DECL
extit_plugin_getFlags
(
	extit_plugin_t *plugin
)
{
	return plugin->flags;
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_plugin_deactivate
(
	extit_plugin_t *plugin
)
{
	unsigned int			flags;
	extit_module_t *		module;
	extit_spi_descriptor_1_0_t *	descriptor;
	extit_spi_param_deactivate_t	params;
	extit_status_t			status;


	flags = plugin->flags;
	module = plugin->module;

#ifdef	EXTIT_PARANOID
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

	if((plugin->state & EXTIT_INSTANCE_STATE_ACTIVE) == 0)
	{
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
		"Attempting to deactivate inactive instance for plugin %s:%u.",
				descriptor->id,
				descriptor->id_version);
		}

		return EXTIT_STATUS_INVALID;
	}

	params.spi_ctx = plugin->spi_ctx;

	status = descriptor->handler(
			module->api_version,
			module->container,
			EXTIT_SPI_CMD_DEACTIVATE,
			&params,
			flags);

	if(status == EXTIT_STATUS_OK)
		plugin->state &= ~EXTIT_INSTANCE_STATE_ACTIVE;

	return status;
}


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
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

#ifdef	EXTIT_PARANOID
	if(module->refcount == 0)
	{
		fprintf(stderr,
 "Attempting to destroy an instances for plugin %s:%u, which has no instances.",
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
		"Implicitly deactivaing instance for plugin %s:%u on destroy.",
				descriptor->id,
				descriptor->id_version);
		}

		if(status != EXTIT_STATUS_OK)
		{
			fprintf(stderr,
		"Unable to deactive instance for plugin %s:%u on destroy.",
				descriptor->id,
				descriptor->id_version);

			return status;
		}
	}

	params.spi_ctx = plugin->spi_ctx;

	status = descriptor->handler(
			module->api_version,
			module->container,
			EXTIT_SPI_CMD_DESTROY,
			&params,
			flags);

	if(status == EXTIT_STATUS_OK)
	{
		plugin->module->refcount--;
		free(plugin);
	}

	return status;
}


EXTIT_EXPORT
void *
EXTIT_DECL
extit_plugin_getInterface
(
	extit_plugin_t *plugin,
	const char *name,
	extit_iv_t version
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
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return NULL;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

	params.spi_ctx = plugin->spi_ctx;
	params.name = name;
	params.version = version;

#ifdef	EXTIT_PARANOID
	params.interface_ptr = NULL;
#endif

	status = descriptor->handler(
			module->api_version,
			module->container,
			EXTIT_SPI_CMD_GET_INTERFACE,
			&params,
			flags);

	return (status == EXTIT_STATUS_OK) ? params.interface_ptr : NULL;
}


EXTIT_EXPORT
extit_module_t *
EXTIT_DECL
extit_plugin_getModule
(
	extit_plugin_t *plugin
)
{
	return plugin->module;
}


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


	flags = plugin->flags;
	module = plugin->module;

#ifdef	EXTIT_PARANOID
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

	params.spi_ctx = plugin->spi_ctx;

	return descriptor->handler(
			module->api_version,
			module->container,
			EXTIT_SPI_CMD_PING,
			&params,
			flags);
}


EXTIT_EXPORT
extit_iv_t
EXTIT_DECL
extit_plugin_queryInterface
(
	extit_plugin_t *plugin,
	const char *name,
	extit_iv_t base_version
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
	if(EXTIT_IV_MAJOR(module->api_version) != 1)
		return EXTIT_IV_NONE;
#endif

	descriptor = (extit_spi_descriptor_1_0_t *) module->descriptor;

	params.spi_ctx = plugin->spi_ctx;
	params.name = name;
	params.base_version = base_version;

#ifdef	EXTIT_PARANOID
	params.version = EXTIT_IV_NONE;
#endif

	status = descriptor->handler(
			module->api_version,
			module->container,
			EXTIT_SPI_CMD_QUERY_INTERFACE,
			&params,
			flags);

	if(status != EXTIT_STATUS_OK)
	{
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
	"Error querying interface %s:%u.%u for plugin %s:%u, status = %u.",
				name,
				EXTIT_IV_MAJOR(base_version),
				EXTIT_IV_MINOR(base_version),
				descriptor->id,
				descriptor->id_version,
				status);
		}

		return EXTIT_IV_NONE;
	}

	return params.version;
}


EXTIT_EXPORT
void
EXTIT_DECL
extit_plugin_setFlags
(
	extit_plugin_t *plugin,
	unsigned int flags
)
{
	plugin->flags = flags;
}

