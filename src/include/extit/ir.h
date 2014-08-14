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
				extit_ir_t *ir,
				unsigned int flags);

EXTIT_EXPORT
void			EXTIT_DECL
			extit_ir_destroy(
				extit_ir_t *ir,
				unsigned int flags);

EXTIT_EXPORT
void *			EXTIT_DECL
			extit_ir_get(
				const extit_ir_t *ir,
				unsigned int flags,
				const char *id,
				extit_iv_t version);

EXTIT_EXPORT
extit_iv_t		EXTIT_DECL
			extit_ir_query(
				const extit_ir_t *ir,
				unsigned int flags,
				const char *id,
				extit_iv_t base_version);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__ir_h */
