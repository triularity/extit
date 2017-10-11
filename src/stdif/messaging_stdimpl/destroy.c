/*
 * @(#) stdif/messaging_stdimpl/destroy.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


void
EXTIT_DECL
stdif_messaging_stdimpl_destroy
(
	stdif_messaging_t *messaging
)
{
	stdif_messaging_internal_t *	messaging_i;


	messaging_i = (stdif_messaging_internal_t *) messaging;

	iv_map_destroy(messaging_i->map);
}
