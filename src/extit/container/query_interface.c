/*
 * @(#) extit/container/query_interface.c
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


iv_version_t
EXTIT_DECL
extit_container_query_interface__1_0
(
	const extit_container_t *container,
	const char *iid,
	iv_version_t base_version
)
{
	const extit_container_1_0_t *	container_1_0;


#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(container->version) != 1)
		return IV_VERSION_NONE;
#endif

	container_1_0 = (const extit_container_1_0_t *) container;

	return container_1_0->ops->v0.op_query_interface(
		container_1_0, iid, base_version);
}
