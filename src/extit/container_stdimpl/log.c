/*
 * @(#) container_stdimpl/log.c
 *
 * Standard container/log() implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_stdimpl.h>


EXTIT_EXPORT
void
EXTIT_DECL
extit_container_log_stdimpl
(
	const extit_container_t *container,
	const char *message
)
{
	fputs(message, stderr);
}
