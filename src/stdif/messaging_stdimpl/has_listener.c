/*
 * @(#) stdif/messaging_stdimpl/has_listener.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


extit_bool_t
EXTIT_DECL
stdif_messaging_stdimpl_has_listener__1_0
(
	stdif_messaging_1_0_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
)
{
	stdif_messaging_internal_t *	messaging_i;
	stdif_messaging_bound_t *	bound_list;
	stdif_messaging_bound_t *	bound_entry;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	bound_list = (stdif_messaging_bound_t *)
		iv_map_get(messaging_i->map, mid, iid);

	if(bound_list == NULL)
		return EXTIT_FALSE;

	bound_entry = stdif_messaging_stdimpl_bound_get(bound_list, version);

	if(bound_entry == NULL)
		return EXTIT_FALSE;

	return stdif_messaging_stdimpl_bound_has_listener__1_0(
		messaging, bound_entry);
}
