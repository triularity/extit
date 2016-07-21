/*
 * @(#) container/module_set_flags.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "container_impl.h"


EXTIT_EXPORT
void
EXTIT_DECL
extit_module_set_flags
(
	extit_module_t *module,
	unsigned int flags
)
{
	module->flags = flags;
}
