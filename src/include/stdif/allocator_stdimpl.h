/*
 * @(#) stdif/allocator_stdimpl.h
 *
 * Allocator Interface - standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__allocator_stdimpl_h
#define	__stdif__allocator_stdimpl_h

#include <stdif/allocator.h>

#ifdef	stdif_allocator_stdimpl_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#define	LIBAPI_STUB	EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#define	LIBAPI_STUB	EXTIT_IMPORT_STUB
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Allocator (v1.0)
 */
LIBAPI
extern	stdif_allocator_1_0_t		stdif_allocator_stdimpl_1_0;


LIBAPI_STUB
void *			EXTIT_DECL
			stdif_allocator_stdimpl_alloc__1_0(
				stdif_allocator_1_0_t *allocator,
				size_t size);

LIBAPI_STUB
void *			EXTIT_DECL
			stdif_allocator_stdimpl_dup__1_0(
				stdif_allocator_1_0_t *allocator,
				void *ptr,
				size_t size);

LIBAPI_STUB
void			EXTIT_DECL
			stdif_allocator_stdimpl_free__1_0(
				stdif_allocator_1_0_t *allocator,
				void *ptr);

LIBAPI_STUB
void *			EXTIT_DECL
			stdif_allocator_stdimpl_realloc__1_0(
				stdif_allocator_1_0_t *allocator,
				void *ptr,
				size_t size);

LIBAPI_STUB
void *			EXTIT_DECL
			stdif_allocator_stdimpl_zalloc__1_0(
				stdif_allocator_1_0_t *allocator,
				size_t size);

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__stdif__allocator_stdimpl_h */
