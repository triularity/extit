/*
 * @(#) extit/if/allocator.h
 *
 * Allocator Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__allocator_h
#define	__extit__if__allocator_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	extit_if_allocator_EXPORTS
#define	EXTIT_IF_ALLOCATOR_LIBAPI	EXTIT_EXPORT
#else
#define	EXTIT_IF_ALLOCATOR_LIBAPI	EXTIT_IMPORT
#endif


/*
 * Allocator Interface ID
 */
#define EXTIT_IF_ALLOCATOR_IID		"{c1c017b1-44d5-11e6-9660-406186e454c1}/allocator"

/*
 * Allocator (v1.0)
 */
#define EXTIT_IF_ALLOCATOR_ABI_1_0	IV_VERSION(1,0)
typedef struct _extit_if_allocator_1_0	extit_if_allocator_1_0_t;


/*
 * ABI Version
 */
#define	EXTIT_IF_ALLOCATOR_ABI		EXTIT_IF_ALLOCATOR_ABI_1_0

#ifndef	EXTIT_IF_ALLOCATOR_ABI_TARGET
#define	EXTIT_IF_ALLOCATOR_ABI_TARGET	EXTIT_IF_ALLOCATOR_ABI
#endif

#if	EXTIT_IF_ALLOCATOR_ABI_TARGET == EXTIT_IF_ALLOCATOR_ABI_1_0
#define	extit_if_allocator_t		extit_if_allocator_1_0_t
#else
#error	Unsupported EXTIT_IF_ALLOCATOR_ABI_TARGET version
#endif


/*
 * Public API (v1.0)
 */
EXTIT_IF_ALLOCATOR_LIBAPI
void *			EXTIT_DECL
			extit_if_allocator_alloc(
				extit_if_allocator_t *allocator,
				size_t size);

EXTIT_IF_ALLOCATOR_LIBAPI
void			EXTIT_DECL
			extit_if_allocator_free(
				extit_if_allocator_t *allocator,
				void *ptr);

EXTIT_IF_ALLOCATOR_LIBAPI
void *			EXTIT_DECL
			extit_if_allocator_realloc(
				extit_if_allocator_t *allocator,
				void *ptr,
				size_t size);

EXTIT_IF_ALLOCATOR_LIBAPI
void *			EXTIT_DECL
			extit_if_allocator_zalloc(
				extit_if_allocator_t *allocator,
				size_t size);

EXTIT_IF_ALLOCATOR_LIBAPI
void *			EXTIT_DECL
			extit_if_allocator_dup(
				extit_if_allocator_t *allocator,
				void *ptr,
				size_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__allocator_h */
