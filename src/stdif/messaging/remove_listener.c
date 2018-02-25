/*
 * @(#) stdif/messaging/remove_listener.c
 *
 * Messaging Interface - remove_listener@1.0 wrapper.
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
 * Remove a listener from the messaging instance.
 *
 * This will remove a listener with the same @{param mid}, @{param iid},
 * @{param version}, @{param callback} and @{param client_data}.
 *
 * This is a convenience function that calls
 * @{param messaging}@{code ->ops->v0.op_bound_remove_listener( ... )}
 *
 * @param	messaging	The messaging instance.
 * @param	mid		The message ID.
 * @param	iid		The interface ID of the callback.
 * @param	version		The interface version of the callback.
 * @param	callback	The listener callback.
 * @param	client_data	Additional data passed to callback.
 *
 * @return	@{constant EXTIT_STATUS_OK} if a listener was found/removed,
 * 		@{constant EXTIT_STATUS_NOTFOUND} if no listener was found,
 *		@{constant EXTIT_STATUS_UNSUPPORTED} if the messaging
 *		interface version is not supported.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_remove_listener_by_id__1_0(stdif_messaging_t *, stdif_messaging_listener_id_t)}
 * @see		@{func stdif_messaging_bound_remove_listener__1_0(stdif_messaging_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_add_listener__1_0(stdif_messaging_t *, const char *, const char *, iv_version_t , stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_bound_add_listener__1_0(stdif_messaging_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
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
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_remove_listener(
		IMPL(messaging), mid, iid, version, callback, client_data);

#undef	IMPL
}
