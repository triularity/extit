/*
 * @(#) container_stdimpl/dl/get_function.c
 *
 * Standard container/get_function() implementations.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <dlfcn.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_stdimpl.h>


EXTIT_EXPORT
extit_func_t
EXTIT_DECL
extit_container_stdimpl_get_function__1_0
(
	const extit_container_t *container,
	const char *name
)
{
#ifdef	EXTIT_HAVE_DLFUNC
	return dlfunc(RTLD_DEFAULT, name);
#else
	{
		extit_func_t	fptr;


		*((void **) &fptr) = dlsym(RTLD_DEFAULT, name);
		return fptr;
	}
#endif	/* EXTIT_HAVE_DLFUNC */
}
