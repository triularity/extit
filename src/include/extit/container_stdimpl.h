/*
 * @(#) extit/container_stdimpl.h
 *
 * ExtIt container implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__container_stdimpl_h
#define	__extit__container_stdimpl_h

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	extit_container_stdimpl_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#define	LIBAPI_STATIC	EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#define	LIBAPI_STATIC	EXTIT_IMPORT_STATIC
#endif


LIBAPI
extern extit_container_ops_1_0_t	extit_container_stdimpl_ops_1_0;


LIBAPI_STATIC
extit_func_t		EXTIT_DECL
			extit_container_stdimpl_get_function__1_0(
				const extit_container_1_0_t *container,
				const char *name);

LIBAPI_STATIC
void *			EXTIT_DECL
			extit_container_stdimpl_get_interface__1_0(
				const extit_container_1_0_t *container,
				const char *name,
				iv_version_t version);

LIBAPI_STATIC
void *			EXTIT_DECL
			extit_container_stdimpl_get_symbol__1_0(
				const extit_container_1_0_t *container,
				const char *name);

LIBAPI_STATIC
void			EXTIT_DECL
			extit_container_stdimpl_log__1_0(
				const extit_container_1_0_t *container,
				const char *message);

LIBAPI_STATIC
iv_version_t		EXTIT_DECL
			extit_container_stdimpl_query_interface__1_0(
				const extit_container_1_0_t *container,
				const char *name,
				iv_version_t base_version);

#undef	LIBAPI
#undef	LIBAPI_STATIC

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__container_stdimpl_h */
