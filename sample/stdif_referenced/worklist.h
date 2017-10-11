/*
 * @(#) sample/stdif_referenced/worklist.h
 *
 * This file is in the Public Domain.
 */

#ifndef	__worklist_h
#define	__worklist_h

#include "myobj.h"


struct worklist_node
{
	myobj_t *		obj;
	struct worklist_node *	next;
};

struct worklist
{
	struct worklist_node *	head;
	struct worklist_node **	next_p;
};


struct worklist *	worklist_create(void);

void			worklist_add(struct worklist *list, myobj_t *obj);

void			worklist_execute(struct worklist *list);

void			worklist_destroy(struct worklist *list);

#endif	/* !__worklist_h */
