/*
 * @(#) if/configurable_stdimpl.h
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__configurable_stdimpl_h
#define	__if__configurable_stdimpl_h

#include <stddef.h>

#include <extit/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_configurable_stdimpl_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#define	LIBAPI_STATIC	EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#define	LIBAPI_STATIC	EXTIT_IMPORT_STATIC
#endif


struct if_configurable_propref
{
	if_configurable_propdef_t	definition;
	int				offset;

	void			(*update_notifier)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop);
};


LIBAPI
extern if_configurable_ops_1_0_t	if_configurable_stdimpl_ops_1_0;


LIBAPI_STATIC
if_configurable_propref_t *
			EXTIT_DECL
			if_configurable_stdimpl_find_property__1_0(
					if_configurable_t *conf,
					const char *id);

LIBAPI_STATIC
if_configurable_propref_t *
			EXTIT_DECL
			if_configurable_stdimpl_find_property__1_0_sorted(
					if_configurable_t *conf,
					const char *id);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_bool__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				extit_bool_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_bool__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				extit_bool_t *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_custom__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				void **valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_custom__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				void **valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_double__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				double *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_double__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				double *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_enum32__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_enum32__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_float__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				float *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_float__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				float *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_int8__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int8_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_int8__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int8_t *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_int16__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int16_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_int16__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int16_t *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_int32__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int32_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_int32__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int32_t *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_int64__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int64_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_int64__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int64_t *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_uint8__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint8_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_uint8__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint8_t *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_uint16__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint16_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_uint16__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint16_t *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_uint32__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_uint32__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_uint64__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint64_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_uint64__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint64_t *valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_utf8__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				const char **valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_get_utf8__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				const char **valuep);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_reset__1_0(
				if_configurable_t *conf);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_bool__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				extit_bool_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_bool__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				extit_bool_t value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_custom__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				void *value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_custom__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				void *value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_double__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				double value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_double__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				double value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_enum32__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint32_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_enum32__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint32_t value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_float__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				float value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_float__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				float value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_int8__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int8_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_int8__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int8_t value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_int16__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int16_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_int16__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int16_t value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_int32__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int32_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_int32__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int32_t value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_int64__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int64_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_int64__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int64_t value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_uint8__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint8_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_uint8__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint8_t value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_uint16__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint16_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_uint16__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint16_t value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_uint32__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint32_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_uint32__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint32_t value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_uint64__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint64_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_uint64__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint64_t value);

LIBAPI_STATIC
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_utf8__1_0(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				const char *value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_stdimpl_set_utf8__1_0_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				const char *value);

#undef	LIBAPI
#undef	LIBAPI_STATIC

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__configurable_stdimpl_h */
