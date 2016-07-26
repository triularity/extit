/*
 * @(#) iv/repository/set.c
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
iv_repository_set
(
	iv_repository_t *repo,
	const char *iid,
	iv_version_t version,
	void *value,
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

	/*
	 * Can't 'unset' this way
	 */
	if(value == NULL)
		return IV_REPOSITORY_STATUS_INVALID;

	vlistp = (version_node_t **) iv_keymap_acquire_valueptr(
		repo->keymap, (const unsigned char *) iid, strlen(iid), NULL);

	if(vlistp == NULL)
		return IV_REPOSITORY_STATUS_NOMEM;

	while((entry = *vlistp) != NULL)
	{
		entry_version = entry->version;

		if(entry_version == version)
		{
			/*
			 * Just replace the existing entry
			 */
			if(old_valuep != NULL)
				*old_valuep = entry->value;

			entry->value = value;

			return IV_REPOSITORY_STATUS_OK;
		}

		if(entry_version > version)
			break;

		vlistp = &entry->next;
	}

	/*
	 * New entry
	 */
	if((entry = calloc(1, sizeof(version_node_t))) == NULL)
		return IV_REPOSITORY_STATUS_NOMEM;

	entry->version = version;
	entry->value = value;

	entry->next = *vlistp;
	*vlistp = entry;

	if(old_valuep != NULL)
		*old_valuep = NULL;

	return IV_REPOSITORY_STATUS_OK;
}
