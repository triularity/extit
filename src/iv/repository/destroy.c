/*
 * @(#) iv/repository/destroy.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <iv/util.h>
#include <iv/repository.h>

#include "internal.h"


IV_EXPORT
void
IV_DECL
iv_repository_destroy
(
	iv_repository_t *repo
)
{
	iv_map_destroy(repo->map);
	free(repo);
}