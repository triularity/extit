/*
 * @(#) if/allocator/free.c
 *
 * Allocator Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

//-#include <stddef.h>
#include <extit/base.h>
#include <if/allocator.h>
#include <if/allocator_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
void
EXTIT_DECL
if_allocator_free
(
	if_allocator_t *allocator,
	void *ptr
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(allocator->version, IF_ALLOCATOR_ABI_1_0))
		return;
#endif

	IF_ALLOCATOR_FREE(allocator, ptr);
}
