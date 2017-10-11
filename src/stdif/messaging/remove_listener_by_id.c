/*
 * @(#) if/messaging/remove_listener_by_id.c
 *
 * Messaging Interface - remove_listener_by_id@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
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
if_messaging_remove_listener_by_id__1_0
(
	if_messaging_t *messaging,
	if_messaging_listener_id_t id
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(messaging->version, IF_MESSAGING_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((if_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_remove_listener_by_id(
		IMPL(messaging), id);

#undef	IMPL
}