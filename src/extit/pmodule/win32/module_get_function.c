/*
 * @(#) pmodule/win32/module_get_function.c
 *
 * Windows specific implementations of container library.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <windows.h>

#include <extit/base.h>
#include <extit/container.h>
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
	return GetProcAddress(module->handle, name);
}
