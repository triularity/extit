/*
 * @(#) stdif/allocator/free.c
 *
 * Allocator Interface - free@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

//-#include <stddef.h>
#include <extit/base.h>
#include <stdif/allocator.h>
#include <stdif/allocator_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


void
EXTIT_DECL
stdif_allocator_free__1_0
(
	stdif_allocator_t *allocator,
	void *ptr
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(allocator->version, STDIF_ALLOCATOR_ABI_1_0))
		return;
#endif

#define	IMPL(x)		((stdif_allocator_1_0_t *) (x))

	IMPL(allocator)->ops->v0.op_free(IMPL(allocator), ptr);

#undef	IMPL
}
