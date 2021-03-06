/*
 * @(#) extit/pmodule/version.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/pmodule.h>


iv_version_t
EXTIT_DECL
extit_get_version(void)
{
	return EXTIT_ABI_TARGET;
}
