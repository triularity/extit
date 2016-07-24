/*
 * @(#) container/log.c
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
void
EXTIT_DECL
extit_container_log
(
	const extit_container_t *container,
	const char *message
)
{
#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(container->version) != 1)
		return;
#endif

	container->ops->op_log(container, message);
}
