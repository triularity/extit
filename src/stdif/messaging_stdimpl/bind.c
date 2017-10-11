/*
 * @(#) stdif/messaging_stdimpl/bind.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


stdif_messaging_bound_t *
EXTIT_DECL
stdif_messaging_stdimpl_bind__1_0
(
	stdif_messaging_1_0_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
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
		return NULL;

	bound_entry = stdif_messaging_stdimpl_bound_acquire(
		bound_listp, version, internal_mid);

	if(bound_entry == NULL)
		return NULL;

	if(extit_refcount_add(&bound_entry->bound_refcount) != EXTIT_STATUS_OK)
		return NULL;

	return bound_entry;
}
