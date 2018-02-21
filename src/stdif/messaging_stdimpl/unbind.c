/*
 * @(#) stdif/messaging_stdimpl/unbind.c
 *
 * Messaging Interface - unbind@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


/**
 * Standard implementation to unbind a bound message from this messaging
 * instance.
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
 * @see		@{func stdif_messaging_stdimpl_bind__1_0(stdif_messaging_1_0_t *, const char *, const char *, iv_version_t)}
 */
extit_status_t
EXTIT_DECL
stdif_messaging_stdimpl_unbind__1_0
(
	stdif_messaging_1_0_t *messaging,
	stdif_messaging_bound_t *bound
)
{
	extit_status_t			status;
	stdif_messaging_internal_t *	messaging_i;


	status = extit_refcount_release(&bound->bound_refcount);

	if(status == EXTIT_STATUS_OK)
	{
		messaging_i = (stdif_messaging_internal_t *) messaging;

		if(++messaging_i->num_deletes == CLEANUP_DELETES)
		{
			stdif_messaging_stdimpl_cleanup(
				(stdif_messaging_t *) messaging);
		}
	}

	return status;
}
