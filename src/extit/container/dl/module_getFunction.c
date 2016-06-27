/*
 * @(#) container/dl/module_getFunction.c
 *
 * [lib]dl specific implementations of container library.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <dlfcn.h>

#include <extit/base.h>
#include <extit/plugin_spi.h>
#include <extit/container.h>

#include "../container_impl.h"


EXTIT_EXPORT
extit_func_t
EXTIT_DECL
extit_module_getFunction
(
	extit_module_t *module,
	const char *name
)
{
#ifdef	EXTIT_HAVE_DLFUNC
	return dlfunc(module->handle, name);
#else
	{
		extit_func_t	fptr;


		*((void **) &fptr) = dlsym(module->handle, name);
		return fptr;
	}
#endif	/* EXTIT_HAVE_DLFUNC */
}
