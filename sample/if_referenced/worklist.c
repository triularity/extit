/*
 * @(#) sample/if_referenced/worklist.c
 *
 * This file is in the Public Domain.
 */

#include <stdlib.h>

#include "myobj.h"
#include "worklist.h"


struct worklist *
worklist_create()
{
	struct worklist *	list;


	if((list = malloc(sizeof(struct worklist))) != NULL)
	{
		list->head = NULL;
		list->next_p = &list->head;
	}

	return list;
}


void
worklist_add(struct worklist *list, myobj_t *obj)
{
	struct worklist_node *	node;
	if_referenced_t *	if_refed;


	/* We only handle Foo types */
	if(obj->type != MYOBJ_TYPE_FOO)
		return;

	if((node = malloc(sizeof(struct worklist_node))) != NULL)
	{
		node->obj = obj;
		node->next = NULL;

		/*
		 * Ideally this would be done via the resolvable interface
		 */
		if_refed = obj->get_if_referenced(obj);

		/*
		 * Keep a reference
		 */
		if(if_referenced_add(if_refed) == EXTIT_STATUS_OK)
		{
			*list->next_p = node;
			list->next_p = &node->next;
		}
		else
		{
			free(node);
		}
	}
}


void
worklist_execute(struct worklist *list)
{
	if_referenced_t *	if_refed;
	struct worklist_node *	node;
	struct worklist_node *	next_node;
	myobj_t *		obj;


	node = list->head;

	while(node != NULL)
	{
		obj = node->obj;

		/* Do something with obj ... */


		/*
		 * Ideally this would be done via the resolvable interface
		 */
		if_refed = obj->get_if_referenced(obj);

		/*
		 * Release it
		 */
		if(if_referenced_release(if_refed) != EXTIT_STATUS_OK)
		{
			/* Log or handle the error ... */
		}

		next_node = node->next;
		free(node);

		list->head = node = next_node;
	}
}


void
worklist_destroy(struct worklist *list)
{
	/*
	 * Assume list->head == NULL
	 * Real code wouldn't assume that
	 */

	free(list);
}

