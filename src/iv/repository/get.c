/*
 * @(#) iv/repository/get.c
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string.h>

#include <iv/base.h>
#include <iv/util.h>
#include <iv/repository.h>

#include "internal.h"


IV_EXPORT
void *
IV_DECL
iv_repository_get
(
	const iv_repository_t *repo,
	const char *iid,
	iv_version_t version
)
{
	version_node_t *	vlist;
	unsigned int		version_major;
	iv_version_t		vlist_version;


	if(iid == NULL)
		return NULL;

	if(version == IV_VERSION_NONE)
		return NULL;

	vlist = (version_node_t *) iv_keymap_get(
		repo->keymap, (const unsigned char *) iid, strlen(iid));

	if(vlist == NULL)
		return NULL;

	version_major = IV_VERSION_MAJOR(version);

	while(vlist != NULL)
	{
		vlist_version = vlist->version;

		/*
		 * Matching version?
		 */
		if(vlist_version == version)
			return vlist->value;

		if(vlist_version > version)
		{
			/*
			 * For non 0.x, take the first higher minor version
			 */
			if((version_major != 0)
			 && (IV_VERSION_MAJOR(vlist_version) == version_major))
			{
				return vlist->value;
			}

			/*
			 * Not found
			 */
			break;
		}

		vlist = vlist->next;
	}

	return NULL;
}
