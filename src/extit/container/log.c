/*
 * @(#) extit/container/log.c
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


void
EXTIT_DECL
extit_container_log__1_0
(
	const extit_container_t *container,
	const char *message
)
{
	const extit_container_1_0_t *	container_1_0;


#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(container->version) != 1)
		return;
#endif

	container_1_0 = (const extit_container_1_0_t *) container;

	container_1_0->ops->v0.op_log(container_1_0, message);
}
