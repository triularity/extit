/*
 * @(#) stdif/disposable_impl.h
 *
 * Disposable Interface - implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__disposable_impl_h
#define	__stdif__disposable_impl_h

#include <extit/base.h>
#include <stdif/disposable.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Disposable operations (v1.0 component)
 */
typedef struct _stdif_disposable_ops_comp_1_0
{
	extit_status_t		(EXTIT_DECL *op_free)(
					stdif_disposable_1_0_t *disposable);
} stdif_disposable_ops_comp_1_0_t;


/*
 * Disposable operations (v1.0)
 */
typedef struct _stdif_disposable_ops_1_0
{
	stdif_disposable_ops_comp_1_0_t	v0;		/* [1].0 component */
} stdif_disposable_ops_1_0_t;


/*
 * Disposable (base)
 */
struct _stdif_disposable
{
	/* base */
	iv_version_t			version;
};


/*
 * Disposable (v1.0)
 */
struct _stdif_disposable_1_0
{
	/* base */
	iv_version_t			version;	/* 1.0+ */

	/* 1.0+ */
	stdif_disposable_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__stdif__disposable_impl_h */
