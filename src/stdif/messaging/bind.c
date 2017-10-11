/*
 * @(#) if/messaging/bind.c
 *
 * Messaging Interface - bind@1.0 wrapper.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


if_messaging_bound_t *
EXTIT_DECL
if_messaging_bind__1_0
(
	if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(!IV_MATCHES(messaging->version, IF_MESSAGING_ABI_1_0))
		return IF_MESSAGING_BOUND_NONE;
#endif

#define	IMPL(x)		((if_messaging_1_0_t *) (x))

	return IMPL(messaging)->ops->v0.op_bind(
		IMPL(messaging), mid, iid, version);

#undef	IMPL
}