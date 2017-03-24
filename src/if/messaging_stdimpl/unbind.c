/*
 * @(#) if/messaging_stdimpl/unbind.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
if_messaging_stdimpl_unbind__1_0
(
	if_messaging_t *messaging,
	if_messaging_bound_t *bound
)
{
	extit_status_t			status;
	if_messaging_internal_t	*	messaging_i;


	status = extit_refcount_release(&bound->bound_refcount);

	if(status == EXTIT_STATUS_BUSY)
		status = EXTIT_STATUS_OK;

	if(status == EXTIT_STATUS_OK)
	{
		messaging_i = (if_messaging_internal_t *) messaging;

		if(++messaging_i->num_deletes == CLEANUP_DELETES)
			if_messaging_stdimpl_cleanup(messaging);
	}

	return status;
}
