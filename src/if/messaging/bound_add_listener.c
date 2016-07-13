/*
 * @(#) if/messaging/bound_add_listener.c
 *
 * Messaging Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
if_messaging_listener_id_t
EXTIT_DECL
if_messaging_bound_add_listener
(
	if_messaging_t *messaging,
	if_messaging_bound_t bound,
	if_messaging_listener_t callback,
	void *client_data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, IF_MESSAGING_ABI_1_0))
		return IF_MESSAGING_LISTENER_ID_NONE;
#endif

	return IF_MESSAGING_BOUND_ADD_LISTENER(
		messaging, bound, callback, client_data);
}