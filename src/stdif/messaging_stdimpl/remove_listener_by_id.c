/*
 * @(#) stdif/messaging_stdimpl/remove_listener_by_id.c
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


extit_status_t
EXTIT_DECL
stdif_messaging_stdimpl_remove_listener_by_id__1_0
(
	stdif_messaging_1_0_t *messaging,
	stdif_messaging_listener_id_t id
)
{
	stdif_messaging_internal_t *	messaging_i;
	listener_entry_t **		lid_entryp;
	listener_entry_t *		lid_entry;
	listener_entry_t **		l_entryp;
	listener_entry_t *		l_entry;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	/*
	 * Find/remove ID entry
	 */
	lid_entryp = &messaging_i->lid_list;

	while((lid_entry = *lid_entryp) != NULL)
	{
		if(lid_entry->id == id)
			break;

		lid_entryp = &lid_entry->id_next;
	}

	if(lid_entry == NULL)
		return EXTIT_STATUS_NOTFOUND;

	*lid_entryp = lid_entry->id_next;


	/*
	 * Unlink the matching listener entry
	 */
	l_entryp = &lid_entry->bound_entry->listeners;

	while((l_entry = *l_entryp) != NULL)
	{
		if(l_entry == lid_entry)
		{
			*l_entryp = l_entry->next;
			break;
		}
	}


	free(lid_entry);

	if(++messaging_i->num_deletes == CLEANUP_DELETES)
	{
		stdif_messaging_stdimpl_cleanup(
			(stdif_messaging_t *) messaging);
	}

	return EXTIT_STATUS_OK;
}
