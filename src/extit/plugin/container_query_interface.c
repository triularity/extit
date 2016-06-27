/*
 * @(#) plugin/container_query_interface.c
 *
 * Container API wrappers for plugin use.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>


EXTIT_EXPORT
iv_version_t
EXTIT_DECL
extit_container_query_interface
(
	const extit_container_t *container,
	const char *name,
	iv_version_t base_version
)
{
#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(container->version) != 1)
		return IV_VERSION_NONE;
#endif

	return container->ops->query_interface(container, name, base_version);
}
