/*
 * @(#) stdif/disposable/free.c
 *
 * Disposable Interface - free@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/disposable.h>
#include <stdif/disposable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


extit_status_t
EXTIT_DECL
stdif_disposable_free__1_0
(
	stdif_disposable_t *disposable
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(disposable->version, STDIF_DISPOSABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

#define	IMPL(x)		((stdif_disposable_1_0_t *) (x))

	return IMPL(disposable)->ops->v0.op_free(IMPL(disposable));

#undef	IMPL
}
