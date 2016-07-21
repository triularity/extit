/*
 * @(#) container_stdimpl/ops.c
 *
 * Standard container implementation operations.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/container_stdimpl.h>


EXTIT_EXPORT
extit_container_ops_1_0_t	extit_container_stdimpl_ops_1_0 =
{
	extit_container_get_symbol_stdimpl,		/* get_symbol */
	extit_container_get_function_stdimpl,		/* get_function */
	extit_container_get_interface_stdimpl,		/* get_interface */
	extit_container_query_interface_stdimpl,	/* query_interface */
	extit_container_log_stdimpl			/* log */
};
