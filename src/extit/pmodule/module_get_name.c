/*
 * @(#) extit/pmodule/module_get_name.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>
#include <extit/pmodule_impl.h>

#include "pmodule_internal.h"


const char *
EXTIT_DECL
extit_module_get_name
(
	extit_module_t *module
)
{
#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->abi_version) != 1)
		return NULL;
#endif

	return ((extit_pmodule_descriptor_1_0_t *) module->descriptor)->name;
}
