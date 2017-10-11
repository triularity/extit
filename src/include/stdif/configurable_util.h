/*
 * @(#) stdif/configurable_util.h
 *
 * Configurable Interface.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__configurable_util_h
#define	__stdif__configurable_util_h

#include <stdio.h>

#include <extit/base.h>
#include <stdif/configurable.h>

#ifdef	stdif_configurable_util_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Configurable Utils (v1.0)
 */
LIBAPI
void			EXTIT_DECL
			_stdif_configurable_dump_descriptor(
				FILE *fp,
				unsigned int indent,
				const stdif_configurable_descriptor_t *descr);

LIBAPI
void			EXTIT_DECL
			_stdif_configurable_dump_enum32(
				FILE *fp,
				unsigned int indent,
				const stdif_configurable_enum32_t *enum32);

LIBAPI
void			EXTIT_DECL
			_stdif_configurable_dump_propdef(
				FILE *fp,
				unsigned int indent,
				const stdif_configurable_propdef_t *propdef);

LIBAPI
const stdif_configurable_enum32_t *
			EXTIT_DECL
			stdif_configurable_enum32_find_by_id(
				const stdif_configurable_enum32_t *choices,
				uint32_t count,
				const char *id);

LIBAPI
const stdif_configurable_enum32_t *
			EXTIT_DECL
			stdif_configurable_enum32_find_by_value(
				const stdif_configurable_enum32_t *choices,
				uint32_t count,
				uint32_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			_stdif_configurable_fprint_property(
				FILE *fp,
				stdif_configurable_t *conf,
				stdif_configurable_type_t type,
				const char *id);

LIBAPI
extit_status_t		EXTIT_DECL
			_stdif_configurable_fprint_property__1_0(
				FILE *fp,
				stdif_configurable_1_0_t *conf,
				stdif_configurable_type_t type,
				stdif_configurable_propref_t *propref);

LIBAPI
void			EXTIT_DECL
			_stdif_configurable_fprint_utf8(
				FILE *fp,
				const char *utf,
				extit_bool_t esc_ctrl);

LIBAPI
const char *		EXTIT_DECL
			stdif_configurable_type_to_string(
				stdif_configurable_type_t type);

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__stdif__configurable_util_h */
