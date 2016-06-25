/*
 * @(#) container/plugin_getContext.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/container.h>

#include "container_impl.h"


EXTIT_EXPORT
void *
EXTIT_DECL
extit_plugin_getContext
(
	extit_plugin_t *plugin
)
{
	return plugin->spi_ctx;
}
