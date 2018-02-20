/*
 * @(#) stdif/allocator/dup.c
 *
 * Allocator Interface - dup@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <extit/base.h>
#include <stdif/allocator.h>
#include <stdif/allocator_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


/**
 * Allocate memory with the contents of existing memory.
 *
 * This is a convenience function that calls
 * @{param allocator}@{code ->ops->v0.op_dup( ... )}
 *
 * @note	The @{param size} may be @{literal 0} and implementations
 *		should ensure it does not fail, even if an underlying
 *		implementation normally would (such as @{func malloc()}).
 *
 * @param	allocator	The allocator instance.
 * @param	ptr		The start of memory to copy.
 * @param	size		The size of memory to allocate and copy
 *				(in bytes).
 *
 * @return	A pointer to the allocated memory,
 *		or @{constant NULL} on failure.
 */
void *
EXTIT_DECL
stdif_allocator_dup__1_0
(
	stdif_allocator_t *allocator,
	void *ptr,
	size_t size
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(allocator->version, STDIF_ALLOCATOR_ABI_1_0))
		return NULL;
#endif

#define	IMPL(x)		((stdif_allocator_1_0_t *) (x))

	return IMPL(allocator)->ops->v0.op_dup(IMPL(allocator), ptr, size);

#undef	IMPL
}
