/*
 * @(#) stdif/messaging_stdimpl/cleanup.c
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/idmap.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


/**
 * The cleanup callback used by @{func iv_idmap_cleanup}.
 *
 * @param	valueptr		A pointer to the value holder.
 */
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


/**
 * Remove any unused internal resources.
 *
 * To improve efficiency, this implementation defers scanning of removable
 * shared internal resources. This function is automatically called
 * periodically during normal modifications, but can be called explicitly
 * to force cleanup.
 *
 * @param	messaging		The messaging instance.
 *
 * @since	1.0
 */
void
EXTIT_DECL
stdif_messaging_stdimpl_cleanup
(
	stdif_messaging_t *messaging
)
{
	stdif_messaging_internal_t *	messaging_i;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	iv_idmap_cleanup(messaging_i->map, bound_cleaner);
	messaging_i->num_deletes = 0;
}
