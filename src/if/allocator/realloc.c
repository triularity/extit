/*
 * @(#) if/allocator/realloc.c
 *
 * Allocator Interface client API wrappers.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
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
if_allocator_realloc__1_0
(
	if_allocator_t *allocator,
	void *ptr,
	size_t size
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(allocator->version, IF_ALLOCATOR_ABI_1_0))
		return NULL;
#endif

	return allocator->ops_1_0->op_realloc(allocator, ptr, size);
}
