/*
 * @(#) stdif/messaging_stdimpl/bind.c
 *
 * Messaging Interface - bind@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <iv/idmap.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


/**
 * Standard implementation to bind to a message ID and interface.
 *
 * This is used to pre-resolve a specific message/interface that can be
 * used multiple times without the overhead of resolving each time.
 *
 * @note	Bound messages are reference counted. An equal number of
 *		unbinds as binds must be done before internal resources are
 *		release.
 *
 * @param	messaging	The messaging instance.
 * @param	mid		The message ID.
 * @param	iid		The interface ID of the callback.
 * @param	version		The interface version of the callback.
 *
 * @return	A bound message,
 * 		or @{constant STDIF_MESSAGING_BOUND_NONE} on error.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_stdimpl_unbind__1_0(stdif_messaging_1_0_t *, stdif_messaging_bound_t *)}
 */
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
		iv_idmap_acquire_valueptr(
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
