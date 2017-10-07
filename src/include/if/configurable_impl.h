/*
 * @(#) if/configurable_impl.h
 *
 * Configurable Interface - implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__configurable_impl_h
#define	__if__configurable_impl_h

#include <extit/base.h>
#include <if/configurable.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Configurable operations (v1.0 component)
 */
typedef struct _if_configurable_ops_comp_1_0
{
	extit_status_t
				(EXTIT_DECL *op_reset)(
					if_configurable_1_0_t *conf);

	if_configurable_propref_t *
				(EXTIT_DECL *op_find_property)(
					if_configurable_1_0_t *conf,
					const char *id);

	extit_status_t
				(EXTIT_DECL *op_get_bool)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					extit_bool_t *valuep);

	extit_status_t
				(EXTIT_DECL *op_get_custom)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					void **valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_double)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					double *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_enum32)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					uint32_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_float)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					float *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int8)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					int8_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int16)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					int16_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int32)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					int32_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int64)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					int64_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint8)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					uint8_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint16)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					uint16_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint32)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					uint32_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint64)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					uint64_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_utf8)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					const char **valuep);

	extit_status_t	
				(EXTIT_DECL *op_set_bool)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					extit_bool_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_custom)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					void *value);

	extit_status_t	
				(EXTIT_DECL *op_set_double)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					double value);

	extit_status_t	
				(EXTIT_DECL *op_set_enum32)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					uint32_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_float)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					float value);

	extit_status_t	
				(EXTIT_DECL *op_set_int8)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					int8_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_int16)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					int16_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_int32)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					int32_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_int64)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					int64_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint8)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					uint8_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint16)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					uint16_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint32)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					uint32_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint64)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					uint64_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_utf8)(
					if_configurable_1_0_t *conf,
					if_configurable_propref_t *prop,
					const char *value);
} if_configurable_ops_comp_1_0_t;


/*
 * Configurable operations (v1.0)
 */
typedef struct _if_configurable_ops_1_0
{
	if_configurable_ops_comp_1_0_t		v0;	/* [1].0 component */
} if_configurable_ops_1_0_t;


/*
 * Configurable (base)
 */
struct _if_configurable
{
	iv_version_t				version;
};


/*
 * Configurable (v1.0)
 */
struct _if_configurable_1_0
{
	/* base */
	iv_version_t				version;	/* 1.0+ */

	/* 1.0+ */
	if_configurable_ops_1_0_t *		ops;
	const if_configurable_descriptor_t *	descriptor;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__configurable_impl_h */
