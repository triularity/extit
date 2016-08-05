/*
 * @(#) extit/container.h
 *
 * ExtIt container interface.
 *
 * Copyright (c) 2014-2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__container_h
#define	__extit__container_h

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	extit_container_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


/*
 * Container (1.0)
 */
typedef struct _extit_container_1_0	extit_container_1_0_t;


/*
 * ABI Version
 */
#if	EXTIT_ABI_TARGET == EXTIT_ABI_1_0
typedef	extit_container_1_0_t		extit_container_t;
#else
#error	Unsupported EXTIT_ABI_TARGET version
#endif


LIBAPI
extit_func_t		EXTIT_DECL
			extit_container_get_function(
				const extit_container_t *container,
				const char *name);

LIBAPI
void *			EXTIT_DECL
			extit_container_get_interface(
				const extit_container_t *container,
				const char *iid,
				iv_version_t version);

LIBAPI
void *			EXTIT_DECL
			extit_container_get_symbol(
				const extit_container_t *container,
				const char *name);

LIBAPI
void			EXTIT_DECL
			extit_container_log(
				const extit_container_t *container,
				const char *message);

LIBAPI
iv_version_t		EXTIT_DECL
			extit_container_query_interface(
				const extit_container_t *container,
				const char *iid,
				iv_version_t base_version);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__container_h */
