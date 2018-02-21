/*
 * @(#) stdif/messaging/unbind.c
 *
 * Messaging Interface - unbind@1.0 wrapper.
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
 * Unbind a bound message from this messaging instance.
 *
 * This is a convenience function that calls
 * @{param messaging}@{code ->ops->v0.op_unbind( ... )}
 *
 * @note	Bound messages are reference counted. An equal number of
 *		unbinds as binds must be done before internal resources are
 *		release.
 *
 * @note	Using a @{param bound} that was not created from the same
 *		@{param messaging} instance will have undefined results.
 *
 * @param	messaging	The messaging instance.
 * @param	bound		The bound message.
 *
 * @return	A bound message,
 * 		or @{constant STDIF_MESSAGING_BOUND_NONE} on error.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_bind__1_0(stdif_messaging_t *, const char *, const char *, iv_version_t)}
 */
extit_status_t
EXTIT_DECL
stdif_messaging_unbind__1_0
(
	stdif_messaging_t *messaging,
	stdif_messaging_bound_t *bound
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_unbind(IMPL(messaging), bound);

#undef	IMPL
}
