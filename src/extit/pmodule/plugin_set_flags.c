/*
 * @(#) extit/pmodule/plugin_set_flags.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "pmodule_internal.h"


void
EXTIT_DECL
extit_plugin_set_flags
(
	extit_plugin_t *plugin,
	unsigned int flags
)
{
	plugin->flags = flags;
}
