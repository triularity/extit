/*
 * @(#) extit/container/get_symbol.c
 *
 * Container API wrappers.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>


void *
EXTIT_DECL
extit_container_get_symbol__1_0
(
	const extit_container_t *container,
	const char *name
)
{
	const extit_container_1_0_t *	container_1_0;


#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(container->version) != 1)
		return NULL;
#endif

	container_1_0 = (const extit_container_1_0_t *) container;

	return container_1_0->ops->v0.op_get_symbol(container_1_0, name);
}
