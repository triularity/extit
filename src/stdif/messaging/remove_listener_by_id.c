/*
 * @(#) stdif/messaging/remove_listener_by_id.c
 *
 * Messaging Interface - remove_listener_by_id@1.0 wrapper.
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
 * Remove a listener from the messaging instance with matching listener ID.
 *
 * This is a convenience function that calls
 * @{param messaging}@{code ->ops->v0.op_remove_listener_by_id( ... )}
 *
 * @note	Using an @{param id} that was not created from the same
 *		@{param messaging} instance will have undefined results.
 *
 * @param	messaging	The messaging instance.
 * @param	id		The listener ID.
 *
 * @return	@{constant EXTIT_STATUS_OK} if a listener was found/removed,
 * 		@{constant EXTIT_STATUS_NOTFOUND} if no listener was found,
 *		@{constant EXTIT_STATUS_UNSUPPORTED} if the messaging
 *		interface version is not supported.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_remove_listener__1_0(stdif_messaging_t *, const char *, const char *, iv_version_t, stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_bound_remove_listener__1_0(stdif_messaging_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_add_listener__1_0(stdif_messaging_t *, const char *, const char *, iv_version_t , stdif_messaging_listener_t, void *)}
 * @see		@{func stdif_messaging_bound_add_listener__1_0(stdif_messaging_t *, stdif_messaging_bound_t *, stdif_messaging_listener_t, void *)}
 */
extit_status_t
EXTIT_DECL
stdif_messaging_remove_listener_by_id__1_0
(
	stdif_messaging_t *messaging,
	stdif_messaging_listener_id_t id
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_remove_listener_by_id(
		IMPL(messaging), id);

#undef	IMPL
}
