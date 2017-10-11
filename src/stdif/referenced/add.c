/*
 * @(#) stdif/referenced/add.c
 *
 * Referenced Interface - add@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/referenced.h>
#include <stdif/referenced_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


extit_status_t
EXTIT_DECL
stdif_referenced_add__1_0
(
	stdif_referenced_t *referenced
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(referenced->version, STDIF_REFERENCED_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_referenced_1_0_t *) (x))

	return IMPL(referenced)->ops->v0.op_add(IMPL(referenced));

#undef	IMPL
}
