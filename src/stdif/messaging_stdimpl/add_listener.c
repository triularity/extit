/*
 * @(#) stdif/messaging_stdimpl/add_listener.c
 *
 * Messaging Interface - add_listener@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <iv/map.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


/**
 * Standard implementation to add a listener to the messaging instance.
 *
 * @note	This does not check for duplicate listeners. Adding such
 *		listeners will cause them to be called multiple times.
 *
 * @note	This implementation uses non-repeating listener IDs,
 *		which will cause new listeners to fail once the maximum
 *		value is reached (approximately 2 billion).
 *
 * @param	messaging	The messaging instance.
 * @param	mid		The message ID.
 * @param	iid		The interface ID of the callback.
 * @param	version		The interface version of the callback.
 * @param	cb		The listener callback.
 * @param	client_data	Additional data passed to callback.
 *
 * @return	A listener ID,
 * 		or @{constant STDIF_MESSAGING_LISTENER_ID_NONE} on error.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_stdimpl_remove_listener_by_id__1_0(stdif_messaging_1_0_t *, stdif_messaging_listener_id_t)}
 * @see		@{func stdif_messaging_stdimpl_remove_listener__1_0(stdif_messaging_1_0_t *, const char *, const char *, iv_version_t, stdif_messaging_listener_t, void *)}
 */
stdif_messaging_listener_id_t
EXTIT_DECL
stdif_messaging_stdimpl_add_listener__1_0
(
	stdif_messaging_1_0_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	stdif_messaging_listener_t cb,
	void *client_data
)
{
	stdif_messaging_internal_t *	messaging_i;
	stdif_messaging_bound_t **	bound_listp;
	stdif_messaging_bound_t *	bound_entry;
	const char *			internal_mid;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	bound_listp = (stdif_messaging_bound_t **)
		iv_map_acquire_valueptr(
			messaging_i->map, mid, iid, &internal_mid, NULL);

	if(bound_listp == NULL)
		return STDIF_MESSAGING_LISTENER_ID_NONE;

	bound_entry = stdif_messaging_stdimpl_bound_acquire(
		bound_listp, version, internal_mid);

	if(bound_entry == NULL)
		return STDIF_MESSAGING_LISTENER_ID_NONE;

	return stdif_messaging_stdimpl_bound_add_listener__1_0(
		messaging, bound_entry, cb, client_data);
}
