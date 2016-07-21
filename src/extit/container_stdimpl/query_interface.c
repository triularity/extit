/*
 * @(#) container_stdimpl/query_interface.c
 *
 * Standard container/query_interface() implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_stdimpl.h>


EXTIT_EXPORT
iv_version_t
EXTIT_DECL
extit_container_query_interface_stdimpl
(
	const extit_container_t *container,
	const char *id,
	iv_version_t base_version
)
{
	return IV_VERSION_NONE;
}
