/*
 * @(#) iv/util.h
 *
 * Interface Versioning utilities.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__iv__util_h
#define	__iv__util_h

#include <iv/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

IV_EXPORT
iv_bool_t		IV_DECL
			iv_matches(
				const char *id,
				iv_version_t version,
				const char *req_id,
				iv_version_t req_version);

#ifdef	__cplusplus
}
#endif

#endif	/* !__iv__util_h */
