/*
 * @(#) container/win32/module_defaults.c
 *
 * Windows specific implementations of container library.
 * Default extit_module_*() function implementations.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string.h>

#ifdef	EXTIT_WCHAR
#include <wchar.h>
#endif

#include <windows.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/platform.h>


EXTIT_EXPORT
extit_bool_t
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
extit_bool_t
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
