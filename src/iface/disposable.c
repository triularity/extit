/*
 * @(#) extit/iface/disposable.c
 *
 * Disposable Interface API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/iface/disposable_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_iface_disposable_free
(
	extit_iface_disposable_t *iface
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(iface->version, EXTIT_IFACE_DISPOSABLE_VERSION_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IFACE_DISPOSABLE_FREE(iface);
}
