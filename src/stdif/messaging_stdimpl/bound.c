/*
 * @(#) stdif/messaging_stdimpl/bound.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <iv/base.h>
#include <extit/util.h>

#include "internal.h"


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
