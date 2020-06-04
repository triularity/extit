/*
 * @(#) iv/map.h
 *
 * Interface Versioning Map.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__iv__map_h
#define	__iv__map_h

#include <stddef.h>

#include <iv/base.h>

#ifdef	iv_idmap_EXPORTS
#define	LIBAPI		IV_EXPORT
#else
#define	LIBAPI		IV_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

typedef	struct _iv_map		iv_idmap_t;


LIBAPI
void **			IV_DECL
			iv_idmap_acquire_valueptr(
				iv_idmap_t *map,
				const char *nid,
				const char *iid,
				const char **internal_nidp,
				const char **internal_iidp);

LIBAPI
void			IV_DECL
			iv_idmap_cleanup(
				iv_idmap_t *map,
				void (*cleaner)(void **valueptr));

LIBAPI
iv_idmap_t *		IV_DECL
			iv_idmap_create(
				uint32_t hashsize,
				void (*free_callback)(void *value));

LIBAPI
void			IV_DECL
			iv_idmap_destroy(
				iv_idmap_t *map);

LIBAPI
void *			IV_DECL
			iv_idmap_get(
				iv_idmap_t *map,
				const char *nid,
				const char *iid);

LIBAPI
void **			IV_DECL
			iv_idmap_get_valueptr(
				iv_idmap_t *map,
				const char *nid,
				const char *iid);

LIBAPI
const char *		IV_DECL
			iv_idmap_intern_interfaceid(
				iv_idmap_t *map,
				const char *nid,
				const char *iid);

LIBAPI
const char *		IV_DECL
			iv_idmap_intern_nameid(
				iv_idmap_t *map,
				const char *nid,
				const char *iid);

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__iv__map_h */
