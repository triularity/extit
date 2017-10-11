/*
 * @(#) stdif_disposable/itemsource.c
 *
 * This file is in the Public Domain.
 */

#include "item.h"
#include "itemsource.h"


static
void
worker(void)
{
	/* ... */
}


item_t *
itemsource_get_next(void)
{
	return item_create(worker);
}
