/*
 * @(#) container_stdimpl/win32/container_defaults.c
 *
 * Default extit_container_*() function implementations for win32.
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
	FARPROC	ptr;


	ptr = GetProcAddress(GetModuleHandle(NULL), name);

#ifdef	__GNUC__
	return *((void **) &ptr);
#else
	return (void *) ptr;
#endif
}
