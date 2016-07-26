/*
 * @(#) iv/repository/cleanup.c
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/util.h>
#include <iv/repository.h>

#include "internal.h"


IV_EXPORT
void
IV_DECL
iv_repository_cleanup
(
	iv_repository_t *repo
)
{
	iv_keymap_cleanup(repo->keymap, NULL);
	repo->num_deletes = 0;
}
