/*
 * @(#) extit/if/messaging/bind.c
 *
 * Messaging Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/if/messaging.h>
#include <extit/if/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_if_messaging_bound_t
EXTIT_DECL
extit_if_messaging_bind
(
	extit_if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_ABI_1_0))
		return EXTIT_IF_MESSAGING_BOUND_NONE;
#endif

	return EXTIT_IF_MESSAGING_BIND(messaging, mid, iid, version);
}