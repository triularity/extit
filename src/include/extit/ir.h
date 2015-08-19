/*
 * @(#) extit/ir.h
 *
 * Interface Repository API.
 *
 * Copyright (c) 2014, 2015, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__ir_h
#define	__extit__ir_h

#include <extit/base.h>
#include <iv/repository.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	EXTIT_COMPAT
typedef iv_repository_t		extit_ir_t;


EXTIT_EXPORT
iv_repository_t *	EXTIT_DECL
			extit_ir_create(
				unsigned int flags);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_ir_cleanup(
				iv_repository_t *ir);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_ir_destroy(
				iv_repository_t *ir);

EXTIT_EXPORT
unsigned int		EXTIT_DECL
			extit_ir_getFlags(
				const iv_repository_t *ir);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_ir_getInterface(
				const iv_repository_t *ir,
				const char *id,
				iv_version_t version);

EXTIT_EXPORT
iv_version_t		EXTIT_DECL
			extit_ir_queryInterface(
				const iv_repository_t *ir,
				const char *id,
				iv_version_t base_version);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_ir_removeInterface(
				iv_repository_t *ir,
				const char *id,
				iv_version_t version,
				void *old_valuep);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_ir_setFlags(
				iv_repository_t *ir,
				unsigned int flags);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_ir_removeInterface(
				iv_repository_t *ir,
				const char *id,
				iv_version_t version,
				void *old_valuep);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_ir_setInterface(
				iv_repository_t *ir,
				const char *id,
				iv_version_t version,
				void *value,
				void *old_valuep);

#endif	/* EXTIT_COMPAT */

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__ir_h */
