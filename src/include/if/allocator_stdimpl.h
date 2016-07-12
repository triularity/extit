/*
 * @(#) if/allocator_stdimpl.h
 *
 * Allocator Interface standard system implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__allocator_stdimpl_h
#define	__if__allocator_stdimpl_h

#include <if/allocator.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_allocator_stdimpl_EXPORTS
#define	IF_ALLOCATOR_STDIMPL_LIBAPI	EXTIT_EXPORT
#else
#define	IF_ALLOCATOR_STDIMPL_LIBAPI	EXTIT_IMPORT
#endif


IF_ALLOCATOR_STDIMPL_LIBAPI
extern	if_allocator_1_0_t		if_allocator_stdimpl_1_0;


#if	IF_ALLOCATOR_ABI_TARGET == IF_ALLOCATOR_ABI_1_0
#define	if_allocator_stdimpl		if_allocator_stdimpl_1_0
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__allocator_stdimpl_h */
