/*
 * @(#) iv/repository.h
 *
 * Interface Versioning Repository API.
 *
 * Copyright (c) 2015, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__iv__repository_h
#define	__iv__repository_h

#include <iv/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _iv_repository	iv_repository_t;


/*
 * Flags (v1.0)
 */
#define	IV_REPOSITORY_FLAG_LOG			0x00000003
#define	IV_REPOSITORY_FLAG_LOG_MINIMAL		0x00000000
#define	IV_REPOSITORY_FLAG_LOG_NORMAL		0x00000001
#define	IV_REPOSITORY_FLAG_LOG_DEBUG		0x00000002
#define	IV_REPOSITORY_FLAG_LOG_TRACE		0x00000003


/*
 * Status Codes (v1.0)
 */
#define	IV_REPOSITORY_STATUS_OK			0
#define	IV_REPOSITORY_STATUS_FAIL		1
#define	IV_REPOSITORY_STATUS_NOMEM		2
#define	IV_REPOSITORY_STATUS_INVALID		3

typedef	unsigned int		iv_repository_status_t;


/*
 * Public API (v1.0)
 */
IV_EXPORT
iv_repository_t *	IV_DECL
			iv_repository_create();

IV_EXPORT
void			IV_DECL
			iv_repository_cleanup(
				iv_repository_t *ir);

IV_EXPORT
void			IV_DECL
			iv_repository_destroy(
				iv_repository_t *ir);

IV_EXPORT
void *			IV_DECL
			iv_repository_get(
				const iv_repository_t *ir,
				const char *id,
				iv_version_t version);

IV_EXPORT
unsigned int		IV_DECL
			iv_repository_getDefaultFlags();

IV_EXPORT
unsigned int		IV_DECL
			iv_repository_getFlags(
				const iv_repository_t *ir);

IV_EXPORT
iv_version_t		IV_DECL
			iv_repository_query(
				const iv_repository_t *ir,
				const char *id,
				iv_version_t base_version);

IV_EXPORT
iv_repository_status_t	IV_DECL
			iv_repository_remove(
				iv_repository_t *ir,
				const char *id,
				iv_version_t version,
				void *old_valuep);

IV_EXPORT
iv_repository_status_t	IV_DECL
			iv_repository_set(
				iv_repository_t *ir,
				const char *id,
				iv_version_t version,
				void *value,
				void *old_valuep);

IV_EXPORT
void			IV_DECL
			iv_repository_setDefaultFlags(
				unsigned int flags);

IV_EXPORT
void			IV_DECL
			iv_repository_setFlags(
				iv_repository_t *ir,
				unsigned int flags);

#ifdef	__cplusplus
}
#endif

#endif	/* !__iv__repository_h */