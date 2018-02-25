/*
 * @(#) stdif/allocator_stdimpl/realloc.c
 *
 * Allocator Interface - realloc@1.0 standard implementation.
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
 * Reallocate memory to a new size using @{func realloc(void *, size_t)}.
 *
 * @param	allocator	The allocator instance.
 * @param	ptr		The previously allocated memory.
 * @param	size		The new allocation size (in bytes).
 *
 * @return	A pointer to the moved or same allocated memory address,
 *		or @{constant NULL} on failure.
 */
void *
EXTIT_DECL
stdif_allocator_stdimpl_realloc__1_0
(
	stdif_allocator_1_0_t *allocator,
	void *ptr,
	size_t size
)
{
#ifndef	EXTIT_MALLOC_0_SUCCEEDS
	/* Skip if malloc(0) returns non-NULL */
	if(size == 0)
		size = 1;
#endif

#ifdef	EXTIT_PARANOID
	if(ptr == NULL)
		return malloc(size);
#endif

	return realloc(ptr, size);
}
