/*
 * @(#) stdif/allocator_stdimpl/alloc.c
 *
 * Allocator Interface - alloc@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <stdif/allocator.h>
#include <stdif/allocator_impl.h>
#include <stdif/allocator_stdimpl.h>


/**
 * Allocate uninitialized memory using @{func malloc(size_t)}.
 *
 * @param	allocator	The allocator instance.
 * @param	size		The size of memory to allocate (in bytes).
 *
 * @return	A pointer to the allocated memory,
 *		or @{constant NULL} on failure.
 */
void *
EXTIT_DECL
stdif_allocator_stdimpl_alloc__1_0
(
	stdif_allocator_1_0_t *allocator,
	size_t size
)
{
#ifndef	EXTIT_MALLOC_0_SUCCEEDS
	/* Skip if malloc(0) returns non-NULL */
	if(size == 0)
		size = 1;
#endif

	return malloc(size);
}
