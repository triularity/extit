/*
 * @(#) if/messaging_stdimpl/remove_listener.c
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
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
if_messaging_stdimpl_remove_listener__1_0
(
	if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	if_messaging_listener_t cb,
	void *client_data
)
{
	if_messaging_internal_t	*	messaging_i;
	extit_status_t			status;
	if_messaging_bound_t *		bound_list;
	if_messaging_bound_t *		bound_entry;


	messaging_i = (if_messaging_internal_t *) messaging;

	if((status = if_messaging_stdimpl_keybuf_setids(
	 &messaging_i->keybuf, mid, iid)) != EXTIT_STATUS_OK)
	{
		return status;
	}

	bound_list = (if_messaging_bound_t *)
		iv_keymap_get(
			messaging_i->keymap,
			messaging_i->keybuf.buf,
			messaging_i->keybuf.len);

	if(bound_list == NULL)
		return EXTIT_STATUS_NOTFOUND;

	bound_entry = if_messaging_stdimpl_bound_get(bound_list, version);

	if(bound_entry == NULL)
		return EXTIT_STATUS_NOTFOUND;

	return if_messaging_stdimpl_bound_remove_listener__1_0(
		messaging, bound_entry, cb, client_data);
}
