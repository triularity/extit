/*
 * @(#) stdif/configurable.h
 *
 * Configurable Interface.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__configurable_h
#define	__stdif__configurable_h

#include <stdbool.h>

#include <iv/base.h>
#include <extit/base.h>

#ifdef	stdif_configurable_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum stdif_configurable_type
{
	/* v1.0 */
	STDIF_CONFIGURABLE_TYPE_BOOL	= 0,
	STDIF_CONFIGURABLE_TYPE_DOUBLE	= 1,
	STDIF_CONFIGURABLE_TYPE_ENUM32	= 2,
	STDIF_CONFIGURABLE_TYPE_FLOAT	= 3,
	STDIF_CONFIGURABLE_TYPE_INT8	= 4,
	STDIF_CONFIGURABLE_TYPE_INT16	= 5,
	STDIF_CONFIGURABLE_TYPE_INT32	= 6,
	STDIF_CONFIGURABLE_TYPE_INT64	= 7,
	STDIF_CONFIGURABLE_TYPE_UINT8	= 8,
	STDIF_CONFIGURABLE_TYPE_UINT16	= 9,
	STDIF_CONFIGURABLE_TYPE_UINT32	= 10,
	STDIF_CONFIGURABLE_TYPE_UINT64	= 11,
	STDIF_CONFIGURABLE_TYPE_UTF8	= 12,
	STDIF_CONFIGURABLE_TYPE_DATA	= 13,
	STDIF_CONFIGURABLE_TYPE_FUNCTION	= 14
} stdif_configurable_type_t;


/*
 * Configurable Status (v1.0)
 */
#define	STDIF_CONFIGURABLE_STATUS_MISMATCH	\
			((extit_status_t) (EXTIT_STATUS_CUSTOM_BASE + 0))

#define	STDIF_CONFIGURABLE_STATUS_BADLEN	\
			((extit_status_t) (EXTIT_STATUS_CUSTOM_BASE + 1))


typedef struct _stdif_configurable_enum32
{
	const char *		id;
	const char *		name;
	const char *		description;
	uint32_t		value;
} stdif_configurable_enum32_t;


typedef struct _stdif_configurable_propspec_bool
{
	bool			def_value;
} stdif_configurable_propspec_bool_t;


typedef struct _stdif_configurable_propspec_data
{
	void *			def_value;
	const char *		iid;
	iv_version_t		version;
} stdif_configurable_propspec_data_t;


typedef struct _stdif_configurable_propspec_double
{
	double			min_value;
	double			max_value;
	double			step_hint;
	double			def_value;
} stdif_configurable_propspec_double_t;


typedef struct _stdif_configurable_propspec_enum32
{
	const stdif_configurable_enum32_t *
				choices;

	uint32_t		choice_count;
	uint32_t		def_value;
} stdif_configurable_propspec_enum32_t;


typedef struct _stdif_configurable_propspec_float
{
	float			min_value;
	float			max_value;
	float			step_hint;
	float			def_value;
} stdif_configurable_propspec_float_t;


typedef struct _stdif_configurable_propspec_function
{
	extit_func_t		def_value;
	const char *		iid;
	iv_version_t		version;
} stdif_configurable_propspec_function_t;


typedef struct _stdif_configurable_propspec_int8
{
	int8_t			min_value;
	int8_t			max_value;
	int8_t			def_value;
} stdif_configurable_propspec_int8_t;


typedef struct _stdif_configurable_propspec_int16
{
	int16_t			min_value;
	int16_t			max_value;
	int16_t			def_value;
} stdif_configurable_propspec_int16_t;


typedef struct _stdif_configurable_propspec_int32
{
	int32_t			min_value;
	int32_t			max_value;
	int32_t			def_value;
} stdif_configurable_propspec_int32_t;


typedef struct _stdif_configurable_propspec_int64
{
	int64_t			min_value;
	int64_t			max_value;
	int64_t			def_value;
} stdif_configurable_propspec_int64_t;


typedef struct _stdif_configurable_propspec_uint8
{
	uint8_t			min_value;
	uint8_t			max_value;
	uint8_t			def_value;
} stdif_configurable_propspec_uint8_t;


typedef struct _stdif_configurable_propspec_uint16
{
	uint16_t		min_value;
	uint16_t		max_value;
	uint16_t		def_value;
} stdif_configurable_propspec_uint16_t;


typedef struct _stdif_configurable_propspec_uint32
{
	uint32_t		min_value;
	uint32_t		max_value;
	uint32_t		def_value;
} stdif_configurable_propspec_uint32_t;


typedef struct _stdif_configurable_propspec_uint64
{
	uint64_t		min_value;
	uint64_t		max_value;
	uint64_t		def_value;
} stdif_configurable_propspec_uint64_t;


typedef struct _stdif_configurable_propspec_utf8
{
	const char *		def_value;
} stdif_configurable_propspec_utf8_t;


typedef struct _stdif_configurable_propdef
{
	const char *			id;
	const char *			name;
	const char *			description;
	stdif_configurable_type_t	type;

	union
	{
		stdif_configurable_propspec_bool_t	type_bool;
		stdif_configurable_propspec_data_t	type_data;
		stdif_configurable_propspec_double_t	type_double;
		stdif_configurable_propspec_enum32_t	type_enum32;
		stdif_configurable_propspec_float_t	type_float;
		stdif_configurable_propspec_function_t	type_function;
		stdif_configurable_propspec_int8_t	type_int8;
		stdif_configurable_propspec_int16_t	type_int16;
		stdif_configurable_propspec_int32_t	type_int32;
		stdif_configurable_propspec_int64_t	type_int64;
		stdif_configurable_propspec_uint8_t	type_uint8;
		stdif_configurable_propspec_uint16_t	type_uint16;
		stdif_configurable_propspec_uint32_t	type_uint32;
		stdif_configurable_propspec_uint64_t	type_uint64;
		stdif_configurable_propspec_utf8_t	type_utf8;
	} spec;
} stdif_configurable_propdef_t;


typedef struct _stdif_configurable_descriptor
{
	const stdif_configurable_propdef_t **
				properties;

	uint32_t		count;		/* Number of properties */
	const char *		id;		/* Internalization context */
} stdif_configurable_descriptor_t;


typedef struct stdif_configurable_propref	stdif_configurable_propref_t;


/*
 * Configurable Interface ID
 */
#define STDIF_CONFIGURABLE_IID		"{c1c017b1-44d5-11e6-9660-406186e454c1}/configurable"


/*
 * Configurable (base)
 */
typedef struct _stdif_configurable		stdif_configurable_t;


/*
 * Configurable (v1.0)
 */
#define STDIF_CONFIGURABLE_ABI_1_0		IV_VERSION(1,0)

typedef struct _stdif_configurable_1_0	stdif_configurable_1_0_t;

LIBAPI
stdif_configurable_propref_t *
			EXTIT_DECL
			stdif_configurable_find_property__1_0(
				stdif_configurable_t *configurable,
				const char *id);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_data__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				void **valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_bool__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				bool *valuep);

LIBAPI
const stdif_configurable_descriptor_t *
			EXTIT_DECL
			stdif_configurable_get_descriptor__1_0(
				stdif_configurable_t *configurable);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_double__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				double *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_enum32__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_float__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				float *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_function__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				extit_func_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_int8__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				int8_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_int16__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				int16_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_int32__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				int32_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_int64__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				int64_t *valuep);

LIBAPI
const stdif_configurable_propdef_t *
			EXTIT_DECL
			stdif_configurable_get_definition__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_uint8__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				uint8_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_uint16__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				uint16_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_uint32__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_uint64__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				uint64_t *valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_get_utf8__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				const char **valuep);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_reset__1_0(
				stdif_configurable_t *configurable);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_bool__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				bool value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_data__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				void *value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_double__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				double value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_enum32__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				uint32_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_float__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				float value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_function__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				extit_func_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_int8__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				int8_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_int16__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				int16_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_int32__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				int32_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_int64__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				int64_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_uint8__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				uint8_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_uint16__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				uint16_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_uint32__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				uint32_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_uint64__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				uint64_t value);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_configurable_set_utf8__1_0(
				stdif_configurable_t *configurable,
				stdif_configurable_propref_t *prop,
				const char *value);


/*
 * ABI Version
 */
#ifndef	STDIF_CONFIGURABLE_ABI_TARGET
#define	STDIF_CONFIGURABLE_ABI_TARGET	STDIF_CONFIGURABLE_ABI_1_0
#endif

#if	IV_VERSION_MAJOR(STDIF_CONFIGURABLE_ABI_TARGET) == 1
#define	stdif_configurable_find_property	\
					stdif_configurable_find_property__1_0

#define	stdif_configurable_get_bool	stdif_configurable_get_bool__1_0
#define	stdif_configurable_get_data	stdif_configurable_get_data__1_0

#define	stdif_configurable_get_definition	\
					stdif_configurable_get_definition__1_0

#define	stdif_configurable_get_descriptor	\
					stdif_configurable_get_descriptor__1_0

#define	stdif_configurable_get_double	stdif_configurable_get_double__1_0
#define	stdif_configurable_get_enum32	stdif_configurable_get_enum32__1_0
#define	stdif_configurable_get_float	stdif_configurable_get_float__1_0
#define	stdif_configurable_get_function	stdif_configurable_get_function__1_0
#define	stdif_configurable_get_int16	stdif_configurable_get_int16__1_0
#define	stdif_configurable_get_int32	stdif_configurable_get_int32__1_0
#define	stdif_configurable_get_int64	stdif_configurable_get_int64__1_0
#define	stdif_configurable_get_int8	stdif_configurable_get_int8__1_0
#define	stdif_configurable_get_uint16	stdif_configurable_get_uint16__1_0
#define	stdif_configurable_get_uint32	stdif_configurable_get_uint32__1_0
#define	stdif_configurable_get_uint64	stdif_configurable_get_uint64__1_0
#define	stdif_configurable_get_uint8	stdif_configurable_get_uint8__1_0
#define	stdif_configurable_get_utf8	stdif_configurable_get_utf8__1_0
#define	stdif_configurable_reset	stdif_configurable_reset__1_0
#define	stdif_configurable_set_bool	stdif_configurable_set_bool__1_0
#define	stdif_configurable_set_data	stdif_configurable_set_data__1_0
#define	stdif_configurable_set_double	stdif_configurable_set_double__1_0
#define	stdif_configurable_set_enum32	stdif_configurable_set_enum32__1_0
#define	stdif_configurable_set_float	stdif_configurable_set_float__1_0
#define	stdif_configurable_set_function	stdif_configurable_set_function__1_0
#define	stdif_configurable_set_int16	stdif_configurable_set_int16__1_0
#define	stdif_configurable_set_int32	stdif_configurable_set_int32__1_0
#define	stdif_configurable_set_int64	stdif_configurable_set_int64__1_0
#define	stdif_configurable_set_int8	stdif_configurable_set_int8__1_0
#define	stdif_configurable_set_uint16	stdif_configurable_set_uint16__1_0
#define	stdif_configurable_set_uint32	stdif_configurable_set_uint32__1_0
#define	stdif_configurable_set_uint64	stdif_configurable_set_uint64__1_0
#define	stdif_configurable_set_uint8	stdif_configurable_set_uint8__1_0
#define	stdif_configurable_set_utf8	stdif_configurable_set_utf8__1_0
#endif	/* IV_VERSION_MAJOR(STDIF_CONFIGURABLE_ABI_TARGET) == 1 */

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__stdif__configurable_h */
