/*
 * @(#) extit/if/configurable_stdimpl.h
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__configurable_stdimpl_h
#define	__extit__if__configurable_stdimpl_h

#include <stddef.h>

#include <extit/base.h>
#include <extit/if/configurable.h>
#include <extit/if/configurable_impl.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	extit_if_configurable_stdimpl_EXPORTS
#define	EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI	EXTIT_EXPORT
#define	EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI	EXTIT_EXPORT
#else
#define	EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI	EXTIT_IMPORT
#define	EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI	EXTIT_IMPORT_STATIC
#endif


struct extit_if_configurable_propref
{
	extit_if_configurable_propdef_t	definition;
	int				offset;

	extit_status_t		(*setter)(
					void *base,
					extit_if_configurable_propref_t *prop,
					void *valuep);
};


EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extern extit_if_configurable_ops_1_0_t	extit_if_configurable_stdimpl_ops_1_0;


#if	EXTIT_IF_CONFIGURABLE_ABI_TARGET == EXTIT_IF_CONFIGURABLE_ABI_1_0
#define	extit_if_configurable_stdimpl_ops	\
					extit_if_configurable_stdimpl_ops_1_0
#else
#error	Unsupported EXTIT_IF_CONFIGURABLE_ABI_TARGET version
#endif


EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_if_configurable_propref_t *
			EXTIT_DECL
			extit_if_configurable_find_property_stdimpl(
					extit_if_configurable_t *conf,
					const char *id);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_if_configurable_propref_t *
			EXTIT_DECL
			extit_if_configurable_find_property_stdimpl_sorted(
					extit_if_configurable_t *conf,
					const char *id);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_bool_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				extit_bool_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_bool_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				extit_bool_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_custom_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				void **valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_custom_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				void **valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_double_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				double *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_double_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				double *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_enum32_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				uint32_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_enum32_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				uint32_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_float_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				float *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_float_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				float *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int8_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				int8_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int8_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				int8_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int16_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				int16_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int16_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				int16_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int32_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				int32_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int32_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				int32_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int64_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				int64_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int64_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				int64_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint8_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				uint8_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint8_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				uint8_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint16_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				uint16_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint16_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				uint16_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint32_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				uint32_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint32_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				uint32_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint64_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				uint64_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint64_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				uint64_t *valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_utf8_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				const char **valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_utf8_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				const char **valuep);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_reset_stdimpl(
				extit_if_configurable_t *conf);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_bool_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				extit_bool_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_bool_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				extit_bool_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_custom_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				void *value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_custom_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				void *value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_double_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				double value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_double_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				double value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_enum32_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				uint32_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_enum32_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				uint32_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_float_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				float value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_float_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				float value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int8_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				int8_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int8_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				int8_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int16_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				int16_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int16_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				int16_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int32_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				int32_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int32_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				int32_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int64_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				int64_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int64_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				int64_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint8_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				uint8_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint8_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				uint8_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint16_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				uint16_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint16_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				uint16_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint32_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				uint32_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint32_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				uint32_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint64_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				uint64_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint64_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				uint64_t value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBXAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_utf8_stdimpl(
				extit_if_configurable_t *conf,
				extit_if_configurable_propref_t *prop,
				const char *value);

EXTIT_IF_CONFIGURABLE_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_utf8_stdimpl_base(
				void *base,
				extit_if_configurable_propref_t *prop,
				const char *value);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__configurable_stdimpl_h */
