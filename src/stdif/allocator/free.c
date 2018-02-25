/*
 * @(#) stdif/allocator/free.c
 *
 * Allocator Interface - free@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/allocator.h>
#include <stdif/allocator_impl.h>

#ifdef	STDIF_PARANOID
#include <iv/util.h>
#endif


/**
 * Release allocated memory.
 *
 * This is a convenience function that calls
 * @{param allocator}@{code ->ops->v0.op_free( ... )}
 *
 * @note	Using a @{param ptr} that was not allocated by this specific
 *		@{param allocator} instance or has already been freed will have
 *		undefined results.
 *
 * @param	allocator	The allocator instance.
 * @param	ptr		The previously allocated memory.
 *
 * @see		stdif_allocator_alloc__1_0(stdif_allocator_t *, void *)
 */
void
EXTIT_DECL
stdif_allocator_free__1_0
(
	stdif_allocator_t *allocator,
	void *ptr
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(allocator->version, STDIF_ALLOCATOR_ABI_1_0))
		return;
#endif

#define	IMPL(x)		((stdif_allocator_1_0_t *) (x))

	IMPL(allocator)->ops->v0.op_free(IMPL(allocator), ptr);

#undef	IMPL
}
