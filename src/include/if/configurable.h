/*
 * @(#) if/configurable.h
 *
 * Configurable Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__configurable_h
#define	__if__configurable_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_configurable_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


/*
 * Configurable Interface ID
 */
#define IF_CONFIGURABLE_IID		"{e89cceaa-459c-11e6-9660-406186e454c1}/configurable"

/*
 * Configurable (v1.0)
 */
#define IF_CONFIGURABLE_ABI_1_0	IV_VERSION(1,0)

typedef struct _if_configurable_1_0	if_configurable_1_0_t;

typedef enum if_configurable_type
{
	IF_CONFIGURABLE_TYPE_BOOL	= 0,
	IF_CONFIGURABLE_TYPE_DOUBLE	= 1,
	IF_CONFIGURABLE_TYPE_ENUM32	= 2,
	IF_CONFIGURABLE_TYPE_FLOAT	= 3,
	IF_CONFIGURABLE_TYPE_INT8	= 4,
	IF_CONFIGURABLE_TYPE_INT16	= 5,
	IF_CONFIGURABLE_TYPE_INT32	= 6,
	IF_CONFIGURABLE_TYPE_INT64	= 7,
	IF_CONFIGURABLE_TYPE_UINT8	= 8,
	IF_CONFIGURABLE_TYPE_UINT16	= 9,
	IF_CONFIGURABLE_TYPE_UINT32	= 10,
	IF_CONFIGURABLE_TYPE_UINT64	= 11,
	IF_CONFIGURABLE_TYPE_UTF8	= 12,
	IF_CONFIGURABLE_TYPE_CUSTOM	= 13
} if_configurable_type_t;


#define	IF_CONFIGURABLE_STATUS_MISMATCH	\
			((extit_status_t) (EXTIT_STATUS_CUSTOM_BASE + 0))

#define	IF_CONFIGURABLE_STATUS_BADLEN	\
			((extit_status_t) (EXTIT_STATUS_CUSTOM_BASE + 1))


typedef struct _if_configurable_enum32
{
	const char *		id;
	const char *		name;
	const char *		description;
	uint32_t		value;
} if_configurable_enum32_t;


typedef struct _if_configurable_propspec_bool
{
	extit_bool_t		def_value;
} if_configurable_propspec_bool_t;


typedef struct _if_configurable_propspec_custom
{
	void *			def_value;
} if_configurable_propspec_custom_t;


typedef struct _if_configurable_propspec_double
{
	double			min_value;
	double			max_value;
	double			step_hint;
	double			def_value;
} if_configurable_propspec_double_t;


typedef struct _if_configurable_propspec_enum32
{
	const if_configurable_enum32_t *
				choices;

	uint32_t		choice_count;
	uint32_t		def_value;
} if_configurable_propspec_enum32_t;


typedef struct _if_configurable_propspec_float
{
	float			min_value;
	float			max_value;
	float			step_hint;
	float			def_value;
} if_configurable_propspec_float_t;


typedef struct _if_configurable_propspec_int8
{
	int8_t			min_value;
	int8_t			max_value;
	int8_t			def_value;
} if_configurable_propspec_int8_t;


typedef struct _if_configurable_propspec_int16
{
	int16_t			min_value;
	int16_t			max_value;
	int16_t			def_value;
} if_configurable_propspec_int16_t;


typedef struct _if_configurable_propspec_int32
{
	int32_t			min_value;
	int32_t			max_value;
	int32_t			def_value;
} if_configurable_propspec_int32_t;


typedef struct _if_configurable_propspec_int64
{
	int64_t			min_value;
	int64_t			max_value;
	int64_t			def_value;
} if_configurable_propspec_int64_t;


typedef struct _if_configurable_propspec_uint8
{
	uint8_t			min_value;
	uint8_t			max_value;
	uint8_t			def_value;
} if_configurable_propspec_uint8_t;


typedef struct _if_configurable_propspec_uint16
{
	uint16_t		min_value;
	uint16_t		max_value;
	uint16_t		def_value;
} if_configurable_propspec_uint16_t;


typedef struct _if_configurable_propspec_uint32
{
	uint32_t		min_value;
	uint32_t		max_value;
	uint32_t		def_value;
} if_configurable_propspec_uint32_t;


typedef struct _if_configurable_propspec_uint64
{
	uint64_t		min_value;
	uint64_t		max_value;
	uint64_t		def_value;
} if_configurable_propspec_uint64_t;


typedef struct _if_configurable_propspec_utf8
{
	const char *		def_value;
} if_configurable_propspec_utf8_t;


typedef struct _if_configurable_propdef
{
	const char *		id;
	const char *		name;
	const char *		description;
	if_configurable_type_t	type;

	union
	{
		if_configurable_propspec_bool_t		type_bool;
		if_configurable_propspec_custom_t	type_custom;
		if_configurable_propspec_double_t	type_double;
		if_configurable_propspec_enum32_t	type_enum32;
		if_configurable_propspec_float_t	type_float;
		if_configurable_propspec_int8_t		type_int8;
		if_configurable_propspec_int16_t	type_int16;
		if_configurable_propspec_int32_t	type_int32;
		if_configurable_propspec_int64_t	type_int64;
		if_configurable_propspec_uint8_t	type_uint8;
		if_configurable_propspec_uint16_t	type_uint16;
		if_configurable_propspec_uint32_t	type_uint32;
		if_configurable_propspec_uint64_t	type_uint64;
		if_configurable_propspec_utf8_t		type_utf8;
	} spec;
} if_configurable_propdef_t;


typedef struct _if_configurable_descriptor
{
	const if_configurable_propdef_t **
				properties;

	uint32_t		count;
} if_configurable_descriptor_t;


typedef struct if_configurable_propref	if_configurable_propref_t;


/*
 * ABI Version
 */
#ifndef	IF_CONFIGURABLE_ABI_TARGET
#define	IF_CONFIGURABLE_ABI_TARGET	IF_CONFIGURABLE_ABI_1_0
#endif

#if	IF_CONFIGURABLE_ABI_TARGET == IF_CONFIGURABLE_ABI_1_0
#define	if_configurable_t		if_configurable_1_0_t
#else
#error	Unsupported IF_CONFIGURABLE_ABI_TARGET version
#endif


/*
 * Public API (v1.0)
 */
LIBAPI
if_configurable_propref_t *
			EXTIT_DECL
			if_configurable_find_property(
				if_configurable_t *configurable,
				const char *id);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_custom(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				void **valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_bool(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				extit_bool_t *valuep);

LIBAPI
const if_configurable_descriptor_t *
			EXTIT_DECL
			if_configurable_get_descriptor(
				if_configurable_t *configurable);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_double(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				double *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_enum32(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_float(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				float *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int8(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				int8_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int16(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				int16_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int32(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				int32_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_int64(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				int64_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint8(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				uint8_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint16(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				uint16_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint32(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				uint32_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_uint64(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				uint64_t *valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_get_utf8(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				const char **valuep);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_reset(
				if_configurable_t *configurable);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_bool(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				extit_bool_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_custom(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				void *value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_double(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				double value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_enum32(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				uint32_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_float(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				float value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int8(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				int8_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int16(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				int16_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int32(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				int32_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_int64(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				int64_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint8(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				uint8_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint16(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				uint16_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint32(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				uint32_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_uint64(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				uint64_t value);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_configurable_set_utf8(
				if_configurable_t *configurable,
				if_configurable_propref_t *prop,
				const char *value);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__configurable_h */
