/*
 * @(#) stdif/configurable_stdimpl/ops.c
 *
 * Configurable Interface - Operators standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


/**
 * Standard implementation operators for a configurable 1.0 interface.
 *
 * @since	1.0
 */
stdif_configurable_ops_1_0_t  stdif_configurable_stdimpl_ops_1_0	=
{
	/* v0 */
	{
		/* op_get_descriptor */
		stdif_configurable_stdimpl_get_descriptor__1_0,

		/* op_reset */
		stdif_configurable_stdimpl_reset__1_0,

		/* op_find_property */
		stdif_configurable_stdimpl_find_property__1_0,

		/* op_get_bool */
		stdif_configurable_stdimpl_get_bool__1_0,

		/* op_get_data */
		stdif_configurable_stdimpl_get_data__1_0,

		/* op_get_double */
		stdif_configurable_stdimpl_get_double__1_0,

		/* op_get_enum32 */
		stdif_configurable_stdimpl_get_enum32__1_0,

		/* op_get_float */
		stdif_configurable_stdimpl_get_float__1_0,

		/* op_get_function */
		stdif_configurable_stdimpl_get_function__1_0,

		/* op_get_int8 */
		stdif_configurable_stdimpl_get_int8__1_0,

		/* op_get_int16 */
		stdif_configurable_stdimpl_get_int16__1_0,

		/* op_get_int32 */
		stdif_configurable_stdimpl_get_int32__1_0,

		/* op_get_int64 */
		stdif_configurable_stdimpl_get_int64__1_0,

		/* op_get_uint8 */
		stdif_configurable_stdimpl_get_uint8__1_0,

		/* op_get_uint16 */
		stdif_configurable_stdimpl_get_uint16__1_0,

		/* op_get_uint32 */
		stdif_configurable_stdimpl_get_uint32__1_0,

		/* op_get_uint64 */
		stdif_configurable_stdimpl_get_uint64__1_0,

		/* op_get_utf8 */
		stdif_configurable_stdimpl_get_utf8__1_0,

		/* op_set_bool */
		stdif_configurable_stdimpl_set_bool__1_0,

		/* op_set_data */
		stdif_configurable_stdimpl_set_data__1_0,

		/* op_set_double */
		stdif_configurable_stdimpl_set_double__1_0,

		/* op_set_enum32 */
		stdif_configurable_stdimpl_set_enum32__1_0,

		/* op_set_float */
		stdif_configurable_stdimpl_set_float__1_0,

		/* op_set_function */
		stdif_configurable_stdimpl_set_function__1_0,

		/* op_set_int8 */
		stdif_configurable_stdimpl_set_int8__1_0,

		/* op_set_int16 */
		stdif_configurable_stdimpl_set_int16__1_0,

		/* op_set_int32 */
		stdif_configurable_stdimpl_set_int32__1_0,

		/* op_set_int64 */
		stdif_configurable_stdimpl_set_int64__1_0,

		/* op_set_uint8 */
		stdif_configurable_stdimpl_set_uint8__1_0,

		/* op_set_uint16 */
		stdif_configurable_stdimpl_set_uint16__1_0,

		/* op_set_uint32 */
		stdif_configurable_stdimpl_set_uint32__1_0,

		/* op_set_uint64 */
		stdif_configurable_stdimpl_set_uint64__1_0,

		/* op_set_utf8 */
		stdif_configurable_stdimpl_set_utf8__1_0
	}
};
