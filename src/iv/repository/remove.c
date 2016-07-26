/*
 * @(#) iv/repository/remove.c
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <iv/base.h>
#include <iv/util.h>
#include <iv/repository.h>

#include "internal.h"


IV_EXPORT
iv_repository_status_t
IV_DECL
iv_repository_remove
(
	iv_repository_t *repo,
	const char *iid,
	iv_version_t version,
	void **old_valuep
)
{
	version_node_t **	vlistp;
	version_node_t *	entry;
	iv_version_t		entry_version;


	if(iid == NULL)
		return IV_REPOSITORY_STATUS_INVALID;

	if(version == IV_VERSION_NONE)
		return IV_REPOSITORY_STATUS_INVALID;

	vlistp = (version_node_t **) iv_keymap_get_valueptr(
		repo->keymap, (const unsigned char *) iid, strlen(iid));

	if(vlistp == NULL)
		return IV_REPOSITORY_STATUS_NOTFOUND;

	while((entry = *vlistp) != NULL)
	{
		entry_version = entry->version;

		if(entry_version == version)
		{
			if(old_valuep != NULL)
				*old_valuep = entry->value;

			*vlistp = entry->next;
			free(entry);

			if(++repo->num_deletes >= DELETES_PER_CLEANUP)
				iv_repository_cleanup(repo);

			return IV_REPOSITORY_STATUS_OK;
		}
		else if(entry_version > version)
		{
			/*
			 * Not found
			 */
			break;
		}

		vlistp = &entry->next;
	}

	return IV_REPOSITORY_STATUS_FAIL;
}
