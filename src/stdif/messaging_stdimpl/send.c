/*
 * @(#) if/messaging_stdimpl/send.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


extit_status_t
EXTIT_DECL
if_messaging_stdimpl_send__1_0
(
	if_messaging_1_0_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
        void *data
)
{
	if_messaging_internal_t *	messaging_i;
	if_messaging_bound_t *		bound_list;
	if_messaging_bound_t *		bound_entry;


	messaging_i = (if_messaging_internal_t *) messaging;

	bound_list = (if_messaging_bound_t *)
		iv_map_get(messaging_i->map, mid, iid);

	if(bound_list == NULL)
		return EXTIT_STATUS_OK;

	bound_entry =
		if_messaging_stdimpl_bound_getmatch(bound_list, version);

	if(bound_entry == NULL)
		return EXTIT_STATUS_OK;

	return if_messaging_stdimpl_bound_send__1_0(
		messaging, bound_entry, data);
}