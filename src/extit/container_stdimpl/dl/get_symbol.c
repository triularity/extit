/*
 * @(#) container_stdimpl/dl/get_symbol.c
 *
 * Standard container/get_function() implementations.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <dlfcn.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_stdimpl.h>


EXTIT_EXPORT
void *
EXTIT_DECL
extit_container_get_symbol_stdimpl
(
	const extit_container_t *container,
	const char *name
)
{
	return dlsym(RTLD_DEFAULT, name);
}
