/*
 * @(#) stdif/allocator/realloc.c
 *
 * Allocator Interface - realloc@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <extit/base.h>
#include <stdif/allocator.h>
#include <stdif/allocator_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


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
