/*
 * @(#) if/messaging_stdimpl/destroy.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


EXTIT_EXPORT
void
EXTIT_DECL
if_messaging_stdimpl_destroy
(
	if_messaging_1_0_t *messaging
)
{
	if_messaging_internal_t *	messaging_i;


	messaging_i = (if_messaging_internal_t *) messaging;

	iv_map_destroy(messaging_i->map);
}
