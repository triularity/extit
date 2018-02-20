/*
 * @(#) stdif/allocator_stdimpl/stdimpl.c
 *
 * A standard system implemtation for an Allocator Interface.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <stdif/allocator.h>
#include <stdif/allocator_impl.h>
#include <stdif/allocator_stdimpl.h>


/**
 * Allocate uninitialized memory using @{func malloc(size_t)}.
 *
 * @param	allocator	The allocator instance.
 * @param	size		The size of memory to allocate (in bytes).
 *
 * @return	A pointer to the allocated memory,
 *		or @{constant NULL} on failure.
 */
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


/**
 * Allocate memory with the contents of existing memory using
 * @{func malloc(size_t)} and @{func memcpy(char *, const char *, size_t)}.
 *
 * @param	allocator	The allocator instance.
 * @param	ptr		The start of memory to copy.
 * @param	size		The size of memory to allocate and copy
 *				(in bytes).
 *
 * @return	A pointer to the allocated memory,
 *		or @{constant NULL} on failure.
 */
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


/**
 * Release allocated memory using @{func free(void *)}.
 *
 * @param	allocator	The allocator instance.
 * @param	ptr		The previously allocated memory.
 *
 * @see		stdif_allocator_alloc__1_0(stdif_allocator_t *, void *)
 */
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


/**
 * Reallocate memory to a new size using @{func realloc(void *, size_t)}.
 *
 * @param	allocator	The allocator instance.
 * @param	ptr		The previously allocated memory.
 * @param	size		The new allocation size (in bytes).
 *
 * @return	A pointer to the moved or same allocated memory address,
 *		or @{constant NULL} on failure.
 */
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


/**
 * Allocate zero initialized memory using @{func malloc(size_t)} and
 * @[func memset(void *, char, size_t)}.
 *
 * @param	allocator	The allocator instance.
 * @param	size		The size of memory to allocate (in bytes).
 *
 * @return	A pointer to the allocated memory,
 *		or @{constant NULL} on failure.
 */
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


/**
 * A static instance of an allocator 1.0 interface that uses standard
 * C memory management.
 */
stdif_allocator_1_0_t	stdif_allocator_stdimpl_1_0 =
{
	STDIF_ALLOCATOR_ABI_1_0,	/* version */
	&allocator_ops_1_0		/* ops_1_0 */
};

