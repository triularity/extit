/*
 * @(#) pmodule/dylib/module_defaults.c
 *
 * [lib]dylib specific implementations of container library.
 * Default extit_module_*() function implementations.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <stdbool.h>

#include <extit/base.h>
#include <extit/pmodule.h>
#include <extit/platform.h>


bool
EXTIT_DECL
extit_module_scan_fnfilter_default
(
	const char *basename,
	size_t length,
	void *client_data
)
{
	/*
	 * Must have a ".dylib" extension
	 */
	if(length < 7)
		return 0;

	return (EXTIT_FN_STRCMP(basename + length - 6, ".dylib") == 0);
}
