/*
 * @(#) iv/repository/create.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>

#include <iv/base.h>
#include <iv/map.h>
#include <iv/repository.h>

#include "internal.h"


static
void
free_vlist(void *value)
{
	version_node_t *	entry;
	version_node_t *	entry_next;


	entry = (version_node_t *) value;

	while(entry != NULL)
	{
		entry_next = entry->next;
		free(entry);
		entry = entry_next;
	}
}


iv_repository_t *
IV_DECL
iv_repository_create(void)
{
	iv_repository_t *	repo;


	if((repo = malloc(sizeof(iv_repository_t))) == NULL)
		return NULL;

	if((repo->map = iv_idmap_create(0, free_vlist)) == NULL)
	{
		free(repo);
		return NULL;
	}

	repo->num_deletes = 0;

	return repo;
}
