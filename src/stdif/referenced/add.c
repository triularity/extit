/*
 * @(#) stdif/referenced/add.c
 *
 * Referenced Interface - add@1.0 wrapper.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/referenced.h>
#include <stdif/referenced_impl.h>

#ifdef	STDIF_PARANOID
#include <iv/util.h>
#endif


/**
 * Add an object reference.
 *
 * This is a convenience function that calls
 * @{param referenced}@{code ->ops->v0.op_add( ... )}
 *
 * @param	referenced	The referenced instance.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 * 		otherwise another @{constant EXTIT_STATUS_}*.
 *
 * @since	1.0
 */
extit_status_t
EXTIT_DECL
stdif_referenced_add__1_0
(
	stdif_referenced_t *referenced
)
{
#ifdef	STDIF_PARANOID
	if(!IV_MATCHES(referenced->version, STDIF_REFERENCED_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_referenced_1_0_t *) (x))

	return IMPL(referenced)->ops->v0.op_add(IMPL(referenced));

#undef	IMPL
}
