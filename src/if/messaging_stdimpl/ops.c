/*
 * @(#) if/messaging_stdimpl/ops.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <if/messaging_impl.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


EXTIT_EXPORT
if_messaging_ops_1_0_t		if_messaging_stdimpl_ops__1_0 =
{
	if_messaging_stdimpl_add_listener__1_0,
	if_messaging_stdimpl_remove_listener__1_0,
	if_messaging_stdimpl_remove_listener_by_id__1_0,
	if_messaging_stdimpl_has_listener__1_0,
	if_messaging_stdimpl_send__1_0,
	if_messaging_stdimpl_bind__1_0,
	if_messaging_stdimpl_unbind__1_0,
	if_messaging_stdimpl_bound_add_listener__1_0,
	if_messaging_stdimpl_bound_remove_listener__1_0,
	if_messaging_stdimpl_bound_has_listener__1_0,
	if_messaging_stdimpl_bound_send__1_0
};
