/*
 * @(#) if/referenced_impl.h
 *
 * Referenced Interface implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__referenced_impl_h
#define	__if__referenced_impl_h

#include <extit/base.h>
#include <if/referenced.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Referenced operations (1.0 component)
 */
typedef struct _if_referenced_ops_comp_1_0
{
	extit_status_t		(EXTIT_DECL *op_add)(
					if_referenced_t *referenced);

	extit_status_t		(EXTIT_DECL *op_release)(
					if_referenced_t *referenced);
} if_referenced_ops_comp_1_0_t;


/*
 * Referenced operations (1.0)
 */
typedef struct _if_referenced_ops_1_0
{
	if_referenced_ops_comp_1_0_t	v0;		/* [1].0 component */
} if_referenced_ops_1_0_t;


/*
 * Referenced (1.0)
 */
struct _if_referenced_1_0
{
	iv_version_t			version;	/* 1.x */
	if_referenced_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__referenced_impl_h */
