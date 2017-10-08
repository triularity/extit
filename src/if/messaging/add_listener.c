/*
 * @(#) if/messaging/add_listener.c
 *
 * Messaging Interface client API wrappers.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


if_messaging_listener_id_t
EXTIT_DECL
if_messaging_add_listener__1_0
(
	if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	if_messaging_listener_t callback,
	void *client_data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, IF_MESSAGING_ABI_1_0))
		return IF_MESSAGING_LISTENER_ID_NONE;
#endif

#define	IMPL(x)		((if_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_add_listener(
		IMPL(messaging), mid, iid, version, callback, client_data);

#undef	IMPL
}
