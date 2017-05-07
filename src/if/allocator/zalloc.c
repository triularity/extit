/*
 * @(#) if/allocator/zalloc.c
 *
 * Allocator Interface client API wrappers.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <extit/base.h>
#include <if/allocator.h>
#include <if/allocator_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
void *
EXTIT_DECL
if_allocator_zalloc__1_0
(
	if_allocator_t *allocator,
	size_t size
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(allocator->version, IF_ALLOCATOR_ABI_1_0))
		return NULL;
#endif

	return allocator->ops->v0.op_zalloc(allocator, size);
}
