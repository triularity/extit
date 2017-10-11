/*
 * @(#) if_disposable/client.c
 *
 * This file is in the Public Domain.
 */

#include <extit/base.h>
#include <if/disposable.h>

#include "item.h"
#include "itemsource.h"


int
main(int argc, char **argv)
{
	item_t *		item;
	if_disposable_t *	disposable;


	item = itemsource_get_next();

	item_dosomething(item);


	disposable = item_get_disposable(item);

	if(if_disposable_free(disposable) != EXTIT_STATUS_OK)
	{
		/* Log or handle the error ... */
	}

	return 0;
}
