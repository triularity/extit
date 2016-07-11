/*
 * @(#) extit/if/allocator/stdimpl.c
 *
 * A standard system implemtation for an Allocator Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <extit/if/allocator.h>
#include <extit/if/allocator_impl.h>
#include <extit/if/allocator_stdimpl.h>


static
void *
EXTIT_DECL
allocator_op_alloc
(
	extit_if_allocator_t *allocator,
	size_t size
)
{
	/* Skip if malloc(0) returns non-NULL */
	if(size == 0)
		size = 1;

	return malloc(size);
}


static
void
EXTIT_DECL
allocator_op_free
(
	extit_if_allocator_t *allocator,
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
allocator_op_realloc
(
	extit_if_allocator_t *allocator,
	void *ptr,
	size_t size
)
{
#ifdef	EXTIT_PARANOID
	if(ptr == NULL)
		return malloc(size);
#endif

	/* Skip if malloc(0) returns non-NULL */
	if(size == 0)
		size = 1;

	return realloc(ptr, size);
}


static
void *
EXTIT_DECL
allocator_op_zalloc
(
	extit_if_allocator_t *allocator,
	size_t size
)
{
	void *	ptr;


	/* Skip if malloc(0) returns non-NULL */
	if(size == 0)
		size = 1;

	if((ptr = malloc(size)) != NULL)
		memset(ptr, '\0', size);

	return ptr;
}


static
void *
EXTIT_DECL
allocator_op_dup
(
	extit_if_allocator_t *allocator,
	void *ptr,
	size_t size
)
{
	size_t	nsize;
	void *	nptr;


	/* Skip if malloc(0) returns non-NULL */
	if(size == 0)
		nsize = 1;
	else
		nsize = size;

	if((nptr = malloc(nsize)) != NULL)
		memcpy(nptr, ptr, size);

	return nptr;
}


static
extit_if_allocator_ops_1_0_t	allocator_ops =
{
	allocator_op_alloc,		/* op_alloc */
	allocator_op_free,		/* op_free */
	allocator_op_realloc,		/* op_realloc */
	allocator_op_zalloc,		/* op_zalloc */
	allocator_op_dup		/* op_dup */
};


EXTIT_IF_ALLOCATOR_STDIMPL_LIBAPI
extit_if_allocator_1_0_t	extit_if_allocator_stdimpl_1_0 =
{
	EXTIT_IF_ALLOCATOR_ABI_1_0,	/* version */
	&allocator_ops			/* ops */
};
