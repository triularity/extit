/*
 * @(#) extit/pmodule/module_get_effective_abi_version.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/pmodule.h>

#include "pmodule_internal.h"


iv_version_t
EXTIT_DECL
extit_module_get_effective_abi_version
(
	extit_module_t *module
)
{
	return module->abi_version;
}
