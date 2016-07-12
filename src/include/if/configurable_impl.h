/*
 * @(#) if/configurable_impl.h
 *
 * Configurable Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__configurable_impl_h
#define	__if__configurable_impl_h

#include <extit/base.h>
#include <if/configurable.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _if_configurable_1_0_ops
{
	extit_status_t
				(EXTIT_DECL *op_reset)(
					if_configurable_t *conf);

	if_configurable_propref_t *
				(EXTIT_DECL *op_find_property)(
					if_configurable_t *conf,
					const char *id);

	extit_status_t
				(EXTIT_DECL *op_get_bool)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					extit_bool_t *valuep);

	extit_status_t
				(EXTIT_DECL *op_get_custom)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					void **valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_double)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					double *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_enum32)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					uint32_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_float)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					float *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int8)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					int8_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int16)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					int16_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int32)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					int32_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int64)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					int64_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint8)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					uint8_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint16)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					uint16_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint32)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					uint32_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint64)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					uint64_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_utf8)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					const char **valuep);

	extit_status_t	
				(EXTIT_DECL *op_set_bool)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					extit_bool_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_custom)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					void *value);

	extit_status_t	
				(EXTIT_DECL *op_set_double)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					double value);

	extit_status_t	
				(EXTIT_DECL *op_set_enum32)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					uint32_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_float)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					float value);

	extit_status_t	
				(EXTIT_DECL *op_set_int8)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					int8_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_int16)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					int16_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_int32)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					int32_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_int64)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					int64_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint8)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					uint8_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint16)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					uint16_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint32)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					uint32_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint64)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					uint64_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_utf8)(
					if_configurable_t *conf,
					if_configurable_propref_t *prop,
					const char *value);
} if_configurable_ops_1_0_t;


struct _if_configurable_1_0
{
	iv_version_t				version;
	if_configurable_ops_1_0_t *		ops;
	const if_configurable_descriptor_t *	descriptor;
};


#define	IF_CONFIGURABLE_RESET(conf)	\
			((conf)->ops->op_reset(conf))

#define	IF_CONFIGURABLE_FIND_PROPERTY(conf, id)	\
			((conf)->ops->op_find_property((conf), (id)))

#define	IF_CONFIGURABLE_GET_BOOL(conf, prop, valuep)	\
			((conf)->ops->op_get_bool((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_CUSTOM(conf, prop, valuep)	\
			((conf)->ops->op_get_custom((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_DOUBLE(conf, prop, valuep)	\
			((conf)->ops->op_get_double((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_ENUM32(conf, prop, valuep)	\
			((conf)->ops->op_get_enum32((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_FLOAT(conf, prop, valuep)	\
			((conf)->ops->op_get_float((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_INT8(conf, prop, valuep)	\
			((conf)->ops->op_get_int8((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_INT16(conf, prop, valuep)	\
			((conf)->ops->op_get_int16((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_INT32(conf, prop, valuep)	\
			((conf)->ops->op_get_int32((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_INT64(conf, prop, valuep)	\
			((conf)->ops->op_get_int64((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_UINT8(conf, prop, valuep)	\
			((conf)->ops->op_get_uint8((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_UINT16(conf, prop, valuep)	\
			((conf)->ops->op_get_uint16((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_UINT32(conf, prop, valuep)	\
			((conf)->ops->op_get_uint32((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_UINT64(conf, prop, valuep)	\
			((conf)->ops->op_get_uint64((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_GET_UTF8(conf, prop, valuep)	\
			((conf)->ops->op_get_utf8((conf), (prop), (valuep)))

#define	IF_CONFIGURABLE_SET_BOOL(conf, prop, value)	\
			((conf)->ops->op_set_bool((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_CUSTOM(conf, prop, value)	\
			((conf)->ops->op_set_custom((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_DOUBLE(conf, prop, value)	\
			((conf)->ops->op_set_double((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_ENUM32(conf, prop, value)	\
			((conf)->ops->op_set_enum32((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_FLOAT(conf, prop, value)	\
			((conf)->ops->op_set_float((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_INT8(conf, prop, value)	\
			((conf)->ops->op_set_int8((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_INT16(conf, prop, value)	\
			((conf)->ops->op_set_int16((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_INT32(conf, prop, value)	\
			((conf)->ops->op_set_int32((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_INT64(conf, prop, value)	\
			((conf)->ops->op_set_int64((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_UINT8(conf, prop, value)	\
			((conf)->ops->op_set_uint8((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_UINT16(conf, prop, value)	\
			((conf)->ops->op_set_uint16((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_UINT32(conf, prop, value)	\
			((conf)->ops->op_set_uint32((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_UINT64(conf, prop, value)	\
			((conf)->ops->op_set_uint64((conf), (prop), (value)))

#define	IF_CONFIGURABLE_SET_UTF8(conf, prop, value)	\
			((conf)->ops->op_set_utf8((conf), (prop), (value)))

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__configurable_impl_h */
