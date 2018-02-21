/*
 * @(#) stdif/messaging_stdimpl/bound_remove_listener.c
 *
 * Messaging Interface - bound_remove_listener@1.0 standard implementation.
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
 * Standard implementation to remove a listener from the messaging instance.
 *
 * This will remove a listener with the same @{param bound}'s
 * message/interface, @{param callback} and @{param client_data}.
 *
 * @note	Using a @{param bound} that was not created from the same
 *		@{param messaging} instance will have undefined results.
 *
 * @note	This may only remove one listener if it has duplicates.
 *
 * @param	messaging	The messaging instance.
 * @param	bound		The bound message.
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
 * @see		@{func stdif_messaging_stdimpl_remove_listener__1_0(stdif_messaging_1_0_t *, const char *, const char *, iv_version_t, stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_stdimpl_remove_listener_by_id__1_0(stdif_messaging_1_0_t *, stdif_messaging_listener_id_t)}
 * @see		@{func stdif_messaging_stdimpl_add_listener__1_0(stdif_messaging_1_0_t *, const char *, const char *, iv_version_t , stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_stdimpl_bound_add_listener__1_0(stdif_messaging_1_0_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
extit_status_t
EXTIT_DECL
stdif_messaging_stdimpl_bound_remove_listener__1_0
(
	stdif_messaging_1_0_t *messaging,
	stdif_messaging_bound_t *bound,
	stdif_messaging_listener_t cb,
	void *client_data
)
{
	stdif_messaging_internal_t *	messaging_i;
	listener_entry_t **		l_entryp;
	listener_entry_t *		l_entry;
	listener_entry_t **		lid_entryp;
	listener_entry_t *		lid_entry;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	l_entryp = &bound->listeners;

	while((l_entry = *l_entryp) != NULL)
	{
		if((l_entry->callback == cb)
		 && (l_entry->client_data == client_data))
		{
			break;
		}
	}

	if(l_entry == NULL)
		return EXTIT_STATUS_NOTFOUND;

	*l_entryp = l_entry->next;

	/*
	 * Remove the ID entry with the matching listener
	 */
	lid_entryp = &messaging_i->lid_list;

	while((lid_entry = *lid_entryp) != NULL)
	{
		if(lid_entry == l_entry)
		{
			*lid_entryp = lid_entry->id_next;
			break;
		}
	}

	free(l_entry);

	if(++messaging_i->num_deletes == CLEANUP_DELETES)
	{
		stdif_messaging_stdimpl_cleanup(
			(stdif_messaging_t *) messaging);
	}

	return EXTIT_STATUS_OK;
}
