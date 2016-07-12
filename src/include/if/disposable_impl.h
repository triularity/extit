/*
 * @(#) if/disposable_impl.h
 *
 * Disposable Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__disposable_impl_h
#define	__if__disposable_impl_h

#include <extit/base.h>
#include <if/disposable.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _if_disposable_1_0_ops
{
	extit_status_t		(EXTIT_DECL *op_free)(
					if_disposable_t *disposable);
} if_disposable_ops_1_0_t;


struct _if_disposable_1_0
{
	iv_version_t			version;	/* 1.0+ */
	if_disposable_ops_1_0_t *	ops;
};


#define	IF_DISPOSABLE_FREE(disposable)	\
			((disposable)->ops->op_free(disposable))

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__disposable_impl_h */
