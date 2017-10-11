/*
 * @(#) stdif/allocator_stdimpl/stdimpl.c
 *
 * A standard system implemtation for an Allocator Interface.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <stdif/allocator.h>
#include <stdif/allocator_impl.h>
#include <stdif/allocator_stdimpl.h>


static
void *
EXTIT_DECL
allocator_op_alloc__1_0
(
	stdif_allocator_1_0_t *allocator,
	size_t size
)
{
#ifndef	EXTIT_MALLOC_0_SUCCEEDS
	/* Skip if malloc(0) returns non-NULL */
	if(size == 0)
		size = 1;
#endif

	return malloc(size);
}


static
void *
EXTIT_DECL
allocator_op_dup__1_0
(
	stdif_allocator_1_0_t *allocator,
	void *ptr,
	size_t size
)
{
	size_t	nsize;
	void *	nptr;


#ifndef	EXTIT_MALLOC_0_SUCCEEDS
	/* Skip if malloc(0) returns non-NULL */
	if(size == 0)
		nsize = 1;
	else
#endif
		nsize = size;

	if((nptr = malloc(nsize)) != NULL)
		memcpy(nptr, ptr, size);

	return nptr;
}


static
void
EXTIT_DECL
allocator_op_free__1_0
(
	stdif_allocator_1_0_t *allocator,
	void *ptr
)
{
#ifdef	EXTIT_PARANOID
	if(ptr == NULL)
		return;
#endif

	free(ptr);
}


static
void *
EXTIT_DECL
allocator_op_realloc__1_0
(
	stdif_allocator_1_0_t *allocator,
	void *ptr,
	size_t size
)
{
#ifndef	EXTIT_MALLOC_0_SUCCEEDS
	/* Skip if malloc(0) returns non-NULL */
	if(size == 0)
		size = 1;
#endif

#ifdef	EXTIT_PARANOID
	if(ptr == NULL)
		return malloc(size);
#endif

	return realloc(ptr, size);
}


static
void *
EXTIT_DECL
allocator_op_zalloc__1_0
(
	stdif_allocator_1_0_t *allocator,
	size_t size
)
{
	void *	ptr;


#ifndef	EXTIT_MALLOC_0_SUCCEEDS
	/* Skip if malloc(0) returns non-NULL */
	if(size == 0)
		size = 1;
#endif

	if((ptr = malloc(size)) != NULL)
		memset(ptr, '\0', size);

	return ptr;
}


static
stdif_allocator_ops_1_0_t	allocator_ops_1_0 =
{
	/* v0 */
	{
		allocator_op_alloc__1_0,	/* op_alloc */
		allocator_op_free__1_0,		/* op_free */
		allocator_op_realloc__1_0,	/* op_realloc */
		allocator_op_zalloc__1_0,	/* op_zalloc */
		allocator_op_dup__1_0		/* op_dup */
	}
};


stdif_allocator_1_0_t	stdif_allocator_stdimpl_1_0 =
{
	STDIF_ALLOCATOR_ABI_1_0,	/* version */
	&allocator_ops_1_0		/* ops_1_0 */
};

