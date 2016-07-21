/*
 * @(#) extit/container_stdimpl.h
 *
 * ExtIt container implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__container_stdimpl_h
#define	__extit__container_stdimpl_h

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	extit_container_stdimpl_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#define	LIBXAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#define	LIBXAPI		EXTIT_IMPORT_STATIC
#endif


LIBXAPI
extit_func_t		EXTIT_DECL
			extit_container_get_function_default(
				const extit_container_t *container,
				const char *name);

LIBXAPI
void *			EXTIT_DECL
			extit_container_get_interface_default(
				const extit_container_t *container,
				const char *name,
				iv_version_t version);

LIBXAPI
void *			EXTIT_DECL
			extit_container_get_symbol_default(
				const extit_container_t *container,
				const char *name);

LIBXAPI
void			EXTIT_DECL
			extit_container_log_default(
				const extit_container_t *container,
				const char *message);

LIBXAPI
iv_version_t		EXTIT_DECL
			extit_container_query_interface_default(
				const extit_container_t *container,
				const char *name,
				iv_version_t base_version);

#undef	LIBAPI
#undef	LIBXAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__container_stdimpl_h */
