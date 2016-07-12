/*
 * @(#) extit/if_disposable/free.c
 *
 * Disposable Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/if/disposable.h>
#include <extit/if/disposable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_disposable_free
(
	extit_if_disposable_t *disposable
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(disposable->version, EXTIT_IF_DISPOSABLE_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IF_DISPOSABLE_FREE(disposable);
}
