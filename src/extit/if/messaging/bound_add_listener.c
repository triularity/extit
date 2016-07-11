/*
 * @(#) extit/if/messaging/bound_add_listener.c
 *
 * Messaging Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/if/messaging.h>
#include <extit/if/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_if_messaging_listener_id_t
EXTIT_DECL
extit_if_messaging_bound_add_listener
(
	extit_if_messaging_t *messaging,
	extit_if_messaging_bound_t bound,
	extit_if_messaging_listener_t callback,
	void *client_data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_ABI_1_0))
		return EXTIT_IF_MESSAGING_LISTENER_ID_NONE;
#endif

	return EXTIT_IF_MESSAGING_BOUND_ADD_LISTENER(
		messaging, bound, callback, client_data);
}