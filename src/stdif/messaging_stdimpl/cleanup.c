/*
 * @(#) stdif/messaging_stdimpl/cleanup.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


static
void
bound_cleaner(void **valueptr)
{
	stdif_messaging_bound_t **	bound_entryp;
	stdif_messaging_bound_t *	bound_entry;


	bound_entryp = (stdif_messaging_bound_t **) valueptr;

	while((bound_entry = *bound_entryp) != NULL)
	{
		if((bound_entry->listeners == NULL)
		 && extit_refcount_isnone(&bound_entry->bound_refcount))
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


void
EXTIT_DECL
stdif_messaging_stdimpl_cleanup
(
	stdif_messaging_t *messaging
)
{
	stdif_messaging_internal_t *	messaging_i;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	iv_map_cleanup(messaging_i->map, bound_cleaner);
	messaging_i->num_deletes = 0;
}
