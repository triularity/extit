/*
 * @(#) stdif/allocator_impl.h
 *
 * Allocator Interface - implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__allocator_impl_h
#define	__stdif__allocator_impl_h

#include <extit/base.h>
#include <stdif/allocator.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Allocator operations (v1.0 component)
 */
typedef struct _stdif_allocator_ops_comp_1_0
{
	void *			(EXTIT_DECL *op_alloc)(
					stdif_allocator_1_0_t *allocator,
					size_t size);

	void			(EXTIT_DECL *op_free)(
					stdif_allocator_1_0_t *allocator,
					void *ptr);

	void *			(EXTIT_DECL *op_realloc)(
					stdif_allocator_1_0_t *allocator,
					void *ptr,
					size_t size);

	void *			(EXTIT_DECL *op_zalloc)(
					stdif_allocator_1_0_t *allocator,
					size_t size);

	void *			(EXTIT_DECL *op_dup)(
					stdif_allocator_1_0_t *allocator,
					void *ptr,
					size_t size);
} stdif_allocator_ops_comp_1_0_t;


/*
 * Allocator operations (v1.0)
 */
typedef struct _stdif_allocator_ops_1_0
{
	stdif_allocator_ops_comp_1_0_t	v0;		/* [1].0 components */
} stdif_allocator_ops_1_0_t;


/*
 * Allocator (base)
 */
struct _stdif_allocator
{
	iv_version_t			version;
};


/*
 * Allocator (v1.0)
 */
struct _stdif_allocator_1_0
{
	/* base */
	iv_version_t			version;	/* 1.0+ */

	/* 1.0+ */
	stdif_allocator_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__stdif__allocator_impl_h */
