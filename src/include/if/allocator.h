/*
 * @(#) if/allocator.h
 *
 * Allocator Interface.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__allocator_h
#define	__if__allocator_h

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>

#ifdef	if_allocator_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Allocator Interface ID
 */
#define IF_ALLOCATOR_IID		"{c1c017b1-44d5-11e6-9660-406186e454c1}/allocator"


/*
 * Allocator (base)
 */
typedef struct _if_allocator		if_allocator_t;


/*
 * Allocator (v1.0)
 */
#define IF_ALLOCATOR_ABI_1_0		IV_VERSION(1,0)

typedef struct _if_allocator_1_0	if_allocator_1_0_t;

LIBAPI
void *			EXTIT_DECL
			if_allocator_alloc__1_0(
				if_allocator_t *allocator,
				size_t size);

LIBAPI
void *			EXTIT_DECL
			if_allocator_dup__1_0(
				if_allocator_t *allocator,
				void *ptr,
				size_t size);

LIBAPI
void			EXTIT_DECL
			if_allocator_free__1_0(
				if_allocator_t *allocator,
				void *ptr);

LIBAPI
void *			EXTIT_DECL
			if_allocator_realloc__1_0(
				if_allocator_t *allocator,
				void *ptr,
				size_t size);

LIBAPI
void *			EXTIT_DECL
			if_allocator_zalloc__1_0(
				if_allocator_t *allocator,
				size_t size);


/*
 * ABI Version
 */
#ifndef	IF_ALLOCATOR_ABI_TARGET
#define	IF_ALLOCATOR_ABI_TARGET		IF_ALLOCATOR_ABI_1_0
#endif

#if	IV_VERSION_MAJOR(IF_ALLOCATOR_ABI_TARGET) == 1
#define	if_allocator_alloc		if_allocator_alloc__1_0
#define	if_allocator_dup		if_allocator_dup__1_0
#define	if_allocator_free		if_allocator_free__1_0
#define	if_allocator_realloc		if_allocator_realloc__1_0
#define	if_allocator_zalloc		if_allocator_zalloc__1_0
#endif	/* IV_VERSION_MAJOR(IF_ALLOCATOR_ABI_TARGET) == 1 */

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__if__allocator_h */
