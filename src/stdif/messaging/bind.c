/*
 * @(#) stdif/messaging/bind.c
 *
 * Messaging Interface - bind@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


/**
 * Bind to a message ID and interface.
 *
 * This is used to pre-resolve a specific message/interface that can be
 * used multiple times without the overhead of resolving each time.
 *
 * This is a convenience function that calls
 * @{param messaging}@{code ->ops->v0.op_bind( ... )}
 *
 * @note	Bound messages are reference counted. An equal number of
 *		unbinds as binds must be done before internal resources are
 *		release.
 *
 * @param	messaging	The messaging instance.
 * @param	mid		The message ID.
 * @param	iid		The interface ID of the callback.
 * @param	version		The interface version of the callback.
 *
 * @return	A bound message,
 * 		or @{constant STDIF_MESSAGING_BOUND_NONE} on error.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_unbind__1_0(stdif_messaging_t *, stdif_messaging_bound_t *)}
 */
stdif_messaging_bound_t *
EXTIT_DECL
stdif_messaging_bind__1_0
(
	stdif_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return STDIF_MESSAGING_BOUND_NONE;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_bind(
		IMPL(messaging), mid, iid, version);

#undef	IMPL
}
