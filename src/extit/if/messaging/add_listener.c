/*
 * @(#) extit/if/messaging/add_listener.c
 *
 * Messaging Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/if/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_if_messaging_listener_id_t
EXTIT_DECL
extit_if_messaging_addListener
(
	extit_if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	extit_if_messaging_listener_t callback,
	void *client_data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_IF_MESSAGING_LISTENER_ID_NONE;
#endif

	return EXTIT_IF_MESSAGING_ADD_LISTENER(
		messaging, mid, iid, version, callback, client_data);
}
