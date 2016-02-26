/*
 * @(#) container/container_dl.c
 *
 * [lib]dl specific implementations of container library.
 *
 * Copyright (c) 2014-2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>

#include <extit/base.h>
#include <extit/plugin_spi.h>
#include <extit/container.h>
#include <extit/platform.h>

#include "container_impl.h"


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


EXTIT_EXPORT
extit_func_t
EXTIT_DECL
extit_container_get_function_default
(
	const extit_container_t *container,
	const char *name
)
{
#ifdef	EXTIT_HAVE_DLFUNC
	return dlfunc(RTLD_DEFAULT, name);
#else
	{
		extit_func_t	fptr;


		*((void **) &fptr) = dlsym(RTLD_DEFAULT, name);
		return fptr;
	}
#endif	/* EXTIT_HAVE_DLFUNC */
}


EXTIT_EXPORT
void *
EXTIT_DECL
extit_container_get_symbol_default
(
	const extit_container_t *container,
	const char *name
)
{
	return dlsym(RTLD_DEFAULT, name);
}


EXTIT_EXPORT
extit_func_t
EXTIT_DECL
extit_module_getFunction
(
	extit_module_t *module,
	const char *name
)
{
#ifdef	EXTIT_HAVE_DLFUNC
	return dlfunc(module->handle, name);
#else
	{
		extit_func_t	fptr;


		*((void **) &fptr) = dlsym(module->handle, name);
		return fptr;
	}
#endif	/* EXTIT_HAVE_DLFUNC */
}


EXTIT_EXPORT
void *
EXTIT_DECL
extit_module_getSymbol
(
	extit_module_t *module,
	const char *name
)
{
	return dlsym(module->handle, name);
}


EXTIT_EXPORT
extit_module_t *
EXTIT_DECL
extit_module_load(
	const extit_container_t *container,
	const char *path,
	unsigned int flags
)
{
	void *			handle;
	const void *		descriptor;
	extit_module_t *	module;


	/*
	 * Supported container version?
	 */
	if(IV_VERSION_MAJOR(container->version) != 1)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
		"[extit:module] Unsupported container version: %u.x.\n",
				IV_VERSION_MAJOR(container->version));
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:module] Loading '%s'.\n",
			path);
	}
#endif	/* EXTIT_DEBUG */

	if((handle = dlopen(path, RTLD_LAZY|RTLD_LOCAL)) == NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:module] Error loading '%s': %s.\n",
				path,
				dlerror());
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

	/*
	 * Find the plugin descriptor
	 */
	if((descriptor = dlsym(handle, EXTIT_SPI_DESCRIPTOR_SYMBOL)) == NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:module] No plugin descriptor.\n");
		}
#endif	/* EXTIT_DEBUG */

		dlclose(handle);
		return NULL;
	}

	/*
	 * Create the module from a descriptor
	 */
	module = extit_module_bind(container, descriptor, flags);

	if(module == NULL)
	{
		dlclose(handle);
		return NULL;
	}

	module->handle = handle;

	return module;
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_module_release(
	extit_module_t *module
)
{
	extit_status_t		status;
	unsigned int		flags;


	status = _extit_module_unload(module);

	if(status != EXTIT_STATUS_OK)
		return status;

	flags = module->flags;

	if(module->handle != NULL)
	{
		if(dlclose(module->handle) != 0)
		{
			if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
			{
				fprintf(stderr,
			"[extit:module] Error unloading library: %s\n",
					dlerror());
			}
		}
	}

	free(module);

	return EXTIT_STATUS_OK;
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_module_scan(
	const extit_container_t *container,
	const char *directory,
	extit_module_scan_callback_t callback,
	void *client_data,
	extit_module_scan_fnfilter_t fnfilter,
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
		if((entry->d_type != DT_REG) && (entry->d_type != DT_LNK))
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

		if(!fnfilter(entry->d_name, namelen))
			continue;

		if((dlen + namelen + 2) > EXTIT_PATH_MAX)
			continue;

		strcpy(path + dlen + 1, entry->d_name);

		module = extit_module_load(container, path, flags);

		if(module != NULL)
		{
			if(callback(module, client_data) != EXTIT_STATUS_OK)
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


EXTIT_EXPORT
unsigned int
EXTIT_DECL
extit_module_scan_fnfilter_default
(
	const char *basename,
	size_t length
)
{
	/*
	 * Must have a ".so" extension
	 */
	if(length < 4)
		return 0;

	return (EXTIT_FN_STRCMP(basename + length - 3, ".so") == 0);
}

