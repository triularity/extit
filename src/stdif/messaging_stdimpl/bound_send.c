/*
 * @(#) stdif/messaging_stdimpl/bound_send.c
 *
 * Messaging Interface - bound_send@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


/**
 * Standard implementation to send a bound message.
 *
 * This will call any registered listeners that are compatible with
 * @{param bound}'s message/interface.
 *
 * @note	Using a @{param bound} that was not created from the same
 *		@{param messaging} instance will have undefined results.
 *
 * @note	If @{param data} is not compatible with @{param bound}'s
 *		interface ID/version, then results are undefined.
 *
 * @param	messaging	The messaging instance.
 * @param	bound		The bound message.
 * @param	data		The data to send.
 *
 * @return	@{constant EXTIT_STATUS_OK} on success,
 *		@{constant EXTIT_STATUS_UNSUPPORTED} if the messaging
 *		interface version is not supported.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_stdimpl_send__1_0(stdif_messaging_1_0_t *, const char *, const char *, iv_version_t, void *)}
 * @see		@{func stdif_messaging_stdimpl_bound_send__1_0(stdif_messaging_1_0_t *, stdif_messaging_bound_t *, void *)}
 * @see		@{func stdif_messaging_stdimpl_add_listener__1_0(stdif_messaging_1_0_t *, const char *, const char *, iv_version_t , stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_stdimpl_bound_add_listener__1_0(stdif_messaging_1_0_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
extit_status_t
EXTIT_DECL
stdif_messaging_stdimpl_bound_send__1_0
(
	stdif_messaging_1_0_t *messaging,
	stdif_messaging_bound_t *bound,
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
