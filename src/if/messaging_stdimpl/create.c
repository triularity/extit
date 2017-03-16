/*
 * @(#) if/messaging_stdimpl/create.c
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>
#include <if/messaging_stdimpl.h>

#include "internal.h"


static
void
bound_destroy(void *value)
{
	if_messaging_stdimpl_bound_destroy((if_messaging_bound_t *) value);
}


EXTIT_EXPORT
if_messaging_t *
EXTIT_DECL
if_messaging_stdimpl_create
(
	void
)
{
	if_messaging_internal_t *	messaging_i;


	if((messaging_i = malloc(sizeof(if_messaging_internal_t))) == NULL)
		return NULL;

	if((messaging_i->keymap = iv_keymap_create(0, bound_destroy)) == NULL)
	{
		free(messaging_i);
		return NULL;
	}

	messaging_i->pub.version = IF_MESSAGING_ABI_1_0;
	messaging_i->pub.ops_1_0 = &if_messaging_stdimpl_ops__1_0;

	messaging_i->lid_list = NULL;
	messaging_i->lid_next = 1;
	messaging_i->num_deletes = 0;

	if_messaging_stdimpl_keybuf_init(&messaging_i->keybuf);


	return &messaging_i->pub;
}
