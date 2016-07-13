/*
 * @(#) if/configurable_stdimpl.h
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
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
#define	IF_CONFIGURABLE_STDIMPL_LIBAPI	EXTIT_EXPORT
#define	IF_CONFIGURABLE_STDIMPL_LIBXAPI	EXTIT_EXPORT
#else
#define	IF_CONFIGURABLE_STDIMPL_LIBAPI	EXTIT_IMPORT
#define	IF_CONFIGURABLE_STDIMPL_LIBXAPI	EXTIT_IMPORT_STATIC
#endif


struct if_configurable_propref
{
	if_configurable_propdef_t	definition;
	int				offset;

	void			(*update_notifier)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop);
};


IF_CONFIGURABLE_STDIMPL_LIBAPI
extern if_configurable_ops_1_0_t	if_configurable_stdimpl_ops_1_0;


#if	IF_CONFIGURABLE_ABI_TARGET == IF_CONFIGURABLE_ABI_1_0
#define	if_configurable_stdimpl_ops	if_configurable_stdimpl_ops_1_0
#else
#error	Unsupported IF_CONFIGURABLE_ABI_TARGET version
#endif


IF_CONFIGURABLE_STDIMPL_LIBXAPI
if_configurable_propref_t *
			EXTIT_DECL
			if_configurable_find_property_stdimpl(
					if_configurable_t *conf,
					const char *id);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
if_configurable_propref_t *
			EXTIT_DECL
			if_configurable_find_property_stdimpl_sorted(
					if_configurable_t *conf,
					const char *id);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_bool_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				extit_bool_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_bool_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				extit_bool_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_custom_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				void **valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_custom_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				void **valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_double_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				double *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_double_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				double *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_enum32_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint32_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_enum32_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint32_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_float_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				float *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_float_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				float *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int8_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int8_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int8_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int8_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int16_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int16_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int16_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int16_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int32_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int32_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int32_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int32_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int64_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int64_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int64_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int64_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint8_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint8_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint8_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint8_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint16_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint16_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint16_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint16_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint32_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint32_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint32_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint32_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint64_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint64_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint64_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint64_t *valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_utf8_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				const char **valuep);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_utf8_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				const char **valuep);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_reset_stdimpl(
				if_configurable_t *conf);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_bool_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				extit_bool_t value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_bool_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				extit_bool_t value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_custom_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				void *value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_custom_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				void *value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_double_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				double value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_double_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				double value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_enum32_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint32_t value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_enum32_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint32_t value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_float_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				float value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_float_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				float value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int8_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int8_t value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int8_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int8_t value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int16_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int16_t value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int16_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int16_t value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int32_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int32_t value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int32_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int32_t value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int64_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				int64_t value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int64_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				int64_t value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint8_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint8_t value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint8_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint8_t value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint16_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint16_t value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint16_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint16_t value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint32_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint32_t value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint32_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint32_t value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint64_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				uint64_t value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint64_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				uint64_t value);

IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_utf8_stdimpl(
				if_configurable_t *conf,
				if_configurable_propref_t *prop,
				const char *value);

IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_utf8_stdimpl_base(
				if_configurable_t *conf,
				void *base,
				if_configurable_propref_t *prop,
				const char *value);

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__configurable_stdimpl_h */
