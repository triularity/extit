/*
 * @(#) stdif/messaging_stdimpl/bound_add_listener.c
 *
 * Messaging Interface - bound_add_listener@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


/**
 * Standard implementation to add a listener to a bound message.
 *
 * @note	Using a @{param bound} that was not created from the same
 *		@{param messaging} instance will have undefined results.
 *
 * @note	This does not check for duplicate listeners. Adding such
 *		listeners will cause them to be called multiple times.
 *
 * @note	This implementation uses non-repeating listener IDs,
 *		which will cause new listeners to fail once the maximum
 *		value is reached (approximately 2 billion).
 *
 * @param	messaging	The messaging instance.
 * @param	bound		The bound message.
 * @param	cb		The listener callback.
 * @param	client_data	Additional data passed to callback.
 *
 * @return	A listener ID,
 * 		or @{constant STDIF_MESSAGING_LISTENER_ID_NONE} on error.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_stdimpl_remove_listener_by_id__1_0(stdif_messaging_1_0_t *, stdif_messaging_listener_id_t)}
 * @see		@{func stdif_messaging_stdimpl_bound_remove_listener__1_0(stdif_messaging_1_0_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
stdif_messaging_listener_id_t
EXTIT_DECL
stdif_messaging_stdimpl_bound_add_listener__1_0
(
	stdif_messaging_1_0_t *messaging,
	stdif_messaging_bound_t *bound,
	stdif_messaging_listener_t cb,
	void *client_data
)
{
	stdif_messaging_internal_t *	messaging_i;
	stdif_messaging_listener_id_t	lid;
	listener_entry_t *		l_entry;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	/*
	 * Wrapped around (no ID's left)?
	 */
	if((lid = messaging_i->lid_next) == STDIF_MESSAGING_LISTENER_ID_NONE)
	{
		/* XXX - Try to find a free ID before failing? */
		return STDIF_MESSAGING_LISTENER_ID_NONE;
	}

	if((l_entry = malloc(sizeof(listener_entry_t))) == NULL)
		return STDIF_MESSAGING_LISTENER_ID_NONE;

	l_entry->callback = cb;
	l_entry->client_data = client_data;
	l_entry->id = lid;
	l_entry->bound_entry = bound;

	l_entry->next = bound->listeners;
	bound->listeners = l_entry;

	l_entry->id_next = messaging_i->lid_list;
	messaging_i->lid_list = l_entry;

	messaging_i->lid_next++;

	return lid;
}
