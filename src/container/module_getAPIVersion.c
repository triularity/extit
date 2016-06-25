/*
 * @(#) container/module_getAPIVersion.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>

#include "container_impl.h"


EXTIT_EXPORT
iv_version_t
EXTIT_DECL
extit_module_getAPIVersion
(
	extit_module_t *module
)
{
	return module->descriptor->extit_version;
}
