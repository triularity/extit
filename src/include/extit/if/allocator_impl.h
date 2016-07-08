/*
 * @(#) extit/if/allocator_impl.h
 *
 * Allocator Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__allocator_impl_h
#define	__extit__if__allocator_impl_h

#include <extit/base.h>
#include <extit/if/allocator.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _extit_if_allocator_1_0_ops
{
	void *			(EXTIT_DECL *op_alloc)(
					extit_if_allocator_t *allocator,
					size_t size);

	void			(EXTIT_DECL *op_free)(
					extit_if_allocator_t *allocator,
					void *ptr);

	void *			(EXTIT_DECL *op_realloc)(
					extit_if_allocator_t *allocator,
					void *ptr,
					size_t size);

	void *			(EXTIT_DECL *op_zalloc)(
					extit_if_allocator_t *allocator,
					size_t size);

	void *			(EXTIT_DECL *op_dup)(
					extit_if_allocator_t *allocator,
					void *ptr,
					size_t size);
} extit_if_allocator_ops_1_0_t;


struct _extit_if_allocator_1_0
{
	iv_version_t			version;	/* 1.0+ */
	extit_if_allocator_ops_1_0_t *	ops;
};


#define	EXTIT_IF_ALLOCATOR_ALLOC(allocator, size)	\
			((allocator)->ops->op_alloc((allocator), (size)))

#define	EXTIT_IF_ALLOCATOR_DUP(allocator, ptr, size)	\
			((allocator)->ops->op_dup((allocator), (ptr), (size)))

#define	EXTIT_IF_ALLOCATOR_FREE(allocator, ptr)	\
			((allocator)->ops->op_free((allocator), (ptr)))

#define	EXTIT_IF_ALLOCATOR_REALLOC(allocator, ptr, size)	\
			((allocator)->ops->op_realloc((allocator), (ptr), (size)))

#define	EXTIT_IF_ALLOCATOR_ZALLOC(allocator, size)	\
			((allocator)->ops->op_zalloc((allocator), (size)))

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__allocator_impl_h */
