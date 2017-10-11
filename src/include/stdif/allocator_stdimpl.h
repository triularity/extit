/*
 * @(#) stdif/allocator_stdimpl.h
 *
 * Allocator Interface - standard implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__allocator_stdimpl_h
#define	__stdif__allocator_stdimpl_h

#include <stdif/allocator.h>

#ifdef	stdif_allocator_stdimpl_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Allocator (v1.0)
 */
LIBAPI
extern	stdif_allocator_1_0_t		stdif_allocator_stdimpl_1_0;

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__stdif__allocator_stdimpl_h */
