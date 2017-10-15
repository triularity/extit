/*
 * @(#) stdif_disposable/item.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include <extit/base.h>
#include <stdif/disposable.h>
#include <stdif/disposable_impl.h>

#include "item.h"


struct _item
{
	void			(*wfunc)(void);
	stdif_disposable_1_0_t	disposable;
};


static
extit_status_t
EXTIT_DECL
item_disposable_free
(
	stdif_disposable_1_0_t *disposable
)
{
	item_t *	item;


	printf("Freeing item...\n");

	item = (item_t *)
		(((char *) disposable) - offsetof(item_t, disposable));

	free(item);

	return EXTIT_STATUS_OK;
}


static
stdif_disposable_ops_1_0_t		item_disposable_ops =
{
	/* v0 */
	{
		item_disposable_free		/* op_free */
	}
};



item_t *
item_create(void (*wfunc)(void))
{
	item_t *	item;


	/* XXX - Check for NULL in real thing! */
	item = malloc(sizeof(item_t));

	item->wfunc = wfunc;

	item->disposable.version = STDIF_DISPOSABLE_ABI_1_0;
	item->disposable.ops = &item_disposable_ops;

	return item;
}


void
item_dosomething(item_t *item)
{
	(item->wfunc)();
}


stdif_disposable_t *
item_get_disposable(item_t *item)
{
	return (stdif_disposable_t *) &item->disposable;
}

