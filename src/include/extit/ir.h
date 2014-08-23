/*
 * @(#) extit/ir.h
 *
 * Interface Repository API.
 *
 * Copyright (c) 2014, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__ir_h
#define	__extit__ir_h

#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _extit_ir	extit_ir_t;


EXTIT_EXPORT
extit_ir_t *		EXTIT_DECL
			extit_ir_create(
				unsigned int flags);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_ir_cleanup(
				extit_ir_t *ir);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_ir_destroy(
				extit_ir_t *ir);

EXTIT_EXPORT
unsigned int		EXTIT_DECL
			extit_ir_getFlags(
				const extit_ir_t *ir);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_ir_getInterface(
				const extit_ir_t *ir,
				const char *id,
				extit_iv_t version);

EXTIT_EXPORT
extit_iv_t		EXTIT_DECL
			extit_ir_queryInterface(
				const extit_ir_t *ir,
				const char *id,
				extit_iv_t base_version);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_ir_removeInterface(
				extit_ir_t *ir,
				const char *id,
				extit_iv_t version,
				void *old_valuep);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_ir_setFlags(
				extit_ir_t *ir,
				unsigned int flags);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_ir_removeInterface(
				extit_ir_t *ir,
				const char *id,
				extit_iv_t version,
				void *old_valuep);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_ir_setInterface(
				extit_ir_t *ir,
				const char *id,
				extit_iv_t version,
				void *value,
				void *old_valuep);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__ir_h */
