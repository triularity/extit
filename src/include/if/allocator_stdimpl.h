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
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


LIBAPI
extern	if_allocator_1_0_t		if_allocator_stdimpl_1_0;


#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__allocator_stdimpl_h */
