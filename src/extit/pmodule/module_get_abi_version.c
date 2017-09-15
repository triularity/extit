/*
 * @(#) extit/pmodule/module_get_abi_version.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "pmodule_internal.h"


EXTIT_EXPORT
iv_version_t
EXTIT_DECL
extit_module_get_abi_version
(
	extit_module_t *module
)
{
	return module->descriptor->extit_version;
}
