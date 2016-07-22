/*
 * @(#) if/referenced_impl.h
 *
 * Referenced Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__referenced_impl_h
#define	__if__referenced_impl_h

#include <extit/base.h>
#include <if/referenced.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _if_referenced_ops_1_0
{
	extit_status_t		(EXTIT_DECL *op_add)(
					if_referenced_t *referenced);

	extit_status_t		(EXTIT_DECL *op_release)(
					if_referenced_t *referenced);
} if_referenced_ops_1_0_t;


struct _if_referenced_1_0
{
	iv_version_t			version;	/* 1.x */
	if_referenced_ops_1_0_t *	ops;
};


#define	IF_REFERENCED_ADD(referenced)	\
			((referenced)->ops->op_add(referenced))

#define	IF_REFERENCED_RELEASE(referenced)	\
			((referenced)->ops->op_release(referenced))

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__referenced_impl_h */
