/*
 * @(#) if/messaging_stdimpl/bound_send.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_messaging_stdimpl_bound_send__1_0
(
	if_messaging_1_0_t *messaging,
	if_messaging_bound_t *bound,
        void *data
)
{
	iv_version_t		min_version;
	unsigned int		major;
	listener_entry_t *	l_entry;
	const char *		mid;


	min_version = bound->version;

	if((major = IV_VERSION_MAJOR(min_version)) != 0)
		min_version = IV_VERSION(major, 0);

	mid = bound->mid;

	while(bound != NULL)
	{
		if(bound->version < min_version)
			break;

		l_entry = bound->listeners;

		while(l_entry != NULL)
		{
			l_entry->callback(mid, data, l_entry->client_data);
			l_entry = l_entry->next;
		}

		bound = bound->next;
	}

	return EXTIT_STATUS_OK;
}
