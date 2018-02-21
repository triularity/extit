/*
 * @(#) stdif/messaging_stdimpl/bound.c
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <iv/base.h>
#include <extit/util.h>

#include "internal.h"


/**
 * Find or create a bound entry on a list by version.
 *
 * @note	The entry's reference count will be unincremented, and
 *		should be incremented by the caller.
 *
 * @param	bound_listp	The head list pointer.
 * @param	version		The version to acquire for.
 * @param	mid		The message ID to store with a new entry.
 *
 * @return	A bound entry, or @{constant NULL} on error.
 *
 * @see		@{func stdif_messaging_stdimpl_bound_get(stdif_messaging_bound_t *, iv_version_t)}
 */
stdif_messaging_bound_t *
stdif_messaging_stdimpl_bound_acquire
(
	stdif_messaging_bound_t **bound_listp,
	iv_version_t version,
	const char *mid
)
{
	stdif_messaging_bound_t *	bound_entry;


	while((bound_entry = *bound_listp) != NULL)
	{
		if(bound_entry->version == version)
			return bound_entry;

		if(bound_entry->version < version)
			break;

		bound_listp = &bound_entry->next;
	}

	bound_entry = malloc(sizeof(stdif_messaging_bound_t));

	bound_entry->version = version;
	bound_entry->bound_refcount = EXTIT_REFCOUNT_NONE;
	bound_entry->listeners = NULL;
	bound_entry->mid = mid;

	bound_entry->next = *bound_listp;
	*bound_listp = bound_entry;

	return bound_entry;
}


/**
 * Destroy an entire bound entry list.
 *
 * @param	bound_list	The head of the list, or @{constant NULL}.
 */
void
stdif_messaging_stdimpl_bound_destroy
(
	stdif_messaging_bound_t *bound_list
)
{
	stdif_messaging_bound_t *	bound_next;
	listener_entry_t *		l_entry;
	listener_entry_t *		l_entry_next;


	while(bound_list != NULL)
	{
		l_entry = bound_list->listeners;

		while(l_entry != NULL)
		{
			l_entry_next = l_entry->next;
			free(l_entry);
			l_entry = l_entry_next;
		}

		bound_next = bound_list->next;
		free(bound_list);
		bound_list = bound_next;
	}
}


/**
 * Find a bound entry on a list by version.
 *
 * @param	bound_list	The head of the list, or @{constant NULL}.
 * @param	version		The version to match.
 *
 * @return	A bound entry, or @{constant NULL} if not found.
 *
 * @see		@{func stdif_messaging_stdimpl_bound_getmatch(stdif_messaging_bound_t *, iv_version_t)}
 */
stdif_messaging_bound_t *
stdif_messaging_stdimpl_bound_get
(
	stdif_messaging_bound_t *bound_list,
	iv_version_t version
)
{
	while(bound_list != NULL)
	{
		if(bound_list->version == version)
			return bound_list;

		if(bound_list->version < version)
			break;

		bound_list = bound_list->next;
	}

	return NULL;
}


/**
 * Find a bound entry on a list with a compatible version.
 *
 * @param	bound_list	The head of the list, or @{constant NULL}.
 * @param	version		The version to support.
 *
 * @return	A bound entry, or @{constant NULL} if not found.
 *
 * @see		@{func stdif_messaging_stdimpl_bound_get(stdif_messaging_bound_t *, iv_version_t)}
 */
stdif_messaging_bound_t *
stdif_messaging_stdimpl_bound_getmatch
(
	stdif_messaging_bound_t *bound_list,
	iv_version_t version
)
{
	unsigned int	major;
	iv_version_t	min_version;


	if((major = IV_VERSION_MAJOR(version)) != 0)
		min_version = IV_VERSION(major, 0);
	else
		min_version = version;

	while(bound_list != NULL)
	{
		if(bound_list->version < min_version)
			break;

		if(bound_list->version <= version)
			return bound_list;

		bound_list = bound_list->next;
	}

	return NULL;
}
