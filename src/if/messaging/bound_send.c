/*
 * @(#) if/messaging/bound_send.c
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


extit_status_t
EXTIT_DECL
if_messaging_bound_send__1_0
(
	if_messaging_t *messaging,
	if_messaging_bound_t *bound,
	void *data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, IF_MESSAGING_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return messaging->ops_1_0->op_bound_send(messaging, bound, data);
}
