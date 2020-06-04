/*
 * @(#) stdif/messaging_stdimpl/remove_listener.c
 *
 * Messaging Interface - remove_listener@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <iv/idmap.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


/**
 * Standard implementation to remove a listener from the messaging instance.
 *
 * This will remove a listener with the same @{param mid}, @{param iid},
 * @{param version}, @{param callback} and @{param client_data}.
 *
 * @param	messaging	The messaging instance.
 * @param	mid		The message ID.
 * @param	iid		The interface ID of the callback.
 * @param	version		The interface version of the callback.
 * @param	cb		The listener callback.
 * @param	client_data	Additional data passed to callback.
 *
 * @return	@{constant EXTIT_STATUS_OK} if a listener was found/removed,
 * 		@{constant EXTIT_STATUS_NOTFOUND} if no listener was found,
 *		@{constant EXTIT_STATUS_UNSUPPORTED} if the messaging
 *		interface version is not supported.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_stdimpl_remove_listener_by_id__1_0(stdif_messaging_1_0_t *, stdif_messaging_listener_id_t)}
 * @see		@{func stdif_messaging_stdimpl_bound_remove_listener__1_0(stdif_messaging_1_0_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_stdimpl_add_listener__1_0(stdif_messaging_1_0_t *, const char *, const char *, iv_version_t , stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_stdimpl_bound_add_listener__1_0(stdif_messaging_1_0_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
extit_status_t
EXTIT_DECL
stdif_messaging_stdimpl_remove_listener__1_0
(
	stdif_messaging_1_0_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	stdif_messaging_listener_t cb,
	void *client_data
)
{
	stdif_messaging_internal_t	*	messaging_i;
	stdif_messaging_bound_t *		bound_list;
	stdif_messaging_bound_t *		bound_entry;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	bound_list = (stdif_messaging_bound_t *)
		iv_idmap_get(messaging_i->map, mid, iid);

	if(bound_list == NULL)
		return EXTIT_STATUS_NOTFOUND;

	bound_entry = stdif_messaging_stdimpl_bound_get(bound_list, version);

	if(bound_entry == NULL)
		return EXTIT_STATUS_NOTFOUND;

	return stdif_messaging_stdimpl_bound_remove_listener__1_0(
		messaging, bound_entry, cb, client_data);
}
