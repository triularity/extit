/*
 * @(#) if/messaging_stdimpl/ops.c
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <if/messaging_impl.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


EXTIT_EXPORT
if_messaging_ops_1_0_t		if_messaging_stdimpl_ops_1_0 =
{
	if_messaging_add_listener_stdimpl,
	if_messaging_remove_listener_stdimpl,
	if_messaging_remove_listener_by_id_stdimpl,
	if_messaging_has_listener_stdimpl,
	if_messaging_send_stdimpl,
	if_messaging_bind_stdimpl,
	if_messaging_unbind_stdimpl,
	if_messaging_bound_add_listener_stdimpl,
	if_messaging_bound_remove_listener_stdimpl,
	if_messaging_bound_has_listener_stdimpl,
	if_messaging_bound_send_stdimpl
};
