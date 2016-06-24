/*
 * @(#) extit/if/resolvable_impl.h
 *
 * Resolvable Interface API implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__resolvable_impl_h
#define	__extit__if__resolvable_impl_h

#include <iv/base.h>
#include <extit/if/resolvable.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _extit_if_resolvable_ops_1_0
{
	void *			(EXTIT_DECL *get_interface)(
					extit_if_resolvable_t *resolvable,
					const char *id,
					iv_version_t version);

	iv_version_t		(EXTIT_DECL *query_interface)(
					extit_if_resolvable_t *resolvable,
					const char *id,
					iv_version_t base_version);
} extit_if_resolvable_ops_1_0_t;


struct _extit_if_resolvable_1_0
{
	iv_version_t			version;	/* 1.0+ */
	extit_if_resolvable_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#define	EXTIT_IF_RESOLVABLE_GET_INTERFACE(resolvable, id, version)	\
			((resolvable)->ops->get_interface((resolvable), (id), (version)))

#define	EXTIT_IF_RESOLVABLE_QUERY_INTERFACE(resolvable, id, base_version)	\
			((resolvable)->ops->query_interface((resolvable), (id), (base_version)))

#endif	/* !__extit__if__resolvable_impl_h */
