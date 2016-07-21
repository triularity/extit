/*
 * @(#) pmodule/win32/ptr_util.c
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <windows.h>

#include "ptr_util.h"


#ifdef	__GNUC__

void *
_extit_funcptr_to_voidptr(FARPROC ptr)
{
	return *((void **) &ptr);
}

#endif
