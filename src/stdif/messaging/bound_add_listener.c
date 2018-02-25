/*
 * @(#) stdif/messaging/bound_add_listener.c
 *
 * Messaging Interface - bound_add_listener@1.0 wrapper.
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
 * Add a listener to a bound message.
 *
 * This is a convenience function that calls
 * @{param messaging}@{code ->ops->v0.op_bound_add_listener( ... )}
 *
 * @note	Using a @{param bound} that was not created from the same
 *		@{param messaging} instance will have undefined results.
 *
 * @note	This may not check for duplicate listeners. Adding such
 *		listeners could cause them to be called multiple times.
 *
 * @param	messaging	The messaging instance.
 * @param	bound		The bound message.
 * @param	callback	The listener callback.
 * @param	client_data	Additional data passed to callback.
 *
 * @return	A listener ID,
 * 		or @{constant STDIF_MESSAGING_LISTENER_ID_NONE} on error.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_remove_listener_by_id__1_0(stdif_messaging_t *, stdif_messaging_listener_id_t)}
 * @see		@{func stdif_messaging_bound_remove_listener__1_0(stdif_messaging_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
stdif_messaging_listener_id_t
EXTIT_DECL
stdif_messaging_bound_add_listener__1_0
(
	stdif_messaging_t *messaging,
	stdif_messaging_bound_t *bound,
	stdif_messaging_listener_t callback,
	void *client_data
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return STDIF_MESSAGING_LISTENER_ID_NONE;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_bound_add_listener(
		IMPL(messaging), bound, callback, client_data);

#undef	IMPL
}
