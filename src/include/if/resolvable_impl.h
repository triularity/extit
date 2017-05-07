/*
 * @(#) if/resolvable_impl.h
 *
 * Resolvable Interface API implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__resolvable_impl_h
#define	__if__resolvable_impl_h

#include <iv/base.h>
#include <if/resolvable.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Resolvable operations (1.0 component)
 */
typedef struct _if_resolvable_ops_comp_1_0
{
	void *			(EXTIT_DECL *op_get_interface)(
					if_resolvable_t *resolvable,
					const char *id,
					iv_version_t version);

	iv_version_t		(EXTIT_DECL *op_query_interface)(
					if_resolvable_t *resolvable,
					const char *id,
					iv_version_t base_version);
} if_resolvable_ops_comp_1_0_t;


/*
 * Resolvable operations (1.0)
 */
typedef struct _if_resolvable_ops_1_0
{
	if_resolvable_ops_comp_1_0_t	v0;		/* [1].0 component */
} if_resolvable_ops_1_0_t;


/*
 * Resolvable (1.0)
 */
struct _if_resolvable_1_0
{
	iv_version_t			version;	/* 1.0+ */
	if_resolvable_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__resolvable_impl_h */
