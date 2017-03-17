/*
 * @(#) container_stdimpl/ops.c
 *
 * Standard container implementation operations.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/container_stdimpl.h>


EXTIT_EXPORT
extit_container_ops_1_0_t	extit_container_stdimpl_ops_1_0 =
{
	extit_container_stdimpl_get_symbol__1_0,	/* op_get_symbol */
	extit_container_stdimpl_get_function__1_0,	/* op_get_function */
	extit_container_stdimpl_get_interface__1_0,	/* op_get_interface */
	extit_container_stdimpl_query_interface__1_0,	/* op_query_interface*/
	extit_container_stdimpl_log__1_0		/* op_log */
};
