/*
 * @(#) stdif/messaging/bound_send.c
 *
 * Messaging Interface - bound_send@1.0 wrapper.
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
 * Send a bound message.
 *
 * This will call any registered listeners that are compatible with
 * @{param bound}'s message/interface.
 *
 * This is a convenience function that calls
 * @{param messaging}@{code ->ops->v0.op_bound_send( ... )}
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
 * @see		@{func stdif_messaging_send__1_0(stdif_messaging_t *, const char *, const char *, iv_version_t, void *)}
 * @see		@{func stdif_messaging_bound_send__1_0(stdif_messaging_t *, stdif_messaging_bound_t *, void *)}
 * @see		@{func stdif_messaging_add_listener__1_0(stdif_messaging_t *, const char *, const char *, iv_version_t , stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_bound_add_listener__1_0(stdif_messaging_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
extit_status_t
EXTIT_DECL
stdif_messaging_bound_send__1_0
(
	stdif_messaging_t *messaging,
	stdif_messaging_bound_t *bound,
	void *data
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_bound_send(
		IMPL(messaging), bound, data);

#undef	IMPL
}
