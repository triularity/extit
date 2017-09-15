/*
 * @(#) container_stdimpl/log.c
 *
 * Standard container/log() implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_stdimpl.h>


EXTIT_EXPORT
void
EXTIT_DECL
extit_container_stdimpl_log__1_0
(
	const extit_container_1_0_t *container,
	const char *message
)
{
	fputs(message, stderr);
	fputc('\n', stderr);
}
