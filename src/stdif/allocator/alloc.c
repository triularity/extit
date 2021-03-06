/*
 * @(#) stdif/allocator/alloc.c
 *
 * Allocator Interface - alloc@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <extit/base.h>
#include <stdif/allocator.h>
#include <stdif/allocator_impl.h>

#ifdef	STDIF_PARANOID
#include <iv/util.h>
#endif


/**
 * Allocate uninitialized memory.
 *
 * This is a convenience function that calls
 * @{param allocator}@{code ->ops->v0.op_alloc( ... )}
 *
 * @note	The @{param size} may be @{literal 0} and implementations
 *		should ensure it does not fail, even if an underlying
 *		implementation normally would (such as @{func malloc()}).
 *
 * @param	allocator	The allocator instance.
 * @param	size		The size of memory to allocate (in bytes).
 *
 * @return	A pointer to the allocated memory,
 *		or @{constant NULL} on failure.
 */
void *
EXTIT_DECL
stdif_allocator_alloc__1_0
(
	stdif_allocator_t *allocator,
	size_t size
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(allocator->version, STDIF_ALLOCATOR_ABI_1_0))
		return NULL;
#endif

#define	IMPL(x)		((stdif_allocator_1_0_t *) (x))

	return IMPL(allocator)->ops->v0.op_alloc(IMPL(allocator), size);

#undef	IMPL
}
