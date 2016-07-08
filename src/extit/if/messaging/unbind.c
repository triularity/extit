/*
 * @(#) extit/if/messaging/unbind.c
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
extit_status_t
EXTIT_DECL
extit_if_messaging_unbind
(
	extit_if_messaging_t *messaging,
	extit_if_messaging_bound_t bound
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IF_MESSAGING_UNBIND(messaging, bound);
}
