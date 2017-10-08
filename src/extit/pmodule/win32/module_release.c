/*
 * @(#) pmodule/win32/module_release.c
 *
 * Windows specific implementations of container library.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>

#include <windows.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "../pmodule_internal.h"


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

	if(!FreeLibrary(module->handle))
	{
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
		"[extit:module] Error unloading library: Error #%u.\n",
				(unsigned int) GetLastError());
		}
	}

	free(module);

	return EXTIT_STATUS_OK;
}
