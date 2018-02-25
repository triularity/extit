/*
 * @(#) stdif/messaging/bound_has_listener.c
 *
 * Messaging Interface - bound_has_listener@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdbool.h>

#include <iv/base.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>

#ifdef	STDIF_PARANOID
#include <iv/util.h>
#endif


/**
 * Check if the messaging instance has any listeners currently registered
 * that are compatible with the given @{param bound}'s message/interface.
 *
 * This is a convenience function that calls
 * @{param messaging}@{code ->ops->v0.op_bound_has_listener( ... )}
 *
 * @note	Using a @{param bound} that was not created from the same
 *		@{param messaging} instance will have undefined results.
 *
 * @param	messaging	The messaging instance.
 * @param	bound		The bound message.
 *
 * @return	@{constant true} if there is at least one listener,
 * 		@{constant false} if there are none or there was an error.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_has_listener__1_0(stdif_messaging_t *, const char *, const char *, iv_version_t)}
 * @see		@{func stdif_messaging_add_listener__1_0(stdif_messaging_t *, const char *, const char *, iv_version_t, stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_bound_add_listener__1_0(stdif_messaging_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
bool
EXTIT_DECL
stdif_messaging_bound_has_listener__1_0
(
	stdif_messaging_t *messaging,
	stdif_messaging_bound_t *bound
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return false;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_bound_has_listener(
		IMPL(messaging), bound);

#undef	IMPL
}
