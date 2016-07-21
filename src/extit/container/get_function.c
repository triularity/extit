/*
 * @(#) container/get_function.c
 *
 * Container API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>


EXTIT_EXPORT
extit_func_t
EXTIT_DECL
extit_container_get_function
(
	const extit_container_t *container,
	const char *name
)
{
#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(container->version) != 1)
		return NULL;
#endif

	return container->ops->get_function(container, name);
}
