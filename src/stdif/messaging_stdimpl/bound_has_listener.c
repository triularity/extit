/*
 * @(#) stdif/messaging_stdimpl/bound_has_listener.c
 *
 * Messaging Interface - bound_has_listener@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
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


/**
 * Standard implementation to check if the messaging instance has any
 * listeners currently registered that are compatible with the given
 * @{param bound}'s message/interface.
 *
 * @note	Using a @{param bound} that was not created from the same
 *		@{param messaging} instance will have undefined results.
 *
 * @param	messaging	The messaging instance.
 * @param	bound		The bound message.
 *
 * @return	@{constant true} if there is at least one listener,
 * 		@{constant false} if there are none or there was an error.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_stdimpl_has_listener__1_0(stdif_messaging_1_0_t *, const char *, const char *, iv_version_t)}
 * @see		@{func stdif_messaging_stdimpl_add_listener__1_0(stdif_messaging_1_0_t *, const char *, const char *, iv_version_t, stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_stdimpl_bound_add_listener__1_0(stdif_messaging_1_0_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
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
