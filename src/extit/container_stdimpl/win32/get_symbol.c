/*
 * @(#) container_stdimpl/win32/get_symbol.c
 *
 * Standard container/get_symbol() implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <windows.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_stdimpl.h>
#include <extit/platform.h>


void *
EXTIT_DECL
extit_container_stdimpl_get_symbol__1_0
(
	const extit_container_1_0_t *container,
	const char *name
)
{
	return FUNCPTR_TO_VOIDPTR(GetProcAddress(GetModuleHandle(NULL), name));
}
