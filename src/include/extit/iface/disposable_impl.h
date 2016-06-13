/*
 * @(#) extit/iface/disposable_impl.h
 *
 * Disposable Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__iface__disposable_impl_h
#define	__extit__iface__disposable_impl_h

#include <extit/base.h>
#include <extit/iface/disposable.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _extit_iface_disposable_1_0_ops
{
	extit_status_t		(EXTIT_DECL *free)(
					extit_iface_disposable_t *iface);
} extit_iface_disposable_ops_1_0_t;

struct _extit_iface_disposable_1_0
{
	iv_version_t				version;	/* 1.0+ */
	void *					base;
	extit_iface_disposable_ops_1_0_t	ops;
};


#define	EXTIT_IFACE_DISPOSABLE_FREE(iface)	\
			((iface)->ops.free(iface))

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__iface__disposable_impl_h */
