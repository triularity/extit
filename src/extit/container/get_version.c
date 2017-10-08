/*
 * @(#) extit/container/get_version.c
 *
 * Container API wrappers.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>


iv_version_t
EXTIT_DECL
extit_container_get_version
(
	const extit_container_t *container
)
{
	return container->version;
}
