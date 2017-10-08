/*
 * @(#) extit/pmodule/module_get_flags.c
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


unsigned int
EXTIT_DECL
extit_module_get_flags
(
	extit_module_t *module
)
{
	return module->flags;
}
