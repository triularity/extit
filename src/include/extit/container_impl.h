/*
 * @(#) extit/container_impl.h
 *
 * ExtIt container implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__container_impl_h
#define	__extit__container_impl_h

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Container operations (1.0)
 */
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


/*
 * Container (base)
 */
typedef struct _extit_container_base
{
	iv_version_t			version;	/* EXTIT_ABI_VERSION */
} extit_container_base_t;


/*
 * Container (1.0)
 */
struct _extit_container_1_0
{
	/* base */
	iv_version_t			version;	/* EXTIT_ABI_VERSION */

	/* 1.0 */
	extit_container_ops_1_0_t *	ops;
};


EXTIT_CONTAINER_LIBXAPI
extit_func_t		EXTIT_DECL
			extit_container_get_function_default(
				const extit_container_t *container,
				const char *name);

EXTIT_CONTAINER_LIBXAPI
void *			EXTIT_DECL
			extit_container_get_interface_default(
				const extit_container_t *container,
				const char *name,
				iv_version_t version);

EXTIT_CONTAINER_LIBXAPI
void *			EXTIT_DECL
			extit_container_get_symbol_default(
				const extit_container_t *container,
				const char *name);

EXTIT_CONTAINER_LIBXAPI
void			EXTIT_DECL
			extit_container_log_default(
				const extit_container_t *container,
				const char *message);

EXTIT_CONTAINER_LIBXAPI
iv_version_t		EXTIT_DECL
			extit_container_query_interface_default(
				const extit_container_t *container,
				const char *name,
				iv_version_t base_version);

EXTIT_CONTAINER_LIBXAPI
extit_bool_t		EXTIT_DECL
			extit_module_scan_fnfilter_default(
				const char *libname,
				size_t length); 

#ifdef  EXTIT_WCHAR
EXTIT_CONTAINER_LIBXAPI
extit_bool_t		EXTIT_DECL
			extit_module_scan_fnfilter_wc_default(
				const wchar_t *libname,
				size_t length); 
#endif  /* EXTIT_WCHAR */

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__container_impl_h */
