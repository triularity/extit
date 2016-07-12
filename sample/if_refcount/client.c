/*
 * @(#) if_refcount/client.c
 *
 * This file is in the Public Domain.
 */

#include <stdlib.h>

#include <iv/base.h>
#include <if/refcount.h>

#include "myobj.h"
#include "worklist.h"
#include "provider.h"


int
main(int argc, char **argv)
{
	struct worklist *	list;
	myobj_t *		obj;
	if_refcount_t *	if_rc;


	list = worklist_create();

	while((obj = provider_get_next()) != NULL)
	{
		worklist_add(list, obj);

		/*
		 * Ideally this would be done via the resolvable interface
		 */
		if_rc = obj->get_if_refcount(obj);

		/*
		 * Release our reference
		 * The worklist may or may not have a reference
		 */
		if(if_refcount_release(if_rc) != EXTIT_STATUS_OK)
		{
			/* Log or handle the error ... */
		}
	}

	worklist_execute(list);

	worklist_destroy(list);

	return 0;
}

