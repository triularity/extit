/*
 * @(#) if/refcount_impl.h
 *
 * Reference Count Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__refcount_impl_h
#define	__if__refcount_impl_h

#include <extit/base.h>
#include <extit/util.h>
#include <if/refcount.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _if_refcount_ops_1_0
{
	extit_status_t		(EXTIT_DECL *op_add)(
					if_refcount_t *refcount);

	extit_refcount_t	(EXTIT_DECL *op_get)(
					if_refcount_t *refcount);

	extit_status_t		(EXTIT_DECL *op_release)(
					if_refcount_t *refcount);
} if_refcount_ops_1_0_t;


struct _if_refcount_1_0
{
	iv_version_t			version;	/* 1.0+ */
	if_refcount_ops_1_0_t *		ops;
};


#define	IF_REFCOUNT_ADD(refcount)	\
			((refcount)->ops->op_add(refcount))

#define	IF_REFCOUNT_GET(refcount)	\
			((refcount)->ops->op_get(refcount))

#define	IF_REFCOUNT_RELEASE(refcount)	\
			((refcount)->ops->op_release(refcount))

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__refcount_impl_h */
