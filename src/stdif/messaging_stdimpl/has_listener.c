/*
 * @(#) stdif/messaging_stdimpl/has_listener.c
 *
 * Messaging Interface - has_listener@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <stdbool.h>

#include <iv/base.h>
#include <iv/map.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


/**
 * Standard implementation to check if the messaging instance has any
 * listeners currently registered that are compatible with the given
 * message/interface.
 *
 * @param	messaging	The messaging instance.
 * @param	mid		The message ID.
 * @param	iid		The interface ID of the callback.
 * @param	version		The interface version of the callback.
 *
 * @return	@{constant true} if there is at least one listener,
 * 		@{constant false} if there are none or there was an error.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_stdimpl_bound_has_listener__1_0(stdif_messaging_1_0_t *, stdif_messaging_bound_t *)}
 * @see		@{func stdif_messaging_stdimpl_add_listener__1_0(stdif_messaging_1_0_t *, const char *, const char *, iv_version_t, stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_stdimpl_bound_add_listener__1_0(stdif_messaging_1_0_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
bool
EXTIT_DECL
stdif_messaging_stdimpl_has_listener__1_0
(
	stdif_messaging_1_0_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
)
{
	stdif_messaging_internal_t *	messaging_i;
	stdif_messaging_bound_t *	bound_list;
	stdif_messaging_bound_t *	bound_entry;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	bound_list = (stdif_messaging_bound_t *)
		iv_map_get(messaging_i->map, mid, iid);

	if(bound_list == NULL)
		return false;

	bound_entry = stdif_messaging_stdimpl_bound_get(bound_list, version);

	if(bound_entry == NULL)
		return false;

	return stdif_messaging_stdimpl_bound_has_listener__1_0(
		messaging, bound_entry);
}
