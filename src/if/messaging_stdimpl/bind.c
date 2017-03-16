/*
 * @(#) if/messaging_stdimpl/bind.c
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


EXTIT_EXPORT
if_messaging_bound_t *
EXTIT_DECL
if_messaging_stdimpl_bind__1_0
(
	if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
)
{
	if_messaging_internal_t *	messaging_i;
	if_messaging_bound_t **		bound_listp;
	if_messaging_bound_t *		bound_entry;
	const unsigned char *		internal_key;


	messaging_i = (if_messaging_internal_t *) messaging;

	if(if_messaging_stdimpl_keybuf_setids(&messaging_i->keybuf, mid, iid)
	 != EXTIT_STATUS_OK)
	{
		return NULL;
	}

	bound_listp = (if_messaging_bound_t **)
		iv_keymap_acquire_valueptr(
			messaging_i->keymap,
			messaging_i->keybuf.buf,
			messaging_i->keybuf.len,
			&internal_key);

	if(bound_listp == NULL)
		return NULL;

	bound_entry = if_messaging_stdimpl_bound_acquire(
		bound_listp, version, (const char *) internal_key);

	if(bound_entry == NULL)
		return NULL;

	if(extit_refcount_add(&bound_entry->bound_refcount) != EXTIT_STATUS_OK)
		return NULL;

	return bound_entry;
}
