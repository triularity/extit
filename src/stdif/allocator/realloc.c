/*
 * @(#) stdif/allocator/realloc.c
 *
 * Allocator Interface - realloc@1.0 wrapper.
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
 * Reallocate memory to a new size.
 *
 * The implementation may attempt to resize in-place, returning the same
 * memory address. Otherwise, it will allocate new memory, copy the
 * existing contents (up to @{param size}, if smaller than the previous size),
 * release the old allocation and return the new address.
 * If the call fails, the existing allocation will remain unchanged.
 *
 * This is a convenience function that calls
 * @{param allocator}@{code ->ops->v0.op_realloc( ... )}
 *
 * @note	The @{param size} may be @{literal 0} and implementations
 *		should ensure it does not fail, even if an underlying
 *		implementation normally would (such as @{func malloc()}).
 *
 * @note	Any additional bytes allocated should be considered
 *		uninitialized, even if the original allocation was done using
 *		@{func stdif_allocator_zalloc__1_0(stdif_allocator_t *, size_t)}
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
stdif_allocator_realloc__1_0
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

	return IMPL(allocator)->ops->v0.op_realloc(IMPL(allocator), ptr, size);

#undef	IMPL
}
