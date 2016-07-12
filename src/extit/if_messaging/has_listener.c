/*
 * @(#) extit/if_messaging/has_listener.c
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
extit_bool_t
EXTIT_DECL
extit_if_messaging_has_listener
(
	extit_if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_ABI_1_0))
		return EXTIT_FALSE;
#endif

	return EXTIT_IF_MESSAGING_HAS_LISTENER(messaging, mid, iid, version);
}
