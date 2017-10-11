/*
 * @(#) stdif/messaging_stdimpl/bound_add_listener.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
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
