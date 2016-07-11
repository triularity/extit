/*
 * @(#) extit/if/allocator_stdimpl.h
 *
 * Allocator Interface standard system implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__allocator_stdimpl_h
#define	__extit__if__allocator_stdimpl_h

#include <extit/if/allocator.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	extit_if_allocator_stdimpl_EXPORTS
#define	EXTIT_IF_ALLOCATOR_STDIMPL_LIBAPI	EXTIT_EXPORT
#else
#define	EXTIT_IF_ALLOCATOR_STDIMPL_LIBAPI	EXTIT_IMPORT
#endif


EXTIT_IF_ALLOCATOR_STDIMPL_LIBAPI
extern	extit_if_allocator_1_0_t		extit_if_allocator_stdimpl_1_0;


#if	EXTIT_IF_ALLOCATOR_ABI_TARGET == EXTIT_IF_ALLOCATOR_ABI_1_0
#define	extit_if_allocator_stdimpl	extit_if_allocator_stdimpl_1_0
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__allocator_stdimpl_h */
