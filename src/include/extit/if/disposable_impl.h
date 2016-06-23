/*
 * @(#) extit/if/disposable_impl.h
 *
 * Disposable Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__disposable_impl_h
#define	__extit__if__disposable_impl_h

#include <extit/base.h>
#include <extit/if/disposable.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _extit_if_disposable_1_0_ops
{
	extit_status_t		(EXTIT_DECL *free)(
					extit_if_disposable_t *disposable);
} extit_if_disposable_ops_1_0_t;

struct _extit_if_disposable_1_0
{
	iv_version_t			version;	/* 1.0+ */
	extit_if_disposable_ops_1_0_t	ops;
	void *				priv;
};


#define	EXTIT_IF_DISPOSABLE_FREE(disposable)	\
			((disposable)->ops.free(disposable))

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__disposable_impl_h */
