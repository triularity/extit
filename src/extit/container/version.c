/*
 * @(#) container/version.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>


EXTIT_EXPORT
iv_version_t
EXTIT_DECL
extit_get_version(void)
{
	return EXTIT_API_VERSION;
}
