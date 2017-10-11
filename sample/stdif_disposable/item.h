/*
 * @(#) stdif_disposable/item.h
 *
 * This file is in the Public Domain.
 */

#ifndef	__item_h
#define	__item_h

#include <stdif/disposable.h>


typedef struct _item		item_t;


item_t *			item_create(void (*wfunc)(void));

void				item_dosomething(item_t *item);

stdif_disposable_t *		item_get_disposable(item_t *item);

#endif	/* !__item_h */
