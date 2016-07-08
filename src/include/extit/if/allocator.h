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

/*
 * Allocator Interface ID
 */
#define EXTIT_IF_ALLOCATOR_IID		"{c1c017b1-44d5-11e6-9660-406186e454c1}/allocator"

/*
 * Allocator (v1.0)
 */
#define EXTIT_IF_ALLOCATOR_ABI_1_0	IV_VERSION(1,0)

typedef struct _extit_if_allocator_1_0	extit_if_allocator_1_0_t;


#ifndef	EXTIT_IF_ALLOCATOR_ABI
#define	EXTIT_IF_ALLOCATOR_ABI		EXTIT_IF_ALLOCATOR_ABI_1_0
#endif

#if	EXTIT_IF_ALLOCATOR_ABI == EXTIT_IF_ALLOCATOR_ABI_1_0
#define	extit_if_allocator_t		extit_if_allocator_1_0_t
#else
#error	Unsupported EXTIT_IF_ALLOCATOR_ABI version
#endif


/*
 * Public API (v1.0)
 */
EXTIT_EXPORT
void *			EXTIT_DECL
			extit_if_allocator_alloc(
				extit_if_allocator_t *allocator,
				size_t size);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_if_allocator_free(
				extit_if_allocator_t *allocator,
				void *ptr);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_if_allocator_realloc(
				extit_if_allocator_t *allocator,
				void *ptr,
				size_t size);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_if_allocator_zalloc(
				extit_if_allocator_t *allocator,
				size_t size);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_if_allocator_dup(
				extit_if_allocator_t *allocator,
				void *ptr,
				size_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__allocator_h */
