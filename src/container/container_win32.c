/*
 * @(#) container/container_win32.c
 *
 * Windows specific implementations of container library.
 *
 * Copyright (c) 2014, 2015, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef	EXTIT_WCHAR
#include <wchar.h>
#endif

#include <windows.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/plugin_spi.h>
#include <extit/container.h>
#include <extit/platform.h>

#include "container_impl.h"


/*
 * Kludgy
 */
#ifndef	EXTIT_PATH_MAX
#define	EXTIT_PATH_MAX	MAX_PATH
#endif



EXTIT_EXPORT
extit_func_t
EXTIT_DECL
extit_container_get_function_default
(
	const extit_container_t *container,
	const char *name
)
{
	return GetProcAddress(GetModuleHandle(NULL), name);
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
	return GetProcAddress(GetModuleHandle(NULL), name);
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
	return GetProcAddress(module->handle, name);
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
	return GetProcAddress(module->handle, name);
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
	HMODULE			handle;
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

	if((handle = LoadLibraryA(path)) == NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
			 "[extit:module] Error loading '%s': Error #%u.\n",
				path,
				GetLastError());
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

	/*
	 * Find the plugin descriptor
	 */
	if((descriptor = GetProcAddress(handle, EXTIT_SPI_DESCRIPTOR_SYMBOL))
	 == NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:module] No plugin descriptor.\n");
		}
#endif	/* EXTIT_DEBUG */

		FreeLibrary(handle);
		return NULL;
	}

	/*
	 * Create the module from a descriptor
	 */
	module = extit_module_bind(container, descriptor, flags);

	if(module == NULL)
	{
		FreeLibrary(handle);
		return NULL;
	}

	module->handle = handle;

	return module;
}


#ifdef	EXTIT_WCHAR
EXTIT_EXPORT
extit_module_t *
EXTIT_DECL
extit_module_load_wc(
	const extit_container_t *container,
	const wchar_t *path,
	unsigned int flags
)
{
	HMODULE			handle;
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
			"[extit:module] Loading '%ls'.\n",
			path);
	}
#endif	/* EXTIT_DEBUG */

	if((handle = LoadLibraryW(path)) == NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
			 "[extit:module] Error loading '%ls': Error #%u.\n",
				path,
				GetLastError());
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

	/*
	 * Find the plugin descriptor
	 */
	if((descriptor = (extit_spi_descriptor_base_t *)
	 GetProcAddress(handle, EXTIT_SPI_DESCRIPTOR_SYMBOL)) == NULL)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
				"[extit:module] No plugin descriptor.\n");
		}
#endif	/* EXTIT_DEBUG */

		FreeLibrary(handle);
		return NULL;
	}

	/*
	 * Create the module from a descriptor
	 */
	module = extit_module_bind(container, descriptor, flags);

	if(module == NULL)
	{
		FreeLibrary(handle);
		return NULL;
	}

	module->handle = handle;

	return module;
}
#endif	/* EXTIT_WCHAR */


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_module_release(
	extit_module_t *module
)
{
	unsigned int		flags;


	flags = module->flags;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:module] Releasing module, ID: %s.\n",
			extit_module_getId(module));
	}
#endif

	if(module->refcount != 0)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
			 "[extit:module] Module is busy, refcount = %u.\n",
				module->refcount);
		}
#endif

		return EXTIT_STATUS_BUSY;
	}

	if(!FreeLibrary(module->handle))
	{
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
		"[extit:module] Error unloading library: Error #%u.\n",
				GetLastError());
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
	size_t			dlen;
	char			path[EXTIT_PATH_MAX];
	WIN32_FIND_DATAA	ffd;
	HANDLE			hFind;
	const char *		basename;
	extit_module_t *	module;
	DWORD			err;


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

	if((dlen = strlen(directory)) > (sizeof(path) - 3))
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
			 "[extit:module] Path too long (> %u): '%s'.\n",
				(sizeof(path) - 3),
				directory);
		}
#endif	/* EXTIT_DEBUG */

		return EXTIT_STATUS_INVALID;
	}

	strcpy(path, directory);
	strcpy(path + dlen, "\\*");

	hFind = FindFirstFile(path, &ffd);

	if(hFind == INVALID_HANDLE_VALUE)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		{
			fprintf(stderr,
		"[extit:module] Error opening directory '%s': Error #%u.\n",
				directory,
				GetLastError());
		}
#endif	/* EXTIT_DEBUG */

		return EXTIT_STATUS_FAIL;
	}

	do
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		{
			fprintf(stderr,
				"[extit:module] Scan candidate: '%s'.\n",
				ffd.cFileName);
		}
#endif	/* EXTIT_DEBUG */

		if(ffd.dwFileAttributes & (FILE_ATTRIBUTE_DEVICE|FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_HIDDEN))
		{
#ifdef	EXTIT_DEBUG
			if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
			{
				fprintf(stderr,
				 "[extit:module] Skipping non-normal file: '%s'.\n",
					ffd.cFileName);
			}
#endif	/* EXTIT_DEBUG */

			continue;
		}

		if((basename = strrchr(ffd.cFileName, '\\')) == NULL)
			basename = ffd.cFileName;

		if(!fnfilter(basename, strlen(basename)))
			continue;

		module = extit_module_load(container, ffd.cFileName, flags);

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
						ffd.cFileName);
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
						ffd.cFileName);
				}
#endif	/* EXTIT_DEBUG */
			}
		}
	} while(FindNextFile(hFind, &ffd));

	if((err = GetLastError()) != ERROR_NO_MORE_FILES) 
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
		"[extit:module] Error reading directory: Error #%u.\n",
				err);
		}
#endif	/* EXTIT_DEBUG */

		FindClose(hFind);

		return EXTIT_STATUS_FAIL;
	}

	FindClose(hFind);

	return EXTIT_STATUS_OK;
}


#ifdef	EXTIT_WCHAR
EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_module_scan_wc(
	const extit_container_t *container,
	const wchar_t *directory,
	extit_module_scan_callback_t callback,
	void *client_data,
	extit_module_scan_fnfilter_wc_t fnfilter,
	unsigned int flags
)
{
	size_t			dlen;
	wchar_t			path[EXTIT_PATH_MAX];
	WIN32_FIND_DATAW	ffd;
	HANDLE			hFind;
	const wchar_t *		basename;
	extit_module_t *	module;
	DWORD			err;


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

		fnfilter = extit_module_scan_fnfilter_wc_default;
	}

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[extit:module] Scan directory: '%ls'.\n",
			directory);
	}
#endif	/* EXTIT_DEBUG */

	if((dlen = wcslen(directory)) > (sizeof(path) - 3))
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
			 "[extit:module] Path too long (> %u): '%ls'.\n",
				(sizeof(path) - 3),
				directory);
		}
#endif	/* EXTIT_DEBUG */

		return EXTIT_STATUS_INVALID;
	}

	wcscpy(path, directory);
	wcscpy(path + dlen, L"\\*");

	hFind = FindFirstFileW(path, &ffd);

	if(hFind == INVALID_HANDLE_VALUE)
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		{
			fprintf(stderr,
		"[extit:module] Error opening directory '%ls': Error #%u.\n",
				directory,
				GetLastError());
		}
#endif	/* EXTIT_DEBUG */

		return EXTIT_STATUS_FAIL;
	}

	do
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		{
			fprintf(stderr,
				"[extit:module] Scan candidate: '%s'.\n",
				ffd.cFileName);
		}
#endif	/* EXTIT_DEBUG */

		if(ffd.dwFileAttributes & (FILE_ATTRIBUTE_DEVICE|FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_HIDDEN))
		{
#ifdef	EXTIT_DEBUG
			if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
			{
				fprintf(stderr,
				 "[extit:module] Skipping non-normal file: '%s'.\n",
					ffd.cFileName);
			}
#endif	/* EXTIT_DEBUG */

			continue;
		}

		if((basename = wcsrchr(ffd.cFileName, '\\')) == NULL)
			basename = ffd.cFileName;

		if(!fnfilter(basename, wcslen(basename)))
			continue;

		module = extit_module_load_wc(container, ffd.cFileName, flags);

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
						ffd.cFileName);
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
						ffd.cFileName);
				}
#endif	/* EXTIT_DEBUG */
			}
		}
	} while(FindNextFileW(hFind, &ffd));

	if((err = GetLastError()) != ERROR_NO_MORE_FILES) 
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
		"[extit:module] Error reading directory: Error #%u.\n",
				err);
		}
#endif	/* EXTIT_DEBUG */

		FindClose(hFind);

		return EXTIT_STATUS_FAIL;
	}

	FindClose(hFind);

	return EXTIT_STATUS_OK;
}
#endif	/* EXTIT_WCHAR */


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
	 * Must have a ".dll" extension
	 */
	if(length < 5)
		return 0;

	return (EXTIT_FN_STRCMP(basename + length - 4, ".dll") == 0);
}


#ifdef	EXTIT_WCHAR
EXTIT_EXPORT
unsigned int
EXTIT_DECL
extit_module_scan_fnfilter_wc_default
(
	const wchar_t *basename,
	size_t length
)
{
	/*
	 * Must have a ".dll" extension
	 */
	if(length < 5)
		return 0;

	return (EXTIT_FN_WCSCMP(basename + length - 4, L".dll") != 0);
}
#endif	/* EXTIT_WCHAR */

