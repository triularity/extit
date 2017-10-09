/*
 * @(#) pmodule/win32/module_load.c
 *
 * Windows specific implementations of container library.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>

#ifdef	EXTIT_WCHAR
#include <wchar.h>
#endif

#include <windows.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>
#include <extit/pmodule.h>
#include <extit/platform.h>

#include "../pmodule_internal.h"


extit_module_t *
EXTIT_DECL
extit_module_load
(
	const extit_container_t *container,
	const char *path,
	unsigned int flags
)
{
	HMODULE			handle;
	FARPROC			descriptor;
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
				(unsigned int) GetLastError());
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

	/*
	 * Find the plugin descriptor
	 */
	if((descriptor = GetProcAddress(
	 handle, EXTIT_PMODULE_DESCRIPTOR_SYMBOL)) == NULL)
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
	module = extit_module_bind(
		container, FUNCPTR_TO_VOIDPTR(descriptor), flags);

	if(module == NULL)
	{
		FreeLibrary(handle);
		return NULL;
	}

	module->handle = handle;

	return module;
}


#ifdef	EXTIT_WCHAR
extit_module_t *
EXTIT_DECL
extit_module_load_wc
(
	const extit_container_t *container,
	const wchar_t *path,
	unsigned int flags
)
{
	HMODULE			handle;
	FARPROC			descriptor;
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
				(unsigned int) GetLastError());
		}
#endif	/* EXTIT_DEBUG */

		return NULL;
	}

	/*
	 * Find the plugin descriptor
	 */
	if((descriptor = GetProcAddress(
	 handle, EXTIT_PMODULE_DESCRIPTOR_SYMBOL)) == NULL)
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
	module = extit_module_bind(
		container, FUNCPTR_TO_VOIDPTR(descriptor), flags);

	if(module == NULL)
	{
		FreeLibrary(handle);
		return NULL;
	}

	module->handle = handle;

	return module;
}
#endif	/* EXTIT_WCHAR */
