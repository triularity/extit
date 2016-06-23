/*
 * @(#) extit/util.h
 *
 * ExtIt utilities.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__util_h
#define	__extit__util_h

#include <extit/base.h>
#include <extit/types.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	EXTIT_REFCOUNT_NONE	0
#define	EXTIT_REFCOUNT_MAX	0xFFFFFFFF

typedef uint32_t		extit_refcount_t;


EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_refcount_add(
				extit_refcount_t *refcount);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_refcount_release(
				extit_refcount_t *refcount);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__util_h */
