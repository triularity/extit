/*
 * @(#) container/dl/container_defaults.c
 *
 * [lib]dl specific implementations of container library.
 * Default extit_container_*() function implementations.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <dlfcn.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>
#include <extit/pmodule.h>

#include "../container_impl.h"


EXTIT_EXPORT
extit_func_t
EXTIT_DECL
extit_container_get_function_default
(
	const extit_container_t *container,
	const char *name
)
{
#ifdef	EXTIT_HAVE_DLFUNC
	return dlfunc(RTLD_DEFAULT, name);
#else
	{
		extit_func_t	fptr;


		*((void **) &fptr) = dlsym(RTLD_DEFAULT, name);
		return fptr;
	}
#endif	/* EXTIT_HAVE_DLFUNC */
}


EXTIT_EXPORT
void *
EXTIT_DECL
extit_container_get_symbol_default
(
	const extit_container_t *container,
	const char *name
)
{
	return dlsym(RTLD_DEFAULT, name);
}
