/*
 * @(#) if/messaging_stdimpl/cleanup.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


static
void
bound_cleaner(void **valueptr)
{
	if_messaging_bound_t **	bound_entryp;
	if_messaging_bound_t *	bound_entry;


	bound_entryp = (if_messaging_bound_t **) valueptr;

	while((bound_entry = *bound_entryp) != NULL)
	{
		if((bound_entry->listeners == NULL)
		 && (bound_entry->bound_refcount == EXTIT_REFCOUNT_NONE))
		{
			*bound_entryp = bound_entry->next;
			free(bound_entry);
		}
		else
		{
			bound_entryp = &bound_entry->next;
		}
	}
}


EXTIT_EXPORT
void
EXTIT_DECL
if_messaging_stdimpl_cleanup
(
	if_messaging_t *messaging
)
{
	if_messaging_internal_t *	messaging_i;


	messaging_i = (if_messaging_internal_t *) messaging;

	iv_map_cleanup(messaging_i->map, bound_cleaner);
	messaging_i->num_deletes = 0;
}
