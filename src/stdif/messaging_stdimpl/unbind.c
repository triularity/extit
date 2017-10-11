/*
 * @(#) stdif/messaging_stdimpl/unbind.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


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
