/*
 * @(#) if/messaging_stdimpl/bound_remove_listener.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_messaging_stdimpl_bound_remove_listener__1_0
(
	if_messaging_1_0_t *messaging,
	if_messaging_bound_t *bound,
	if_messaging_listener_t cb,
	void *client_data
)
{
	if_messaging_internal_t	*	messaging_i;
	listener_entry_t **		l_entryp;
	listener_entry_t *		l_entry;
	listener_entry_t **		lid_entryp;
	listener_entry_t *		lid_entry;


	messaging_i = (if_messaging_internal_t *) messaging;

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
		if_messaging_stdimpl_cleanup((if_messaging_t *) messaging);

	return EXTIT_STATUS_OK;
}
