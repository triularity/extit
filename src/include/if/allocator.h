/*
 * @(#) if/allocator.h
 *
 * Allocator Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__allocator_h
#define	__if__allocator_h

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_allocator_EXPORTS
#define	IF_ALLOCATOR_LIBAPI	EXTIT_EXPORT
#else
#define	IF_ALLOCATOR_LIBAPI	EXTIT_IMPORT
#endif


/*
 * Allocator Interface ID
 */
#define IF_ALLOCATOR_IID		"{c1c017b1-44d5-11e6-9660-406186e454c1}/allocator"

/*
 * Allocator (v1.0)
 */
#define IF_ALLOCATOR_ABI_1_0		IV_VERSION(1,0)
typedef struct _if_allocator_1_0	if_allocator_1_0_t;


/*
 * ABI Version
 */
#define	IF_ALLOCATOR_ABI		IF_ALLOCATOR_ABI_1_0

#ifndef	IF_ALLOCATOR_ABI_TARGET
#define	IF_ALLOCATOR_ABI_TARGET		IF_ALLOCATOR_ABI
#endif

#if	IF_ALLOCATOR_ABI_TARGET == IF_ALLOCATOR_ABI_1_0
#define	if_allocator_t			if_allocator_1_0_t
#else
#error	Unsupported IF_ALLOCATOR_ABI_TARGET version
#endif


/*
 * Public API (v1.0)
 */
IF_ALLOCATOR_LIBAPI
void *			EXTIT_DECL
			if_allocator_alloc(
				if_allocator_t *allocator,
				size_t size);

IF_ALLOCATOR_LIBAPI
void			EXTIT_DECL
			if_allocator_free(
				if_allocator_t *allocator,
				void *ptr);

IF_ALLOCATOR_LIBAPI
void *			EXTIT_DECL
			if_allocator_realloc(
				if_allocator_t *allocator,
				void *ptr,
				size_t size);

IF_ALLOCATOR_LIBAPI
void *			EXTIT_DECL
			if_allocator_zalloc(
				if_allocator_t *allocator,
				size_t size);

IF_ALLOCATOR_LIBAPI
void *			EXTIT_DECL
			if_allocator_dup(
				if_allocator_t *allocator,
				void *ptr,
				size_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__allocator_h */
