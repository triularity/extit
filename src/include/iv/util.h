/*
 * @(#) iv/util.h
 *
 * Interface Versioning utilities.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__iv__util_h
#define	__iv__util_h

#include <stddef.h>

#include <iv/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	iv_util_EXPORTS
#define	LIBAPI		IV_EXPORT
#else
#define	LIBAPI		IV_IMPORT
#endif


typedef	struct _iv_keymap	iv_keymap_t;


LIBAPI
void **			IV_DECL
			iv_keymap_acquire_valueptr(
				iv_keymap_t *keymap,
				const unsigned char *key,
				size_t keylen,
				const unsigned char **internal_keyp);

LIBAPI
void			IV_DECL
			iv_keymap_cleanup(
				iv_keymap_t *keymap,
				void (*value_cleaner)(void **valueptr));


LIBAPI
iv_keymap_t *		IV_DECL
			iv_keymap_create(
				uint32_t hashsize,
				void (*free_func)(void *value));

LIBAPI
void			IV_DECL
			iv_keymap_destroy(
				iv_keymap_t *keymap);

LIBAPI
void *			IV_DECL
			iv_keymap_get(
				iv_keymap_t *keymap,
				const unsigned char *key,
				size_t keylen);

LIBAPI
void **			IV_DECL
			iv_keymap_get_valueptr(
				iv_keymap_t *keymap,
				const unsigned char *key,
				size_t keylen);

LIBAPI
const unsigned char *	IV_DECL
			iv_keymap_intern_key(
				iv_keymap_t *keymap,
				const unsigned char *key,
				size_t keylen);


typedef	struct _iv_map		iv_map_t;


LIBAPI
void **			IV_DECL
			iv_map_acquire_valueptr(
				iv_map_t *map,
				const char *nid,
				const char *iid,
				const char **internal_nidp,
				const char **internal_iidp);

LIBAPI
void			IV_DECL
			iv_map_cleanup(
				iv_map_t *map,
				void (*value_cleaner)(void **valueptr));

LIBAPI
iv_map_t *		IV_DECL
			iv_map_create(
				uint32_t hashsize,
				void (*free_func)(void *value));

LIBAPI
void			IV_DECL
			iv_map_destroy(
				iv_map_t *map);

LIBAPI
void *			IV_DECL
			iv_map_get(
				iv_map_t *map,
				const char *nid,
				const char *iid);

LIBAPI
void **			IV_DECL
			iv_map_get_valueptr(
				iv_map_t *map,
				const char *nid,
				const char *iid);

LIBAPI
const char *		IV_DECL
			iv_map_intern_interfaceid(
				iv_map_t *map,
				const char *nid,
				const char *iid);

LIBAPI
const char *		IV_DECL
			iv_map_intern_nameid(
				iv_map_t *map,
				const char *nid,
				const char *iid);

LIBAPI
iv_bool_t		IV_DECL
			iv_matches(
				iv_version_t version,
				iv_version_t req_version);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__iv__util_h */
