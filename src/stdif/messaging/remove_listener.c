/*
 * @(#) stdif/messaging/remove_listener.c
 *
 * Messaging Interface - remove_listener@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


extit_status_t
EXTIT_DECL
stdif_messaging_remove_listener__1_0
(
	stdif_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	stdif_messaging_listener_t callback,
	void *client_data
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_remove_listener(
		IMPL(messaging), mid, iid, version, callback, client_data);

#undef	IMPL
}
