/*
 * @(#) stdimpl.h
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdimpl_h
#define	__stdimpl_h

#include <stddef.h>

#include <iv/base.h>
#include <iv/map.h>
#include <extit/base.h>
#include <extit/util.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	CLEANUP_DELETES			10

typedef struct _listener_entry		listener_entry_t;


struct _stdif_messaging_bound
{
	iv_version_t			version;
	const char *			mid;
	extit_refcount_t		bound_refcount;
	listener_entry_t *		listeners;
	stdif_messaging_bound_t *	next;
};


struct _listener_entry
{
	stdif_messaging_listener_t	callback;
	void *				client_data;
	stdif_messaging_listener_id_t	id;
	stdif_messaging_bound_t *	bound_entry;
	listener_entry_t *		next;
	listener_entry_t *		id_next;
};


typedef struct _stdif_messaging_internal
{
	stdif_messaging_1_0_t		pub;

	iv_idmap_t *			map;
	listener_entry_t *		lid_list;
	stdif_messaging_listener_id_t	lid_next;
	unsigned int			num_deletes;
} stdif_messaging_internal_t;


stdif_messaging_bound_t *	stdif_messaging_stdimpl_bound_acquire(
					stdif_messaging_bound_t **bound_listp,
					iv_version_t version,
					const char *mid);

void				stdif_messaging_stdimpl_bound_destroy(
					stdif_messaging_bound_t *bound_list);

stdif_messaging_bound_t *	stdif_messaging_stdimpl_bound_get(
					stdif_messaging_bound_t *bound_list,
					iv_version_t version);

stdif_messaging_bound_t *	stdif_messaging_stdimpl_bound_getmatch(
					stdif_messaging_bound_t *bound_list,
					iv_version_t version);

#ifdef	__cplusplus
}
#endif

#endif	/* !__stdimpl_h */
