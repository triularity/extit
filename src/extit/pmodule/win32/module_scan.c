/*
 * @(#) pmodule/win32/module_scan.c
 *
 * Windows specific implementations of container library.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
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

#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#include "../pmodule_internal.h"


/*
 * Kludgy
 */
#ifndef	EXTIT_PATH_MAX
#define	EXTIT_PATH_MAX	MAX_PATH
#endif


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_module_scan
(
	extit_container_t *container,
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
				(unsigned int) GetLastError());
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
				(unsigned int) err);
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
extit_module_scan_wc
(
	extit_container_t *container,
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
				(unsigned int) GetLastError());
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
				"[extit:module] Scan candidate: '%ls'.\n",
				ffd.cFileName);
		}
#endif	/* EXTIT_DEBUG */

		if(ffd.dwFileAttributes & (FILE_ATTRIBUTE_DEVICE|FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_HIDDEN))
		{
#ifdef	EXTIT_DEBUG
			if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
			{
				fprintf(stderr,
				 "[extit:module] Skipping non-normal file: '%ls'.\n",
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
				"[extit:module] Scan rejected '%ls'.\n",
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
				"[extit:module] Scan accepted '%ls'.\n",
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
				(unsigned int) err);
		}
#endif	/* EXTIT_DEBUG */

		FindClose(hFind);

		return EXTIT_STATUS_FAIL;
	}

	FindClose(hFind);

	return EXTIT_STATUS_OK;
}
#endif	/* EXTIT_WCHAR */
