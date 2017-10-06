/*
 * @(#) extit/pmodule.h
 *
 * ExtIt plugin module Interface.
 *
 * Copyright (c) 2014-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__pmodule_h
#define	__extit__pmodule_h

#include <stddef.h>

#ifdef	EXTIT_WCHAR
#include <wchar.h>
#endif

#ifdef	_WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>

#ifdef	extit_pmodule_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#define	LIBAPI_STATIC	EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#define	LIBAPI_STATIC	EXTIT_IMPORT_STATIC
#endif

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _extit_module		extit_module_t;
typedef struct _extit_plugin		extit_plugin_t;


typedef	extit_status_t	(EXTIT_DECL *extit_module_scan_callback_t)(
				extit_module_t *module,
				void *client_data);

typedef	extit_bool_t	(EXTIT_DECL *extit_module_scan_fnfilter_t)(
				const char *basename,
				size_t length,
				void *client_data);

#ifdef	EXTIT_WCHAR
typedef	extit_bool_t	(EXTIT_DECL *extit_module_scan_fnfilter_wc_t)(
				const wchar_t *basename,
				size_t length,
				void *client_data);
#endif	/* EXTIT_WCHAR */

LIBAPI
iv_version_t		EXTIT_DECL
			extit_get_version(void);


LIBAPI
extit_module_t *	EXTIT_DECL
			extit_module_bind(
				const extit_container_t *container,
				const void *descriptor,
				unsigned int flags);

LIBAPI
extit_plugin_t *	EXTIT_DECL
			extit_module_create_plugin(
				extit_module_t *module);

LIBAPI
iv_version_t		EXTIT_DECL
			extit_module_get_abi_version(
				extit_module_t *module);

LIBAPI
iv_version_t		EXTIT_DECL
			extit_module_get_effective_abi_version(
				extit_module_t *module);

LIBAPI
unsigned int		EXTIT_DECL
			extit_module_get_flags(
				extit_module_t *module);

LIBAPI
extit_func_t		EXTIT_DECL
			extit_module_get_function(
				extit_module_t *module,
				const char *name);

LIBAPI
const char *		EXTIT_DECL
			extit_module_get_id(
				extit_module_t *module);

LIBAPI
uint32_t		EXTIT_DECL
			extit_module_get_id_version(
				extit_module_t *module);

LIBAPI
const char *		EXTIT_DECL
			extit_module_get_name(
				extit_module_t *module);

LIBAPI
void *			EXTIT_DECL
			extit_module_get_symbol(
				extit_module_t *module,
				const char *name);

LIBAPI
const char *		EXTIT_DECL
			extit_module_get_version(
				extit_module_t *module);

LIBAPI
extit_module_t *	EXTIT_DECL
			extit_module_load(
				const extit_container_t *container,
				const char *path,
				unsigned int flags);

#ifdef	EXTIT_WCHAR
LIBAPI
extit_module_t *	EXTIT_DECL
			extit_module_load_wc(
				const extit_container_t *container,
				const wchar_t *path,
				unsigned int flags);
#endif	/* EXTIT_WCHAR */

LIBAPI
extit_status_t		EXTIT_DECL
			extit_module_release(
				extit_module_t *module);

LIBAPI
extit_status_t		EXTIT_DECL
			extit_module_scan(
				const extit_container_t *container,
				const char *directory,
				extit_module_scan_callback_t callback,
				void *callback_client_data,
				extit_module_scan_fnfilter_t fnfilter,
				void *fnfilter_client_data,
				unsigned int flags);

#ifdef	EXTIT_WCHAR
LIBAPI
extit_status_t		EXTIT_DECL
			extit_module_scan_wc(
				const extit_container_t *container,
				const wchar_t *directory,
				extit_module_scan_callback_t callback,
				void *callback_client_data,
				extit_module_scan_fnfilter_wc_t fnfilter,
				void *fnfilter_client_data,
				unsigned int flags);
#endif	/* EXTIT_WCHAR */

LIBAPI_STATIC
extit_bool_t		EXTIT_DECL
			extit_module_scan_fnfilter_default(
				const char *libname,
				size_t length,
				void *client_data);

#ifdef	EXTIT_WCHAR
LIBAPI_STATIC
extit_bool_t		EXTIT_DECL
			extit_module_scan_fnfilter_wc_default(
				const wchar_t *libname,
				size_t length,
				void *client_data);
#endif	/* EXTIT_WCHAR */

LIBAPI
void			EXTIT_DECL
			extit_module_set_flags(
				extit_module_t *module,
				unsigned int flags);

LIBAPI
extit_status_t		EXTIT_DECL
			extit_plugin_destroy(
				extit_plugin_t *plugin);

LIBAPI
void *			EXTIT_DECL
			extit_plugin_get_context(
				extit_plugin_t *plugin);

LIBAPI
unsigned int		EXTIT_DECL
			extit_plugin_get_flags(
				extit_plugin_t *plugin);

LIBAPI
void *			EXTIT_DECL
			extit_plugin_get_interface(
				extit_plugin_t *plugin,
				const char *id,
				iv_version_t version);

LIBAPI
extit_module_t *	EXTIT_DECL
			extit_plugin_get_module(
				extit_plugin_t *plugin);

LIBAPI
iv_version_t		EXTIT_DECL
			extit_plugin_query_interface(
				extit_plugin_t *plugin,
				const char *id,
				iv_version_t base_version);

LIBAPI
void			EXTIT_DECL
			extit_plugin_set_flags(
				extit_plugin_t *plugin,
				unsigned int flags);

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI
#undef	LIBAPI_STATIC

#endif	/* !__extit__pmodule_h */
