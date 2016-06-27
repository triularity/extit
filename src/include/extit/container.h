/*
 * @(#) extit/container.h
 *
 * Container API.
 *
 * Copyright (c) 2014, 2015, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__container_h
#define	__extit__container_h

#include <stddef.h>

#ifdef  EXTIT_WCHAR
#include <wchar.h>
#endif

#ifdef	_WIN32
#include <windows.h>
#endif

#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	_WIN32
typedef FARPROC		extit_func_t;
#else
typedef void		(EXTIT_DECL *extit_func_t)();
#endif


/*
 * Aliases for API target
 */
#if	EXTIT_API_TARGET == EXTIT_API_VERSION_1_0
#define	extit_container_t	extit_container_1_0_t
#else
#error	Unsupported API target
#endif


/*
 * Container (base)
 */
typedef struct _extit_container_base	extit_container_base_t;

struct _extit_container_base
{
	iv_version_t	version;		/* EXTIT_API_VERSION */
};


/*
 * Container (v1.0)
 */
typedef struct _extit_container_1_0	extit_container_1_0_t;

typedef struct _extit_container_ops_1_0
{
	/*
	 * Get a raw named symbol
	 */
	void *			(EXTIT_DECL *get_symbol)(
					const extit_container_t *container,
					const char *name);

	/*
	 * Get a raw named function
	 */
	extit_func_t		(EXTIT_DECL *get_function)(
					const extit_container_t *container,
					const char *name);

	/*
	 * Get a named interface object by version
	 */
	void *			(EXTIT_DECL *get_interface)(
					const extit_container_t *container,
					const char *name,
					iv_version_t version);

	/*
	 * Query the supported version of an interface
	 */
	iv_version_t		(EXTIT_DECL *query_interface)(
					const extit_container_t *container,
					const char *name,
					iv_version_t base_version);

	/*
	 * Log a simple message
	 */
	void			(EXTIT_DECL *log)(
					const extit_container_t *container,
					const char *message);
} extit_container_ops_1_0_t;


struct _extit_container_1_0
{
	iv_version_t			version;/* EXTIT_API_VERSION */
	extit_container_ops_1_0_t *	ops;
};


typedef struct _extit_module	extit_module_t;
typedef struct _extit_plugin	extit_plugin_t;


typedef	extit_status_t	(EXTIT_DECL *extit_module_scan_callback_t)(
				extit_module_t *module,
				void *client_data);

typedef	extit_bool_t	(EXTIT_DECL *extit_module_scan_fnfilter_t)(
				const char *basename,
				size_t length); 

#ifdef  EXTIT_WCHAR
typedef	extit_bool_t	(EXTIT_DECL *extit_module_scan_fnfilter_wc_t)(
				const wchar_t *basename,
				size_t length); 
#endif	/* EXTIT_WCHAR */

EXTIT_EXPORT
extit_func_t		EXTIT_DECL
			extit_container_get_function_default(
				const extit_container_t *container,
				const char *name);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_container_get_interface_default(
				const extit_container_t *container,
				const char *name,
				iv_version_t version);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_container_get_symbol_default(
				const extit_container_t *container,
				const char *name);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_container_log_default(
				const extit_container_t *container,
				const char *message);

EXTIT_EXPORT
iv_version_t		EXTIT_DECL
			extit_container_query_interface_default(
				const extit_container_t *container,
				const char *name,
				iv_version_t base_version);

EXTIT_EXPORT
iv_version_t		EXTIT_DECL
			extit_getVersion(void);


EXTIT_EXPORT
extit_module_t *	EXTIT_DECL
			extit_module_bind(
				const extit_container_t *container,
				const void *descriptor,
				unsigned int flags);

EXTIT_EXPORT
extit_plugin_t *	EXTIT_DECL
			extit_module_createPlugin(
				extit_module_t *module);

EXTIT_EXPORT
iv_version_t		EXTIT_DECL
			extit_module_getAPIVersion(
				extit_module_t *module);

EXTIT_EXPORT
iv_version_t		EXTIT_DECL
			extit_module_getEffectiveAPIVersion(
				extit_module_t *module);

EXTIT_EXPORT
unsigned int		EXTIT_DECL
			extit_module_getFlags(
				extit_module_t *module);

EXTIT_EXPORT
extit_func_t		EXTIT_DECL
			extit_module_getFunction(
				extit_module_t *module,
				const char *name);

EXTIT_EXPORT
const char *		EXTIT_DECL
			extit_module_getName(
				extit_module_t *module);

EXTIT_EXPORT
const char *		EXTIT_DECL
			extit_module_getId(
				extit_module_t *module);

EXTIT_EXPORT
uint32_t		EXTIT_DECL
			extit_module_getIdVersion(
				extit_module_t *module);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_module_getSymbol(
				extit_module_t *module,
				const char *name);

EXTIT_EXPORT
const char *		EXTIT_DECL
			extit_module_getVersion(
				extit_module_t *module);

EXTIT_EXPORT
extit_module_t *	EXTIT_DECL
			extit_module_load(
				const extit_container_t *container,
				const char *path,
				unsigned int flags);

#ifdef  EXTIT_WCHAR
EXTIT_EXPORT
extit_module_t *	EXTIT_DECL
			extit_module_load_wc(
				const extit_container_t *container,
				const wchar_t *path,
				unsigned int flags);
#endif  /* EXTIT_WCHAR */

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_module_scan(
				const extit_container_t *container,
				const char *directory,
				extit_module_scan_callback_t callback,
				void *client_data,
				extit_module_scan_fnfilter_t fnfilter,
				unsigned int flags);

#ifdef  EXTIT_WCHAR
EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_module_scan_wc(
				const extit_container_t *container,
				const wchar_t *directory,
				extit_module_scan_callback_t callback,
				void *client_data,
				extit_module_scan_fnfilter_wc_t fnfilter,
				unsigned int flags);
#endif  /* EXTIT_WCHAR */

EXTIT_EXPORT
extit_bool_t		EXTIT_DECL
			extit_module_scan_fnfilter_default(
				const char *libname,
				size_t length); 

#ifdef  EXTIT_WCHAR
EXTIT_EXPORT
extit_bool_t		EXTIT_DECL
			extit_module_scan_fnfilter_wc_default(
				const wchar_t *libname,
				size_t length); 
#endif  /* EXTIT_WCHAR */

EXTIT_EXPORT
void			EXTIT_DECL
			extit_module_setFlags(
				extit_module_t *module,
				unsigned int flags);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_module_release(
				extit_module_t *module);


EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_plugin_activate(
				extit_plugin_t *plugin);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_plugin_deactivate(
				extit_plugin_t *plugin);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_plugin_destroy(
				extit_plugin_t *plugin);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_plugin_getContext(
				extit_plugin_t *plugin);

EXTIT_EXPORT
unsigned int		EXTIT_DECL
			extit_plugin_getFlags(
				extit_plugin_t *plugin);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_plugin_getInterface(
				extit_plugin_t *plugin,
				const char *id,
				iv_version_t version);

EXTIT_EXPORT
extit_module_t *	EXTIT_DECL
			extit_plugin_getModule(
				extit_plugin_t *plugin);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_plugin_ping(
				extit_plugin_t *plugin);

EXTIT_EXPORT
iv_version_t		EXTIT_DECL
			extit_plugin_queryInterface(
				extit_plugin_t *plugin,
				const char *id,
				iv_version_t base_version);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_plugin_setFlags(
				extit_plugin_t *plugin,
				unsigned int flags);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__container_h */
