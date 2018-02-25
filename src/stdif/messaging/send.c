/*
 * @(#) stdif/messaging/send.c
 *
 * Messaging Interface - send@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>

#ifdef	STDIF_PARANOID
#include <iv/util.h>
#endif


/**
 * Send a message.
 *
 * This will call any registered listeners that are compatible with
 * @{param mid}, @{param iid} and @{param version}.
 *
 * This is a convenience function that calls
 * @{param messaging}@{code ->ops->v0.op_send( ... )}
 *
 * @note	If @{param data} is not compatible with @{param bound}'s
 *		interface/version, then results are undefined.
 *
 * @param	messaging	The messaging instance.
 * @param	mid		The message ID.
 * @param	iid		The interface ID of the callback.
 * @param	version		The interface version of the callback.
 * @param	data		The data to send.
 *
 * @return	@{constant EXTIT_STATUS_OK} on success,
 *		@{constant EXTIT_STATUS_UNSUPPORTED} if the messaging
 *		interface version is not supported.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_bound_send__1_0(stdif_messaging_t *, stdif_messaging_bound_t *, void *)}
 * @see		@{func stdif_messaging_add_listener__1_0(stdif_messaging_t *, const char *, const char *, iv_version_t , stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_bound_add_listener__1_0(stdif_messaging_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
extit_status_t
EXTIT_DECL
stdif_messaging_send__1_0
(
	stdif_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	void *data
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_send(
		IMPL(messaging), mid, iid, version, data);

#undef	IMPL
}
