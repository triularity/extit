/*
 * @(#) container/container_defaults.c
 *
 * Default extit_container_*() function implementations.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>


EXTIT_EXPORT
void *
EXTIT_DECL
extit_container_get_interface_default
(
	const extit_container_t *container,
	const char *id,
	iv_version_t version
)
{
	return NULL;
}


EXTIT_EXPORT
void
EXTIT_DECL
extit_container_log_default
(
	const extit_container_t *container,
	const char *message
)
{
	fputs(message, stderr);
}


EXTIT_EXPORT
iv_version_t
EXTIT_DECL
extit_container_query_interface_default
(
	const extit_container_t *container,
	const char *id,
	iv_version_t base_version
)
{
	return IV_VERSION_NONE;
}
