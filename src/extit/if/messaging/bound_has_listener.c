/*
 * @(#) extit/if/messaging/bound_has_listener.c
 *
 * Messaging Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/if/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_bool_t
EXTIT_DECL
extit_if_messaging_boundHasListener
(
	extit_if_messaging_t *messaging,
	extit_if_messaging_bound_t bound
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_FALSE;
#endif

	return EXTIT_IF_MESSAGING_BOUND_HAS_LISTENER(messaging, bound);
}
