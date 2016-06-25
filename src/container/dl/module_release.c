/*
 * @(#) container/dl/module_release.c
 *
 * [lib]dl specific implementations of container library.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include <dlfcn.h>

#include <extit/base.h>
#include <extit/container.h>

#include "../container_impl.h"


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_module_release
(
	extit_module_t *module
)
{
	extit_status_t		status;
	unsigned int		flags;


	status = _extit_module_unload(module);

	if(status != EXTIT_STATUS_OK)
		return status;

	flags = module->flags;

	if(module->handle != NULL)
	{
		if(dlclose(module->handle) != 0)
		{
			if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
			{
				fprintf(stderr,
			"[extit:module] Error unloading library: %s\n",
					dlerror());
			}
		}
	}

	free(module);

	return EXTIT_STATUS_OK;
}
