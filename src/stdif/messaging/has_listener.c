/*
 * @(#) stdif/messaging/has_listener.c
 *
 * Messaging Interface - has_listener@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdbool.h>

#include <iv/base.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


bool
EXTIT_DECL
stdif_messaging_has_listener__1_0
(
	stdif_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(messaging->version, STDIF_MESSAGING_ABI_1_0))
		return false;
#endif

#define	IMPL(x)		((stdif_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_has_listener(
		IMPL(messaging), mid, iid, version);

#undef	IMPL
}
