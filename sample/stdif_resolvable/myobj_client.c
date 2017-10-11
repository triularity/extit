/*
 * @(#) stdif_resolvable/myobj_client.c
 *
 * This file is in the Public Domain.
 */

#include <extit/base.h>
#include <stdif/resolvable.h>

#include "myobj.h"
#include "myobj_priv.h"


stdif_resolvable_t *
EXTIT_DECL
myobj_get_resolvable(myobj_t *obj)
{
	return (stdif_resolvable_t *) &obj->resolvable;
}


void
EXTIT_DECL
myobj_send(myobj_t *obj)
{
	obj->op_send(obj);
}
