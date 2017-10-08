/*
 * @(#) pmodule/dl/module_scan.c
 *
 * [lib]dl specific implementations of container library.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>
#include <extit/pmodule.h>

#include "../pmodule_internal.h"


/*
 * Kludgy
 */
#ifndef	EXTIT_PATH_MAX
#define	EXTIT_PATH_MAX	1024
#endif

#if	defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
#ifndef	_DIRENT_HAVE_D_TYPE
#define	_DIRENT_HAVE_D_TYPE
#endif

#ifndef	_DIRENT_HAVE_D_NAMLEN
#define	_DIRENT_HAVE_D_NAMLEN
#endif
#endif	/* __FreeBSD__ || __NetBSD__ || __OpenBSD__ || __bsdi__ || __DragonFly__*/


extit_status_t
EXTIT_DECL
extit_module_scan(
	const extit_container_t *container,
	const char *directory,
	extit_module_scan_callback_t callback,
	void *callback_client_data,
	extit_module_scan_fnfilter_t fnfilter,
	void *fnfilter_client_data,
	unsigned int flags
)
{
	DIR *			dir;
	size_t			dlen;
	struct dirent *		entry;
	size_t			namelen;
	char			path[EXTIT_PATH_MAX];
	extit_module_t *	module;


	if(directory == NULL)
		return EXTIT_STATUS_INVALID;

	if(fnfilter == NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		{
			fprintf(stderr,
			 "[extit:module] Using default filename filter.\n");
		}
#endif	/* EXTIT_DEBUG */

		fnfilter = extit_module_scan_fnfilter_default;
	}

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[extit:module] Scan directory: '%s'.\n",
			directory);
	}
#endif	/* EXTIT_DEBUG */

	if((dir = opendir(directory)) == NULL)
		return EXTIT_STATUS_FAIL;

	dlen = strlen(directory);
	strcpy(path, directory);
	path[dlen] = '/';

	while((entry = readdir(dir)) != NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		{
			fprintf(stderr,
				"[extit:module] Scan candidate: '%s/%s'.\n",
				directory,
				entry->d_name);
		}
#endif	/* EXTIT_DEBUG */

		if(entry->d_name[0] == '.')
		{
#ifdef	EXTIT_DEBUG
			if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
			{
				fprintf(stderr,
			"[extit:module] Skipping hidden file: '%s/%s'.\n",
					directory,
					entry->d_name);
			}

			continue;
#endif	/* EXTIT_DEBUG */
		}

#ifdef	_DIRENT_HAVE_D_TYPE
		if((entry->d_type != DT_REG) && (entry->d_type != DT_LNK)
		 && (entry->d_type != DT_UNKNOWN))
		{
#ifdef	EXTIT_DEBUG
			if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
			{
				fprintf(stderr,
			"[extit:module] Skipping non-normal file: '%s/%s'.\n",
					directory,
					entry->d_name);
			}
#endif	/* EXTIT_DEBUG */

			continue;
		}
#endif	/* _DIRENT_HAVE_D_TYPE */

#ifdef	_DIRENT_HAVE_D_NAMLEN
		namelen = entry->d_namlen;
#else
		namelen = strlen(entry->d_name);
#endif

		if(!fnfilter(entry->d_name, namelen, fnfilter_client_data))
			continue;

		if((dlen + namelen + 2) > EXTIT_PATH_MAX)
			continue;

		strcpy(path + dlen + 1, entry->d_name);

		module = extit_module_load(container, path, flags);

		if(module != NULL)
		{
			if(callback(module, callback_client_data)
			 != EXTIT_STATUS_OK)
			{
#ifdef	EXTIT_DEBUG
				if((flags & EXTIT_FLAG_LOG)
				 >= EXTIT_FLAG_LOG_DEBUG)
				{
					fprintf(stderr,
				"[extit:module] Scan rejected '%s'.\n",
						path);
				}
#endif	/* EXTIT_DEBUG */

				extit_module_release(module);
			}
			else
			{
#ifdef	EXTIT_DEBUG
				if((flags & EXTIT_FLAG_LOG)
				 >= EXTIT_FLAG_LOG_TRACE)
				{
					fprintf(stderr,
				"[extit:module] Scan accepted '%s'.\n",
						path);
				}
#endif	/* EXTIT_DEBUG */
			}
		}
	}

	closedir(dir);

	return EXTIT_STATUS_OK;
}
