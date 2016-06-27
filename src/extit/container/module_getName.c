/*
 * @(#) container/module_getName.c
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
const char *
EXTIT_DECL
extit_module_getName
(
	extit_module_t *module
)
{
#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->api_version) != 1)
		return NULL;
#endif

	return ((extit_spi_descriptor_1_0_t *) module->descriptor)->name;
}
