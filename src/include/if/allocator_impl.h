/*
 * @(#) if/allocator_impl.h
 *
 * Allocator Interface implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__allocator_impl_h
#define	__if__allocator_impl_h

#include <extit/base.h>
#include <if/allocator.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Allocator operations (1.0 component)
 */
typedef struct _if_allocator_ops_comp_1_0
{
	void *			(EXTIT_DECL *op_alloc)(
					if_allocator_1_0_t *allocator,
					size_t size);

	void			(EXTIT_DECL *op_free)(
					if_allocator_1_0_t *allocator,
					void *ptr);

	void *			(EXTIT_DECL *op_realloc)(
					if_allocator_1_0_t *allocator,
					void *ptr,
					size_t size);

	void *			(EXTIT_DECL *op_zalloc)(
					if_allocator_1_0_t *allocator,
					size_t size);

	void *			(EXTIT_DECL *op_dup)(
					if_allocator_1_0_t *allocator,
					void *ptr,
					size_t size);
} if_allocator_ops_comp_1_0_t;


/*
 * Allocator operations (1.0)
 */
typedef struct _if_allocator_ops_1_0
{
	if_allocator_ops_comp_1_0_t	v0;		/* [1].0 components */
} if_allocator_ops_1_0_t;


/*
 * Allocator (base)
 */
struct _if_allocator
{
	iv_version_t			version;
};


/*
 * Allocator (1.0)
 */
struct _if_allocator_1_0
{
	/* base */
	iv_version_t			version;	/* 1.0+ */

	/* 1.0+ */
	if_allocator_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__allocator_impl_h */
