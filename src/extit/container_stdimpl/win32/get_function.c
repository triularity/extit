/*
 * @(#) container_stdimpl/win32/get_function.c
 *
 * Standard container/get_function() implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <windows.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_stdimpl.h>


extit_func_t
EXTIT_DECL
extit_container_stdimpl_get_function__1_0
(
	const extit_container_1_0_t *container,
	const char *name
)
{
	return GetProcAddress(GetModuleHandle(NULL), name);
}
