/*
 * @(#) stdif/configurable_impl.h
 *
 * Configurable Interface - implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__configurable_impl_h
#define	__stdif__configurable_impl_h

#include <extit/base.h>
#include <stdif/configurable.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Configurable operations (v1.0 component)
 */
typedef struct _stdif_configurable_ops_comp_1_0
{
	const stdif_configurable_descriptor_t *
				(EXTIT_DECL *op_get_descriptor)(
					stdif_configurable_1_0_t *conf);

	extit_status_t
				(EXTIT_DECL *op_reset)(
					stdif_configurable_1_0_t *conf);

	stdif_configurable_propref_t *
				(EXTIT_DECL *op_find_property)(
					stdif_configurable_1_0_t *conf,
					const char *id);

	extit_status_t
				(EXTIT_DECL *op_get_bool)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					extit_bool_t *valuep);

	extit_status_t
				(EXTIT_DECL *op_get_data)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					void **valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_double)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					double *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_enum32)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					uint32_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_float)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					float *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_function)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					extit_func_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int8)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					int8_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int16)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					int16_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int32)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					int32_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_int64)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					int64_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint8)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					uint8_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint16)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					uint16_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint32)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					uint32_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_uint64)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					uint64_t *valuep);

	extit_status_t	
				(EXTIT_DECL *op_get_utf8)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					const char **valuep);

	extit_status_t	
				(EXTIT_DECL *op_set_bool)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					extit_bool_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_data)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					void *value);

	extit_status_t	
				(EXTIT_DECL *op_set_double)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					double value);

	extit_status_t	
				(EXTIT_DECL *op_set_enum32)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					uint32_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_float)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					float value);

	extit_status_t	
				(EXTIT_DECL *op_set_function)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					extit_func_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_int8)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					int8_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_int16)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					int16_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_int32)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					int32_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_int64)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					int64_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint8)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					uint8_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint16)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					uint16_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint32)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					uint32_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_uint64)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					uint64_t value);

	extit_status_t	
				(EXTIT_DECL *op_set_utf8)(
					stdif_configurable_1_0_t *conf,
					stdif_configurable_propref_t *prop,
					const char *value);
} stdif_configurable_ops_comp_1_0_t;


/*
 * Configurable operations (v1.0)
 */
typedef struct _stdif_configurable_ops_1_0
{
	stdif_configurable_ops_comp_1_0_t	v0;	/* [1].0 component */
} stdif_configurable_ops_1_0_t;


/*
 * Configurable (base)
 */
struct _stdif_configurable
{
	iv_version_t				version;
};


/*
 * Configurable (v1.0)
 */
struct _stdif_configurable_1_0
{
	/* base */
	iv_version_t				version;	/* 1.0+ */

	/* 1.0+ */
	stdif_configurable_ops_1_0_t *		ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__stdif__configurable_impl_h */
