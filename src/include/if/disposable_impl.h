/*
 * @(#) if/disposable_impl.h
 *
 * Disposable Interface implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__disposable_impl_h
#define	__if__disposable_impl_h

#include <extit/base.h>
#include <if/disposable.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Disposable operations (1.0 component)
 */
typedef struct _if_disposable_ops_comp_1_0
{
	extit_status_t		(EXTIT_DECL *op_free)(
					if_disposable_1_0_t *disposable);
} if_disposable_ops_comp_1_0_t;


/*
 * Disposable operations (1.0)
 */
typedef struct _if_disposable_ops_1_0
{
	if_disposable_ops_comp_1_0_t	v0;		/* [1].0 component */
} if_disposable_ops_1_0_t;


/*
 * Disposable (base)
 */
struct _if_disposable
{
	/* base */
	iv_version_t			version;
};


/*
 * Disposable (1.0)
 */
struct _if_disposable_1_0
{
	/* base */
	iv_version_t			version;	/* 1.0+ */

	/* 1.0+ */
	if_disposable_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__disposable_impl_h */
