/*
 * @(#) stdif/messaging_stdimpl/create.c
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/idmap.h>
#include <extit/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_impl.h>
#include <stdif/messaging_stdimpl.h>

#include "internal.h"


/**
 * A callback wrapper for @{func iv_idmap_create}.
 *
 * @param	value		The bound entry list to destroy.
 */
static
void
bound_destroy(void *value)
{
	stdif_messaging_stdimpl_bound_destroy(
		(stdif_messaging_bound_t *) value);
}


/**
 * Create a messaging interface instance using standard implementation.
 *
 * @param	version		The messaging interface version.
 *
 * @return	A messaging instance,
 *		or @{constant NULL} on error or if @{param version} is
 *		not supported.
 *
 * @since	1.0
 *
 * @see		@{func stdif_messaging_stdimpl_destroy(stdif_messaging_t *)}
 */
stdif_messaging_t *
EXTIT_DECL
stdif_messaging_stdimpl_create
(
	iv_version_t version
)
{
	stdif_messaging_internal_t *	messaging_i;


	if(version != STDIF_MESSAGING_ABI_1_0)
		return NULL;

	if((messaging_i = malloc(sizeof(stdif_messaging_internal_t))) == NULL)
		return NULL;

	if((messaging_i->map = iv_idmap_create(0, bound_destroy)) == NULL)
	{
		free(messaging_i);
		return NULL;
	}

	messaging_i->pub.version = STDIF_MESSAGING_ABI_1_0;
	messaging_i->pub.ops = &stdif_messaging_stdimpl_ops__1_0;

	messaging_i->lid_list = NULL;
	messaging_i->lid_next = 1;
	messaging_i->num_deletes = 0;

	return (stdif_messaging_t *) &messaging_i->pub;
}
