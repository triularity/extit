/*
 * @(#) container/dl/module_defaults.c
 *
 * [lib]dl specific implementations of container library.
 * Default extit_module_*() function implementations.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/platform.h>


EXTIT_EXPORT
extit_bool_t
EXTIT_DECL
extit_module_scan_fnfilter_default
(
	const char *basename,
	size_t length
)
{
	/*
	 * Must have a ".so" extension
	 */
	if(length < 4)
		return 0;

	return (EXTIT_FN_STRCMP(basename + length - 3, ".so") == 0);
}
