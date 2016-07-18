/*
 * @(#) stdimpl.h
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdimpl_h
#define	__stdimpl_h

#include <stddef.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <extit/util.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	CLEANUP_DELETES			10

typedef struct _listener_entry		listener_entry_t;


struct _if_messaging_bound
{
	iv_version_t			version;
	const char *			mid;
	extit_refcount_t		bound_refcount;
	listener_entry_t *		listeners;
	if_messaging_bound_t *		next;
};


struct _listener_entry
{
	if_messaging_listener_t		callback;
	void *				client_data;
	if_messaging_listener_id_t	id;
	if_messaging_bound_t *		bound_entry;
	listener_entry_t *		next;
	listener_entry_t *		id_next;
};


typedef struct _keybuf
{
	unsigned char *			buf;
	size_t				len;
	size_t				capacity;
	unsigned char			def_buffer[256];
} keybuf_t;


typedef struct _if_messaging_internal
{
	if_messaging_1_0_t		pub;

	iv_keymap_t *			keymap;
	listener_entry_t *		lid_list;
	if_messaging_listener_id_t	lid_next;
	unsigned int			num_deletes;
	keybuf_t			keybuf;
} if_messaging_internal_t;


void				if_messaging_stdimpl_keybuf_init(
					keybuf_t *keybuf);

void				if_messaging_stdimpl_keybuf_release(
					keybuf_t *keybuf);

extit_status_t			if_messaging_stdimpl_keybuf_setids(
					keybuf_t *keybuf,
					const char *mid,
					const char *iid);

if_messaging_bound_t *		if_messaging_stdimpl_bound_acquire(
					if_messaging_bound_t **bound_listp,
					iv_version_t version,
					const char *mid);

void				if_messaging_stdimpl_bound_destroy(
					if_messaging_bound_t *bound_list);

if_messaging_bound_t *		if_messaging_stdimpl_bound_get(
					if_messaging_bound_t *bound_list,
					iv_version_t version);

if_messaging_bound_t *		if_messaging_stdimpl_bound_getmatch(
					if_messaging_bound_t *bound_list,
					iv_version_t version);

#ifdef	__cplusplus
}
#endif

#endif	/* !__stdimpl_h */
