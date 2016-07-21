/*
 * @(#) container_stdimpl/get_interface.c
 *
 * Standard container/get_interface() implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_stdimpl.h>


EXTIT_EXPORT
void *
EXTIT_DECL
extit_container_get_interface_stdimpl
(
	const extit_container_t *container,
	const char *id,
	iv_version_t version
)
{
	return NULL;
}
