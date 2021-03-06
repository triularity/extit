/*
 * @(#) pmodule/dl/module_get_function.c
 *
 * [lib]dl specific implementations of container library.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <dlfcn.h>

#include <extit/base.h>
#include <extit/pmodule.h>

#include "../pmodule_internal.h"


extit_func_t
EXTIT_DECL
extit_module_get_function
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
