/*
 * @(#) sample/stdif_referenced/client.c
 *
 * This file is in the Public Domain.
 */

#include <stdlib.h>
#include <stdio.h>

#include <iv/base.h>
#include <stdif/referenced.h>

#include "myobj.h"
#include "worklist.h"
#include "provider.h"


int
main(int argc, char **argv)
{
	struct worklist *	list;
	myobj_t *		obj;
	stdif_referenced_t *	stdif_refed;


	list = worklist_create();

	while((obj = provider_get_next()) != NULL)
	{
		worklist_add(list, obj);

		/*
		 * Ideally this would be done via the resolvable interface
		 */
		stdif_refed = obj->get_referenced(obj);

		printf("Done with our ref\n");

		/*
		 * Release our reference
		 * The worklist may or may not have a reference
		 */
		if(stdif_referenced_release(stdif_refed) != EXTIT_STATUS_OK)
		{
			/* Log or handle the error ... */
		}
	}

	printf("Time to execute\n");

	worklist_execute(list);

	worklist_destroy(list);

	return 0;
}
