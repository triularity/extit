/*
 * @(#) iv/repository/query.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/map.h>
#include <iv/repository.h>

#include "internal.h"


iv_version_t
IV_DECL
iv_repository_query
(
	const iv_repository_t *repo,
	const char *key,
	const char *iid,
	iv_version_t base_version
)
{
	version_node_t *	vlist;
	unsigned int		base_version_major;
	iv_version_t		result;
	iv_version_t		vlist_version;


	if(key == NULL)
		key = "";

	if(iid == NULL)
		return IV_VERSION_NONE;

	if(base_version == IV_VERSION_NONE)
		return IV_VERSION_NONE;

	vlist = (version_node_t *) iv_idmap_get(repo->map, key, iid);

	if(vlist == NULL)
		return IV_VERSION_NONE;

	base_version_major = IV_VERSION_MAJOR(base_version);
	result = IV_VERSION_NONE;

	while(vlist != NULL)
	{
		vlist_version = vlist->version;

		if(IV_VERSION_MAJOR(vlist_version) == base_version_major)
		{
			if(vlist_version == base_version)
			{
				result = vlist_version;
			}
			else if((base_version_major != 0)
			 && (vlist_version > base_version))
			{
				result = vlist_version;
			}
		}
		else if(IV_VERSION_MAJOR(vlist_version) > base_version_major)
		{
			/*
			 * Passed it, so we are done
			 */
			break;
		}

		vlist = vlist->next;
	}

	return result;
}
