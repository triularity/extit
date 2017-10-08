/*
 * @(#) container_stdimpl/dl/get_symbol.c
 *
 * Standard container/get_function() implementations.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <dlfcn.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_stdimpl.h>


void *
EXTIT_DECL
extit_container_stdimpl_get_symbol__1_0
(
	const extit_container_1_0_t *container,
	const char *name
)
{
	return dlsym(RTLD_DEFAULT, name);
}
