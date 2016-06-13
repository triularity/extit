/*
 * @(#) extit/iface/refcount_impl.h
 *
 * Reference Count Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__iface__refcount_impl_h
#define	__extit__iface__refcount_impl_h

#include <extit/base.h>
#include <extit/util.h>
#include <extit/iface/refcount.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _extit_iface_refcount_ops_1_0
{
	extit_status_t		(EXTIT_DECL *add)(
					extit_iface_refcount_t *iface);

	extit_refcount_t	(EXTIT_DECL *get)(
					extit_iface_refcount_t *iface);

	extit_status_t		(EXTIT_DECL *release)(
					extit_iface_refcount_t *iface);
} extit_iface_refcount_ops_1_0_t;

struct _extit_iface_refcount_1_0
{
	iv_version_t			version;	/* 1.0+ */
	void *				base;
	extit_iface_refcount_ops_1_0_t	ops;
};


#define	EXTIT_IFACE_REFCOUNT_ADD(iface)	\
			((iface)->ops.add(iface))

#define	EXTIT_IFACE_REFCOUNT_GET(iface)	\
			((iface)->ops.get(iface))

#define	EXTIT_IFACE_REFCOUNT_RELEASE(iface)	\
			((iface)->ops.release(iface))

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__iface__refcount_impl_h */
