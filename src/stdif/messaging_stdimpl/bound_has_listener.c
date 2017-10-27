/*
 * @(#) stdif/messaging_stdimpl/bound_has_listener.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <stdbool.h>

#include <iv/base.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


bool
EXTIT_DECL
stdif_messaging_stdimpl_bound_has_listener__1_0
(
	stdif_messaging_1_0_t *messaging,
	stdif_messaging_bound_t *bound
)
{
	iv_version_t		min_version;
	unsigned int		major;


	min_version = bound->version;

	if((major = IV_VERSION_MAJOR(min_version)) != 0)
		min_version = IV_VERSION(major, 0);

	while(bound != NULL)
	{
		if(bound->version < min_version)

		if(bound->listeners != NULL)
			return true;

		bound = bound->next;
	}

	return false;
}
