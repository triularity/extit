/*
 * @(#) extit/iface/refcount.c
 *
 * Reference Count Interface API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <extit/iface/refcount_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_iface_refcount_add
(
	extit_iface_refcount_t *iface
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(iface->version, EXTIT_IFACE_REFCOUNT_VERSION_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IFACE_REFCOUNT_ADD(iface);
}


EXTIT_EXPORT
extit_refcount_t
EXTIT_DECL
extit_iface_refcount_get
(
	extit_iface_refcount_t *iface
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(iface->version, EXTIT_IFACE_REFCOUNT_VERSION_1_0))
		return EXTIT_REFCOUNT_NONE;
#endif

	return EXTIT_IFACE_REFCOUNT_GET(iface);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_iface_refcount_release
(
	extit_iface_refcount_t *iface
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(iface->version, EXTIT_IFACE_REFCOUNT_VERSION_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IFACE_REFCOUNT_RELEASE(iface);
}
