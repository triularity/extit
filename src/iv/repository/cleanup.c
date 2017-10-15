/*
 * @(#) iv/repository/cleanup.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/map.h>
#include <iv/repository.h>

#include "internal.h"


void
IV_DECL
iv_repository_cleanup
(
	iv_repository_t *repo
)
{
	iv_map_cleanup(repo->map, NULL);
	repo->num_deletes = 0;
}
