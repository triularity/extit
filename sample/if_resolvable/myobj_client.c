/*
 * @(#) if_resolvable/myobj_client.c
 *
 * This file is in the Public Domain.
 */

#include <extit/base.h>
#include <if/resolvable.h>

#include "myobj.h"
#include "myobj_priv.h"


if_resolvable_t *
EXTIT_DECL
myobj_get_resolvable(myobj_t *obj)
{
	return &obj->resolvable;
}


void
EXTIT_DECL
myobj_send(myobj_t *obj)
{
	obj->op_send(obj);
}
