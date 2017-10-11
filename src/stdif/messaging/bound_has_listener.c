/*
 * @(#) stdif/messaging/bound_has_listener.c
 *
 * Messaging Interface - bound_has_listener@1.0 wrapper.
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


extit_bool_t
EXTIT_DECL
stdif_messaging_bound_has_listener__1_0
(
	stdif_messaging_t *messaging,
	stdif_messaging_bound_t *bound
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return EXTIT_FALSE;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_bound_has_listener(
		IMPL(messaging), bound);

#undef	IMPL
}
