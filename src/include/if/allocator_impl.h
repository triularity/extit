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

typedef struct _if_allocator_1_0_ops
{
	void *			(EXTIT_DECL *op_alloc)(
					if_allocator_t *allocator,
					size_t size);

	void			(EXTIT_DECL *op_free)(
					if_allocator_t *allocator,
					void *ptr);

	void *			(EXTIT_DECL *op_realloc)(
					if_allocator_t *allocator,
					void *ptr,
					size_t size);

	void *			(EXTIT_DECL *op_zalloc)(
					if_allocator_t *allocator,
					size_t size);

	void *			(EXTIT_DECL *op_dup)(
					if_allocator_t *allocator,
					void *ptr,
					size_t size);
} if_allocator_ops_1_0_t;


struct _if_allocator_1_0
{
	iv_version_t			version;	/* 1.0+ */
	if_allocator_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__allocator_impl_h */
