/*
 * @(#) extit/util.h
 *
 * ExtIt utilities.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__util_h
#define	__extit__util_h

#include <stdint.h>
#include <stdbool.h>

#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	extit_util_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


#define	EXTIT_REFCOUNT_NONE	0
#define	EXTIT_REFCOUNT_MAX	0xFFFFFFFF

typedef uint32_t		extit_refcount_t;


LIBAPI
extit_status_t		EXTIT_DECL
			extit_refcount_add(
				extit_refcount_t *refcount);

LIBAPI
bool			EXTIT_DECL
			extit_refcount_isnone(
				const extit_refcount_t *refcount);

LIBAPI
extit_status_t		EXTIT_DECL
			extit_refcount_release(
				extit_refcount_t *refcount);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__util_h */
