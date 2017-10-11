/*
 * @(#) sample/stdif_referenced/provider.c
 *
 * This file is in the Public Domain.
 */

#include <stdlib.h>
#include <stdio.h>

#include <extit/base.h>
#include <extit/util.h>
#include <stdif/referenced_impl.h>

#include "myobj.h"
#include "provider.h"


#define	OBJ_COUNT	10


struct myobj_internal;

typedef struct stdif_referenced_internal
{
	stdif_referenced_1_0_t		pub;		/* The public object */
	struct myobj_internal *		myobj;
} stdif_referenced_internal_t;

struct myobj_internal
{
	myobj_t				pub;		/* The public object */
	extit_refcount_t		refcount;
	stdif_referenced_internal_t	stdif_referenced;
};


static
stdif_referenced_t *
myobj__get_referenced(myobj_t *obj)
{
	struct myobj_internal *	obji;


	obji = (struct myobj_internal *) obj;

	return (stdif_referenced_t *) &obji->stdif_referenced.pub;
}


static
extit_status_t
myobj__referenced__add(stdif_referenced_1_0_t *referenced)
{
	struct myobj_internal *	obji;


	obji = ((stdif_referenced_internal_t *) referenced)->myobj;

	return extit_refcount_add(&obji->refcount);
}


static
extit_status_t
myobj__referenced__release(stdif_referenced_1_0_t *referenced)
{
	struct myobj_internal *	obji;
	extit_status_t		status;


	obji = ((stdif_referenced_internal_t *) referenced)->myobj;

	status = extit_refcount_release(&obji->refcount);

	/*
	 * If it isn't busy, free the object
	 */
	if((status == EXTIT_STATUS_OK)
	 && extit_refcount_isnone(&obji->refcount))
	{
		printf("freeing object\n");
		free(obji);
	}

	return status;
}


static
stdif_referenced_ops_1_0_t	myobj__referenced_ops =
{
	/* v0 */
	{
		myobj__referenced__add,			/* op_add */
		myobj__referenced__release		/* op_release */
	}
};


static
struct myobj_internal *
alloc_myobj(myobj_type_t type)
{
	struct myobj_internal *	obji;


	if((obji = malloc(sizeof(struct myobj_internal))) != NULL)
	{
		obji->pub.type = type;
		obji->pub.get_referenced = myobj__get_referenced;

		obji->refcount = EXTIT_REFCOUNT_NONE;

		obji->stdif_referenced.pub.version = STDIF_REFERENCED_ABI_1_0;
		obji->stdif_referenced.pub.ops = &myobj__referenced_ops;

		obji->stdif_referenced.myobj = obji;
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

