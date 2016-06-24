/*
 * @(#) extit/if/refcount_impl.h
 *
 * Reference Count Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__refcount_impl_h
#define	__extit__if__refcount_impl_h

#include <extit/base.h>
#include <extit/util.h>
#include <extit/if/refcount.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _extit_if_refcount_ops_1_0
{
	extit_status_t		(EXTIT_DECL *add)(
					extit_if_refcount_t *refcount);

	extit_refcount_t	(EXTIT_DECL *get)(
					extit_if_refcount_t *refcount);

	extit_status_t		(EXTIT_DECL *release)(
					extit_if_refcount_t *refcount);
} extit_if_refcount_ops_1_0_t;

struct _extit_if_refcount_1_0
{
	iv_version_t			version;	/* 1.0+ */
	extit_if_refcount_ops_1_0_t *	ops;
};


#define	EXTIT_IF_REFCOUNT_ADD(refcount)	\
			((refcount)->ops->add(refcount))

#define	EXTIT_IF_REFCOUNT_GET(refcount)	\
			((refcount)->ops->get(refcount))

#define	EXTIT_IF_REFCOUNT_RELEASE(refcount)	\
			((refcount)->ops->release(refcount))

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__refcount_impl_h */
