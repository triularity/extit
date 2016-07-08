/*
 * @(#) extit/if/allocator/dup.c
 *
 * Allocator Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <extit/base.h>
#include <extit/if/allocator.h>
#include <extit/if/allocator_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
void *
EXTIT_DECL
extit_if_allocator_dup
(
	extit_if_allocator_t *allocator,
	void *ptr,
	size_t size
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(allocator->version, EXTIT_IF_ALLOCATOR_ABI_1_0))
		return NULL;
#endif

	return EXTIT_IF_ALLOCATOR_DUP(allocator, ptr, size);
}
