/*
 * @(#) pmodule/win32/container_defaults.c
 *
 * Windows specific implementations of container library.
 * Default extit_container_*() function implementations.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <windows.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "ptr_util.h"


EXTIT_EXPORT
extit_func_t
EXTIT_DECL
extit_container_get_function_default
(
	const extit_container_t *container,
	const char *name
)
{
	return GetProcAddress(GetModuleHandle(NULL), name);
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
	return FUNCPTR_TO_VOIDPTR(GetProcAddress(GetModuleHandle(NULL), name));
}
