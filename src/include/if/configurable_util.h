/*
 * @(#) if/configurable_util.h
 *
 * Configurable Interface.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__configurable_util_h
#define	__if__configurable_util_h

#include <stdio.h>

#include <extit/base.h>
#include <if/configurable.h>

#ifdef	if_configurable_util_EXPORTS
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
			_if_configurable_dump_descriptor(
				FILE *fp,
				unsigned int indent,
				const if_configurable_descriptor_t *descr);

LIBAPI
void			EXTIT_DECL
			_if_configurable_dump_enum32(
				FILE *fp,
				unsigned int indent,
				const if_configurable_enum32_t *enum32);

LIBAPI
void			EXTIT_DECL
			_if_configurable_dump_propdef(
				FILE *fp,
				unsigned int indent,
				const if_configurable_propdef_t *propdef);

LIBAPI
const if_configurable_enum32_t *
			EXTIT_DECL
			if_configurable_enum32_find_by_id(
				const if_configurable_enum32_t *choices,
				uint32_t count,
				const char *id);

LIBAPI
const if_configurable_enum32_t *
			EXTIT_DECL
			if_configurable_enum32_find_by_value(
				const if_configurable_enum32_t *choices,
				uint32_t count,
				uint32_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			_if_configurable_fprint_property(
				FILE *fp,
				if_configurable_t *conf,
				if_configurable_type_t type,
				const char *id);

LIBAPI
extit_status_t		EXTIT_DECL
			_if_configurable_fprint_property__1_0(
				FILE *fp,
				if_configurable_1_0_t *conf,
				if_configurable_type_t type,
				if_configurable_propref_t *propref);

LIBAPI
void			EXTIT_DECL
			_if_configurable_fprint_utf8(
				FILE *fp,
				const char *utf,
				extit_bool_t esc_ctrl);

LIBAPI
const char *		EXTIT_DECL
			if_configurable_type_to_string(
				if_configurable_type_t type);

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__if__configurable_util_h */
