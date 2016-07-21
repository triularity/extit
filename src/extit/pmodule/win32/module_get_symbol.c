/*
 * @(#) pmodule/win32/module_get_symbol.c
 *
 * Windows specific implementations of container library.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <windows.h>

#include <extit/base.h>
#include <extit/pmodule.h>

#include "../container_impl.h"
#include "ptr_util.h"


EXTIT_EXPORT
void *
EXTIT_DECL
extit_module_get_symbol
(
	extit_module_t *module,
	const char *name
)
{
	return FUNCPTR_TO_VOIDPTR(GetProcAddress(module->handle, name));
}
