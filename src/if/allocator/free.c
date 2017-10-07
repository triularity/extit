/*
 * @(#) if/allocator/free.c
 *
 * Allocator Interface client API wrappers.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
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
if_allocator_free__1_0
(
	if_allocator_t *allocator,
	void *ptr
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(allocator->version, IF_ALLOCATOR_ABI_1_0))
		return;
#endif

#define	IMPL(x)		((if_allocator_1_0_t *) (x))

	IMPL(allocator)->ops->v0.op_free(IMPL(allocator), ptr);

#undef	IMPL
}
