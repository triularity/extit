/*
 * @(#) iv/repository/internal.h
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__internal_h
#define	__internal_h

#include <iv/base.h>
#include <iv/util.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	DELETES_PER_CLEANUP	5


typedef struct _version_node	version_node_t;

struct _version_node
{
	iv_version_t		version;
	void *			value;
	version_node_t *	next;
};


struct _iv_repository
{
	iv_keymap_t *		keymap;
	unsigned int		num_deletes;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__internal_h */
