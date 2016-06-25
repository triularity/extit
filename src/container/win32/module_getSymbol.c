/*
 * @(#) container/win32/module_getSymbol.c
 *
 * Windows specific implementations of container library.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <windows.h>

#include <extit/base.h>
#include <extit/container.h>

#include "../container_impl.h"


EXTIT_EXPORT
void *
EXTIT_DECL
extit_module_getSymbol
(
	extit_module_t *module,
	const char *name
)
{
	return (void *) GetProcAddress(module->handle, name);
}
