/*
 * @(#) stdif/referenced_impl.h
 *
 * Referenced Interface - implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__referenced_impl_h
#define	__stdif__referenced_impl_h

#include <extit/base.h>
#include <stdif/referenced.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Referenced operations (v1.0 component)
 */
typedef struct _stdif_referenced_ops_comp_1_0
{
	extit_status_t		(EXTIT_DECL *op_add)(
					stdif_referenced_1_0_t *referenced);

	extit_status_t		(EXTIT_DECL *op_release)(
					stdif_referenced_1_0_t *referenced);
} stdif_referenced_ops_comp_1_0_t;


/*
 * Referenced operations (v1.0)
 */
typedef struct _stdif_referenced_ops_1_0
{
	stdif_referenced_ops_comp_1_0_t	v0;		/* [1].0 component */
} stdif_referenced_ops_1_0_t;


/*
 * Referenced (base)
 */
struct _stdif_referenced
{
	iv_version_t			version;
};


/*
 * Referenced (v1.0)
 */
struct _stdif_referenced_1_0
{
	/* base */
	iv_version_t			version;	/* 1.x */

	/* 1.0+ */
	stdif_referenced_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__stdif__referenced_impl_h */
