/*
 * @(#) extit/if/configurable.h
 *
 * Configurable Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__configurable_h
#define	__extit__if__configurable_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	extit_if_configurable_EXPORTS
#define	EXTIT_IF_CONFIGURABLE_LIBAPI	EXTIT_EXPORT
#else
#define	EXTIT_IF_CONFIGURABLE_LIBAPI	EXTIT_IMPORT
#endif


/*
 * Configurable Interface ID
 */
#define EXTIT_IF_CONFIGURABLE_IID	"{e89cceaa-459c-11e6-9660-406186e454c1}/configurable"

/*
 * Configurable (v1.0)
 */
#define EXTIT_IF_CONFIGURABLE_ABI_1_0	IV_VERSION(1,0)

typedef struct _extit_if_configurable_1_0
					extit_if_configurable_1_0_t;

typedef enum extit_if_configurable_type
{
	EXTIT_IF_CONFIGURABLE_TYPE_BOOL		= 0,
	EXTIT_IF_CONFIGURABLE_TYPE_DOUBLE	= 1,
	EXTIT_IF_CONFIGURABLE_TYPE_ENUM32	= 2,
	EXTIT_IF_CONFIGURABLE_TYPE_FLOAT	= 3,
	EXTIT_IF_CONFIGURABLE_TYPE_INT8		= 4,
	EXTIT_IF_CONFIGURABLE_TYPE_INT16	= 5,
	EXTIT_IF_CONFIGURABLE_TYPE_INT32	= 6,
	EXTIT_IF_CONFIGURABLE_TYPE_INT64	= 7,
	EXTIT_IF_CONFIGURABLE_TYPE_UINT8	= 8,
	EXTIT_IF_CONFIGURABLE_TYPE_UINT16	= 9,
	EXTIT_IF_CONFIGURABLE_TYPE_UINT32	= 10,
	EXTIT_IF_CONFIGURABLE_TYPE_UINT64	= 11,
	EXTIT_IF_CONFIGURABLE_TYPE_UTF8		= 12,
	EXTIT_IF_CONFIGURABLE_TYPE_CUSTOM	= 13
} extit_if_configurable_type_t;


#define	EXTIT_IF_CONFIGURABLE_STATUS_MISMATCH	\
		((extit_status_t) (EXTIT_STATUS_CUSTOM_BASE + 0))

#define	EXTIT_IF_CONFIGURABLE_STATUS_BADLEN	\
		((extit_status_t) (EXTIT_STATUS_CUSTOM_BASE + 1))


typedef struct _extit_if_configurable_enum32
{
	const char *		id;
	const char *		name;
	const char *		description;
	uint32_t		value;
} extit_if_configurable_enum32_t;


typedef struct _extit_if_configurable_propspec_bool
{
	extit_bool_t		def_value;
} extit_if_configurable_propspec_bool_t;


typedef struct _extit_if_configurable_propspec_custom
{
	void *			def_value;
} extit_if_configurable_propspec_custom_t;


typedef struct _extit_if_configurable_propspec_double
{
	double			min_value;
	double			max_value;
	double			step_hint;
	double			def_value;
} extit_if_configurable_propspec_double_t;


typedef struct _extit_if_configurable_propspec_enum32
{
	const extit_if_configurable_enum32_t *
				choices;

	uint32_t		choice_count;
	uint32_t		def_value;
} extit_if_configurable_propspec_enum32_t;


typedef struct _extit_if_configurable_propspec_float
{
	float			min_value;
	float			max_value;
	float			step_hint;
	float			def_value;
} extit_if_configurable_propspec_float_t;


typedef struct _extit_if_configurable_propspec_int8
{
	int8_t			min_value;
	int8_t			max_value;
	int8_t			def_value;
} extit_if_configurable_propspec_int8_t;


typedef struct _extit_if_configurable_propspec_int16
{
	int16_t			min_value;
	int16_t			max_value;
	int16_t			def_value;
} extit_if_configurable_propspec_int16_t;


typedef struct _extit_if_configurable_propspec_int32
{
	int32_t			min_value;
	int32_t			max_value;
	int32_t			def_value;
} extit_if_configurable_propspec_int32_t;


typedef struct _extit_if_configurable_propspec_int64
{
	int64_t			min_value;
	int64_t			max_value;
	int64_t			def_value;
} extit_if_configurable_propspec_int64_t;


typedef struct _extit_if_configurable_propspec_uint8
{
	uint8_t			min_value;
	uint8_t			max_value;
	uint8_t			def_value;
} extit_if_configurable_propspec_uint8_t;


typedef struct _extit_if_configurable_propspec_uint16
{
	uint16_t		min_value;
	uint16_t		max_value;
	uint16_t		def_value;
} extit_if_configurable_propspec_uint16_t;


typedef struct _extit_if_configurable_propspec_uint32
{
	uint32_t		min_value;
	uint32_t		max_value;
	uint32_t		def_value;
} extit_if_configurable_propspec_uint32_t;


typedef struct _extit_if_configurable_propspec_uint64
{
	uint64_t		min_value;
	uint64_t		max_value;
	uint64_t		def_value;
} extit_if_configurable_propspec_uint64_t;


typedef struct _extit_if_configurable_propspec_utf8
{
	const char *		def_value;
} extit_if_configurable_propspec_utf8_t;


typedef struct _extit_if_configurable_propdef
{
	const char *			id;
	const char *			name;
	const char *			description;
	extit_if_configurable_type_t	type;

	union
	{
		extit_if_configurable_propspec_bool_t		type_bool;
		extit_if_configurable_propspec_custom_t		type_custom;
		extit_if_configurable_propspec_double_t		type_double;
		extit_if_configurable_propspec_enum32_t		type_enum32;
		extit_if_configurable_propspec_float_t		type_float;
		extit_if_configurable_propspec_int8_t		type_int8;
		extit_if_configurable_propspec_int16_t		type_int16;
		extit_if_configurable_propspec_int32_t		type_int32;
		extit_if_configurable_propspec_int64_t		type_int64;
		extit_if_configurable_propspec_uint8_t		type_uint8;
		extit_if_configurable_propspec_uint16_t		type_uint16;
		extit_if_configurable_propspec_uint32_t		type_uint32;
		extit_if_configurable_propspec_uint64_t		type_uint64;
		extit_if_configurable_propspec_utf8_t		type_utf8;
	} spec;
} extit_if_configurable_propdef_t;


typedef struct _extit_if_configurable_descriptor
{
	const extit_if_configurable_propdef_t **
					properties;

	unsigned int			count;
} extit_if_configurable_descriptor_t;


typedef struct extit_if_configurable_propref
					extit_if_configurable_propref_t;


/*
 * ABI Version
 */
#define	EXTIT_IF_CONFIGURABLE_ABI	EXTIT_IF_CONFIGURABLE_ABI_1_0

#ifndef	EXTIT_IF_CONFIGURABLE_ABI_TARGET
#define	EXTIT_IF_CONFIGURABLE_ABI_TARGET	\
					EXTIT_IF_CONFIGURABLE_ABI
#endif

#if	EXTIT_IF_CONFIGURABLE_ABI_TARGET == EXTIT_IF_CONFIGURABLE_ABI_1_0
#define	extit_if_configurable_t		extit_if_configurable_1_0_t
#else
#error	Unsupported EXTIT_IF_CONFIGURABLE_ABI_TARGET version
#endif


/*
 * Public API (v1.0)
 */
EXTIT_IF_CONFIGURABLE_LIBAPI
extit_if_configurable_propref_t *
			EXTIT_DECL
			extit_if_configurable_find_property(
				extit_if_configurable_t *configurable,
				const char *id);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_custom(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				void **valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_bool(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				extit_bool_t *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
const extit_if_configurable_descriptor_t *
			EXTIT_DECL
			extit_if_configurable_get_descriptor(
				extit_if_configurable_t *configurable);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_double(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				double *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_enum32(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				uint32_t *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_float(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				float *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int8(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				int8_t *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int16(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				int16_t *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int32(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				int32_t *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_int64(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				int64_t *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint8(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				uint8_t *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint16(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				uint16_t *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint32(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				uint32_t *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_uint64(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				uint64_t *valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_get_utf8(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				const char **valuep);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_reset(
				extit_if_configurable_t *configurable);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_bool(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				extit_bool_t value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_custom(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				void *value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_double(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				double value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_enum32(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				uint32_t value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_float(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				float value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int8(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				int8_t value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int16(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				int16_t value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int32(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				int32_t value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_int64(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				int64_t value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint8(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				uint8_t value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint16(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				uint16_t value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint32(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				uint32_t value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_uint64(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				uint64_t value);

EXTIT_IF_CONFIGURABLE_LIBAPI
extit_status_t
			EXTIT_DECL
			extit_if_configurable_set_utf8(
				extit_if_configurable_t *configurable,
				extit_if_configurable_propref_t *prop,
				const char *value);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__configurable_h */
