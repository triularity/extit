/*
 * @(#) stdif/messaging_stdimpl/ops.c
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


/**
 * Standard implementation operators for a messaging 1.0 interface.
 *
 * @since	1.0
 */
stdif_messaging_ops_1_0_t	stdif_messaging_stdimpl_ops__1_0 =
{
	/* v0 */
	{
		/* op_add_listener */
		stdif_messaging_stdimpl_add_listener__1_0,

		/* op_remove_listener */
		stdif_messaging_stdimpl_remove_listener__1_0,

		/* op_remove_listener_by_id */
		stdif_messaging_stdimpl_remove_listener_by_id__1_0,

		/* op_has_listener */
		stdif_messaging_stdimpl_has_listener__1_0,

		/* op_send */
		stdif_messaging_stdimpl_send__1_0,

		/* op_bind */
		stdif_messaging_stdimpl_bind__1_0,

		/* op_unbind */
		stdif_messaging_stdimpl_unbind__1_0,

		/* op_bound_add_listener */
		stdif_messaging_stdimpl_bound_add_listener__1_0,

		/* op_bound_remove_listener */
		stdif_messaging_stdimpl_bound_remove_listener__1_0,

		/* op_bound_has_listener */
		stdif_messaging_stdimpl_bound_has_listener__1_0,

		/* op_bound_send */
		stdif_messaging_stdimpl_bound_send__1_0
	}
};
