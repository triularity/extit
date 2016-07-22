/*
 * @(#) sample/if_referenced/provider.c
 *
 * This file is in the Public Domain.
 */

#include <stdlib.h>
#include <stdio.h>

#include <extit/base.h>
#include <extit/util.h>
#include <if/referenced_impl.h>

#include "myobj.h"
#include "provider.h"


#define	OBJ_COUNT	10


struct myobj_internal;

struct if_referenced_internal
{
	if_referenced_t			pub;		/* The public object */
	struct myobj_internal *		myobj;
};

struct myobj_internal
{
	myobj_t				pub;		/* The public object */
	extit_refcount_t		refcount;
	struct if_referenced_internal	if_referenced;
};


static
if_referenced_t *
myobj__get_if_referenced(myobj_t *obj)
{
	struct myobj_internal *	obji;


	obji = (struct myobj_internal *) obj;

	return &obji->if_referenced.pub;
}


static
extit_status_t
myobj__refcount__ops_add(if_referenced_t *refcount)
{
	struct myobj_internal *	obji;


	obji = ((struct if_referenced_internal *) refcount)->myobj;

	return extit_refcount_add(&obji->refcount);
}


static
extit_status_t
myobj__refcount__ops_release(if_referenced_t *refcount)
{
	struct myobj_internal *	obji;
	extit_status_t		status;


	obji = ((struct if_referenced_internal *) refcount)->myobj;

	status = extit_refcount_release(&obji->refcount);

	/*
	 * If it wasn't busy, free the object
	 */
	if(status == EXTIT_STATUS_OK)
	{
		printf("freeing object\n");
		free(obji);
	}

	return status;
}


static
if_referenced_ops_1_0_t	myobj__refcount__ops =
{
	myobj__refcount__ops_add,		/* add */
	myobj__refcount__ops_release		/* release */
};


static
struct myobj_internal *
alloc_myobj(myobj_type_t type)
{
	struct myobj_internal *	obji;


	if((obji = malloc(sizeof(struct myobj_internal))) != NULL)
	{
		obji->pub.type = type;
		obji->pub.get_if_referenced = myobj__get_if_referenced;

		obji->refcount = EXTIT_REFCOUNT_NONE;

		obji->if_referenced.pub.version = IF_REFERENCED_ABI_1_0;
		obji->if_referenced.pub.ops = &myobj__refcount__ops;

		obji->if_referenced.myobj = obji;
	}

	return obji;
}


static unsigned int	obj_index = 0;

static myobj_type_t	obj_types[OBJ_COUNT] =
{
        MYOBJ_TYPE_FOO,
        MYOBJ_TYPE_BAR,
        MYOBJ_TYPE_FIZBIN,
        MYOBJ_TYPE_FOO,
        MYOBJ_TYPE_FOO,
        MYOBJ_TYPE_BAR,
        MYOBJ_TYPE_BAR,
        MYOBJ_TYPE_FIZBIN,
        MYOBJ_TYPE_BAR,
        MYOBJ_TYPE_FOO
};


/*
 * This simulates an object source by returning a fixed set of myobj_t types.
 */
myobj_t *
provider_get_next()
{
	struct myobj_internal *	obji;


	if(obj_index >= OBJ_COUNT)
		return NULL;

	/* Should check for NULL */
	obji = alloc_myobj(obj_types[obj_index]);
	obj_index++;

	/* First add will always work */
	extit_refcount_add(&obji->refcount);

	return &obji->pub;
}

