/*
 * @(#) if/messaging_stdimpl/bound_has_listener.c
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


EXTIT_EXPORT
extit_bool_t
EXTIT_DECL
if_messaging_bound_has_listener_stdimpl
(
	if_messaging_t *messaging,
	if_messaging_bound_t *bound
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
			return EXTIT_TRUE;

		bound = bound->next;
	}

	return EXTIT_FALSE;
}
