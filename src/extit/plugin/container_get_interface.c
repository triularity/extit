/*
 * @(#) plugin/container_get_interface.c
 *
 * Container API wrappers for plugin use.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/plugin.h>


EXTIT_EXPORT
void *
EXTIT_DECL
extit_container_get_interface
(
	const extit_container_t *container,
	const char *name,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(container->version) != 1)
		return NULL;
#endif

	return container->ops->get_interface(container, name, version);
}
