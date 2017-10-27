/*
 * @(#) stdif/configurable_stdimpl.h
 *
 * Configurable Interface - standard implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__configurable_stdimpl_h
#define	__stdif__configurable_stdimpl_h

#include <stddef.h>
#include <stdbool.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>

#ifdef	stdif_configurable_stdimpl_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#define	LIBAPI_STUB	EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#define	LIBAPI_STUB	EXTIT_IMPORT_STUB
#endif

#ifdef	__cplusplus
extern "C" {
#endif

struct stdif_configurable_propref
{
	stdif_configurable_propdef_t	definition;
	int				offset;

	void			(*update_notifier)(
					stdif_configurable_t *conf,
					stdif_configurable_propref_t *prop);
};


/*
 * Configurable (v1.0)
 */
typedef struct _stdif_configurable_stdimpl_1_0
{
	stdif_configurable_1_0_t		pub;
	const stdif_configurable_descriptor_t *	descriptor;
} stdif_configurable_stdimpl_1_0_t;


LIBAPI
extern stdif_configurable_ops_1_0_t	stdif_configurable_stdimpl_ops_1_0;


LIBAPI_STUB
stdif_configurable_propref_t *
			EXTIT_DECL
			stdif_configurable_stdimpl_find_property__1_0(
					stdif_configurable_1_0_t *conf,
					const char *id);

LIBAPI_STUB
stdif_configurable_propref_t *
			EXTIT_DECL
			stdif_configurable_stdimpl_find_property__1_0_sorted(
					stdif_configurable_1_0_t *conf,
					const char *id);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_bool__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				bool *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_bool__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				bool *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_data__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				void **valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_data__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				void **valuep);

LIBAPI_STUB
const stdif_configurable_descriptor_t *
			EXTIT_DECL
			stdif_configurable_stdimpl_get_descriptor__1_0(
				stdif_configurable_1_0_t *conf);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_double__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				double *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_double__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				double *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_enum32__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_enum32__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_float__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				float *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_float__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				float *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_function__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				extit_func_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_function__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				extit_func_t *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_int8__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				int8_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_int8__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				int8_t *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_int16__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				int16_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_int16__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				int16_t *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_int32__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				int32_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_int32__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				int32_t *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_int64__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				int64_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_int64__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				int64_t *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_uint8__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				uint8_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_uint8__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				uint8_t *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_uint16__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				uint16_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_uint16__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				uint16_t *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_uint32__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_uint32__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_uint64__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				uint64_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_uint64__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				uint64_t *valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_utf8__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				const char **valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_get_utf8__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				const char **valuep);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_reset__1_0(
				stdif_configurable_1_0_t *conf);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_bool__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				bool value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_bool__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				bool value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_data__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				void *value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_data__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				void *value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_double__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				double value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_double__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				double value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_enum32__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				uint32_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_enum32__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				uint32_t value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_float__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				float value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_float__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				float value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_function__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				extit_func_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_function__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				extit_func_t value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_int8__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				int8_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_int8__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				int8_t value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_int16__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				int16_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_int16__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				int16_t value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_int32__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				int32_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_int32__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				int32_t value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_int64__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				int64_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_int64__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				int64_t value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_uint8__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				uint8_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_uint8__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				uint8_t value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_uint16__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				uint16_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_uint16__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				uint16_t value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_uint32__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				uint32_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_uint32__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				uint32_t value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_uint64__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				uint64_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_uint64__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				uint64_t value);

LIBAPI_STUB
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_utf8__1_0(
				stdif_configurable_1_0_t *conf,
				stdif_configurable_propref_t *prop,
				const char *value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_stdimpl_set_utf8__1_0_base(
				stdif_configurable_1_0_t *conf,
				void *base,
				stdif_configurable_propref_t *prop,
				const char *value);

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI
#undef	LIBAPI_STUB

#endif	/* !__stdif__configurable_stdimpl_h */
