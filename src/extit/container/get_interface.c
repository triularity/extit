/*
 * @(#) container/get_interface.c
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


EXTIT_EXPORT
void *
EXTIT_DECL
extit_container_get_interface__1_0
(
	const extit_container_t *container,
	const char *iid,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(container->version) != 1)
		return NULL;
#endif

	return container->ops->op_get_interface(container, iid, version);
}
