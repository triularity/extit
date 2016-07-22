/*
 * @(#) iv/repository.h
 *
 * Interface Versioning Repository API.
 *
 * Copyright (c) 2015, 2016, Chad M. Fraleigh.  All rights reserved.
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
 * Flags (v1.0)
 */
#define	IV_REPOSITORY_FLAG_LOG		0x00000003
#define	IV_REPOSITORY_FLAG_LOG_MINIMAL	0x00000000
#define	IV_REPOSITORY_FLAG_LOG_NORMAL	0x00000001
#define	IV_REPOSITORY_FLAG_LOG_DEBUG	0x00000002
#define	IV_REPOSITORY_FLAG_LOG_TRACE	0x00000003


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
				iv_repository_t *ir);

LIBAPI
void			IV_DECL
			iv_repository_destroy(
				iv_repository_t *ir);

LIBAPI
void *			IV_DECL
			iv_repository_get(
				const iv_repository_t *ir,
				const char *id,
				iv_version_t version);

LIBAPI
unsigned int		IV_DECL
			iv_repository_get_default_flags(void);

LIBAPI
unsigned int		IV_DECL
			iv_repository_get_flags(
				const iv_repository_t *ir);

LIBAPI
iv_version_t		IV_DECL
			iv_repository_query(
				const iv_repository_t *ir,
				const char *id,
				iv_version_t base_version);

LIBAPI
iv_repository_status_t	IV_DECL
			iv_repository_remove(
				iv_repository_t *ir,
				const char *id,
				iv_version_t version,
				void **old_valuep);

LIBAPI
iv_repository_status_t	IV_DECL
			iv_repository_set(
				iv_repository_t *ir,
				const char *id,
				iv_version_t version,
				void *value,
				void **old_valuep);

LIBAPI
void			IV_DECL
			iv_repository_set_default_flags(
				unsigned int flags);

LIBAPI
void			IV_DECL
			iv_repository_set_flags(
				iv_repository_t *ir,
				unsigned int flags);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__iv__repository_h */
