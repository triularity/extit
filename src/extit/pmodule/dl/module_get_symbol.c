/*
 * @(#) pmodule/dl/module_get_symbol.c
 *
 * [lib]dl specific implementations of container library.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <dlfcn.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "../container_impl.h"


EXTIT_EXPORT
void *
EXTIT_DECL
extit_module_get_symbol
(
	extit_module_t *module,
	const char *name
)
{
	return dlsym(module->handle, name);
}
