/*
 * @(#) if/configurable_stdimpl/ops.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <if/configurable.h>
#include <if/configurable_impl.h>
#include <if/configurable_stdimpl.h>


EXTIT_EXPORT
if_configurable_ops_1_0_t  if_configurable_stdimpl_ops_1_0	=
{
	/* v0 */
	{
		/* op_reset */
		if_configurable_stdimpl_reset__1_0,

		/* op_find_property */
		if_configurable_stdimpl_find_property__1_0,

		/* op_get_bool */
		if_configurable_stdimpl_get_bool__1_0,

		/* op_get_custom */
		if_configurable_stdimpl_get_custom__1_0,

		/* op_get_double */
		if_configurable_stdimpl_get_double__1_0,

		/* op_get_enum32 */
		if_configurable_stdimpl_get_enum32__1_0,

		/* op_get_float */
		if_configurable_stdimpl_get_float__1_0,

		/* op_get_int8 */
		if_configurable_stdimpl_get_int8__1_0,

		/* op_get_int16 */
		if_configurable_stdimpl_get_int16__1_0,

		/* op_get_int32 */
		if_configurable_stdimpl_get_int32__1_0,

		/* op_get_int64 */
		if_configurable_stdimpl_get_int64__1_0,

		/* op_get_uint8 */
		if_configurable_stdimpl_get_uint8__1_0,

		/* op_get_uint16 */
		if_configurable_stdimpl_get_uint16__1_0,

		/* op_get_uint32 */
		if_configurable_stdimpl_get_uint32__1_0,

		/* op_get_uint64 */
		if_configurable_stdimpl_get_uint64__1_0,

		/* op_get_utf8 */
		if_configurable_stdimpl_get_utf8__1_0,

		/* op_set_bool */
		if_configurable_stdimpl_set_bool__1_0,

		/* op_set_custom */
		if_configurable_stdimpl_set_custom__1_0,

		/* op_set_double */
		if_configurable_stdimpl_set_double__1_0,

		/* op_set_enum32 */
		if_configurable_stdimpl_set_enum32__1_0,

		/* op_set_float */
		if_configurable_stdimpl_set_float__1_0,

		/* op_set_int8 */
		if_configurable_stdimpl_set_int8__1_0,

		/* op_set_int16 */
		if_configurable_stdimpl_set_int16__1_0,

		/* op_set_int32 */
		if_configurable_stdimpl_set_int32__1_0,

		/* op_set_int64 */
		if_configurable_stdimpl_set_int64__1_0,

		/* op_set_uint8 */
		if_configurable_stdimpl_set_uint8__1_0,

		/* op_set_uint16 */
		if_configurable_stdimpl_set_uint16__1_0,

		/* op_set_uint32 */
		if_configurable_stdimpl_set_uint32__1_0,

		/* op_set_uint64 */
		if_configurable_stdimpl_set_uint64__1_0,

		/* op_set_utf8 */
		if_configurable_stdimpl_set_utf8__1_0
	}
};
