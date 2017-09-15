/*
 * @(#) pmodule/dl/module_load.c
 *
 * [lib]dl specific implementations of container library.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include <dlfcn.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>
#include <extit/pmodule.h>

#include "../pmodule_internal.h"


EXTIT_EXPORT
extit_module_t *
EXTIT_DECL
extit_module_load(
	const extit_container_t *container,
	const char *path,
	unsigned int flags
)
{
	void *			handle;
	const void *		descriptor;
	extit_module_t *	module;


	/*
	 * Supported container version?
	 */
	if(IV_VERSION_MAJOR(container->version) != 1)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
		"[extit:module] Unsupported container version: %u.x.\n",
				IV_VERSION_MAJOR(container->version));
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:module] Loading '%s'.\n",
			path);
	}
#endif	/* EXTIT_DEBUG */

	if((handle = dlopen(path, RTLD_LAZY|RTLD_LOCAL)) == NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:module] Error loading '%s': %s.\n",
				path,
				dlerror());
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

	/*
	 * Find the plugin descriptor
	 */
	if((descriptor = dlsym(handle, EXTIT_PMODULE_DESCRIPTOR_SYMBOL))
	 == NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:module] No plugin descriptor.\n");
		}
#endif	/* EXTIT_DEBUG */

		dlclose(handle);
		return NULL;
	}

	/*
	 * Create the module from a descriptor
	 */
	module = extit_module_bind(container, descriptor, flags);

	if(module == NULL)
	{
		dlclose(handle);
		return NULL;
	}

	module->handle = handle;

	return module;
}
