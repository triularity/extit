/*
 * @(#) iv/repository.h
 *
 * Interface Versioning Repository API.
 *
 * Copyright (c) 2015-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__iv__repository_h
#define	__iv__repository_h

#include <iv/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	iv_repository_EXPORTS
#define	LIBAPI		IV_EXPORT
#else
#define	LIBAPI		IV_IMPORT
#endif


typedef struct _iv_repository	iv_repository_t;


/*
 * Status Codes
 */
typedef enum _iv_repository_status
{
	/*
	 * v1.0
	 */
	IV_REPOSITORY_STATUS_OK		= 0,	/* Success */
	IV_REPOSITORY_STATUS_FAIL	= 1,	/* General error */
	IV_REPOSITORY_STATUS_NOMEM	= 2,	/* Memory allocation failed */
	IV_REPOSITORY_STATUS_INVALID	= 3,	/* Invalid parameter/state */
	IV_REPOSITORY_STATUS_NOTFOUND	= 4	/* Result not found */
} iv_repository_status_t;


/*
 * Public API (v1.0)
 */
LIBAPI
iv_repository_t *	IV_DECL
			iv_repository_create(void);

LIBAPI
void			IV_DECL
			iv_repository_cleanup(
				iv_repository_t *repo);

LIBAPI
void			IV_DECL
			iv_repository_destroy(
				iv_repository_t *repo);

LIBAPI
void *			IV_DECL
			iv_repository_get(
				const iv_repository_t *repo,
				const char *key,
				const char *iid,
				iv_version_t version);

LIBAPI
iv_version_t		IV_DECL
			iv_repository_query(
				const iv_repository_t *repo,
				const char *key,
				const char *iid,
				iv_version_t base_version);

LIBAPI
iv_repository_status_t	IV_DECL
			iv_repository_remove(
				iv_repository_t *repo,
				const char *key,
				const char *iid,
				iv_version_t version,
				void **old_valuep);

LIBAPI
iv_repository_status_t	IV_DECL
			iv_repository_set(
				iv_repository_t *repo,
				const char *key,
				const char *iid,
				iv_version_t version,
				void *value,
				void **old_valuep);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__iv__repository_h */
