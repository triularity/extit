/*
 * @(#) stdif/messaging_stdimpl/add_listener.c
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


stdif_messaging_listener_id_t
EXTIT_DECL
stdif_messaging_stdimpl_add_listener__1_0
(
	stdif_messaging_1_0_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	stdif_messaging_listener_t cb,
	void *client_data
)
{
	stdif_messaging_internal_t *	messaging_i;
	stdif_messaging_bound_t **	bound_listp;
	stdif_messaging_bound_t *	bound_entry;
	const char *			internal_mid;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	bound_listp = (stdif_messaging_bound_t **)
		iv_map_acquire_valueptr(
			messaging_i->map, mid, iid, &internal_mid, NULL);

	if(bound_listp == NULL)
		return STDIF_MESSAGING_LISTENER_ID_NONE;

	bound_entry = stdif_messaging_stdimpl_bound_acquire(
		bound_listp, version, internal_mid);

	if(bound_entry == NULL)
		return STDIF_MESSAGING_LISTENER_ID_NONE;

	return stdif_messaging_stdimpl_bound_add_listener__1_0(
		messaging, bound_entry, cb, client_data);
}
