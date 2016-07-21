/*
 * @(#) container_stdimpl/win32/get_function.c
 *
 * Standard container/get_function() implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <windows.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_stdimpl.h>


EXTIT_EXPORT
extit_func_t
EXTIT_DECL
extit_container_get_function_stdimpl
(
	const extit_container_t *container,
	const char *name
)
{
	return GetProcAddress(GetModuleHandle(NULL), name);
}
