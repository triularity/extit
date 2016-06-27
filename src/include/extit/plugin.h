/*
 * @(#) extit/plugin.h
 *
 * Container API.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__plugin_h
#define	__extit__plugin_h

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>

#ifdef	__cplusplus
extern "C" {
#endif

EXTIT_EXPORT
extit_func_t		EXTIT_DECL
			extit_container_get_function(
				const extit_container_t *container,
				const char *name);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_container_get_interface(
				const extit_container_t *container,
				const char *name,
				iv_version_t version);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_container_get_symbol(
				const extit_container_t *container,
				const char *name);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_container_log(
				const extit_container_t *container,
				const char *message);

EXTIT_EXPORT
iv_version_t		EXTIT_DECL
			extit_container_query_interface(
				const extit_container_t *container,
				const char *name,
				iv_version_t base_version);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__plugin_h */
