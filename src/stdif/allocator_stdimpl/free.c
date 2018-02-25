/*
 * @(#) stdif/allocator_stdimpl/free.c
 *
 * Allocator Interface - free@1.0 standard implementation.
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
 * Release allocated memory using @{func free(void *)}.
 *
 * @param	allocator	The allocator instance.
 * @param	ptr		The previously allocated memory.
 *
 * @see		stdif_allocator_alloc__1_0(stdif_allocator_t *, void *)
 */
void
EXTIT_DECL
stdif_allocator_stdimpl_free__1_0
(
	stdif_allocator_1_0_t *allocator,
	void *ptr
)
{
#ifdef	STDIF_PARANOID
	if(ptr == NULL)
		return;
#endif

	free(ptr);
}
