/*
 * @(#) extit/container.h
 *
 * ExtIt container interface.
 *
 * Copyright (c) 2014-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__container_h
#define	__extit__container_h

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>

#ifdef	extit_container_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Container (base)
 */
typedef struct _extit_container		extit_container_t;

/*
 * Container (1.0)
 */
typedef struct _extit_container_1_0	extit_container_1_0_t;


LIBAPI
extit_func_t		EXTIT_DECL
			extit_container_get_function__1_0(
				const extit_container_t *container,
				const char *name);

LIBAPI
void *			EXTIT_DECL
			extit_container_get_interface__1_0(
				const extit_container_t *container,
				const char *iid,
				iv_version_t version);

LIBAPI
void *			EXTIT_DECL
			extit_container_get_symbol__1_0(
				const extit_container_t *container,
				const char *name);

LIBAPI
void			EXTIT_DECL
			extit_container_log__1_0(
				const extit_container_t *container,
				const char *message);

LIBAPI
iv_version_t		EXTIT_DECL
			extit_container_query_interface__1_0(
				const extit_container_t *container,
				const char *iid,
				iv_version_t base_version);

LIBAPI
iv_version_t		EXTIT_DECL
			extit_container_get_version(
				const extit_container_t *container);


#if	IV_VERSION_MAJOR(EXTIT_ABI_TARGET) == 1
#define	extit_container_get_function	extit_container_get_function__1_0
#define	extit_container_get_interface	extit_container_get_interface__1_0
#define	extit_container_get_symbol	extit_container_get_symbol__1_0
#define	extit_container_log		extit_container_log__1_0
#define	extit_container_query_interface	extit_container_query_interface__1_0
#endif	/* IV_VERSION_MAJOR(EXTIT_ABI_TARGET) == 1 */

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#undef	LIBAPI

#endif	/* !__extit__container_h */
