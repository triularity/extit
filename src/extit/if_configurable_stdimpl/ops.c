/*
 * @(#) extit/if_configurable_stdimpl/ops.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/if/configurable.h>
#include <extit/if/configurable_impl.h>
#include <extit/if/configurable_stdimpl.h>


EXTIT_EXPORT
extit_if_configurable_ops_1_0_t  extit_if_configurable_stdimpl_ops_1_0	=
{
	extit_if_configurable_reset_stdimpl,		/* op_reset */
	extit_if_configurable_find_property_stdimpl,	/* op_find_property */
	extit_if_configurable_get_bool_stdimpl,		/* op_get_bool */
	extit_if_configurable_get_custom_stdimpl,	/* op_get_custom */
	extit_if_configurable_get_double_stdimpl,	/* op_get_double */
	extit_if_configurable_get_enum32_stdimpl,	/* op_get_enum32 */
	extit_if_configurable_get_float_stdimpl,	/* op_get_float */
	extit_if_configurable_get_int8_stdimpl,		/* op_get_int8 */
	extit_if_configurable_get_int16_stdimpl,	/* op_get_int16 */
	extit_if_configurable_get_int32_stdimpl,	/* op_get_int32 */
	extit_if_configurable_get_int64_stdimpl,	/* op_get_int64 */
	extit_if_configurable_get_uint8_stdimpl,	/* op_get_uint8 */
	extit_if_configurable_get_uint16_stdimpl,	/* op_get_uint16 */
	extit_if_configurable_get_uint32_stdimpl,	/* op_get_uint32 */
	extit_if_configurable_get_uint64_stdimpl,	/* op_get_uint64 */
	extit_if_configurable_get_utf8_stdimpl,		/* op_get_utf8 */
	extit_if_configurable_set_bool_stdimpl,		/* op_set_bool */
	extit_if_configurable_set_custom_stdimpl,	/* op_set_custom */
	extit_if_configurable_set_double_stdimpl,	/* op_set_double */
	extit_if_configurable_set_enum32_stdimpl,	/* op_set_enum32 */
	extit_if_configurable_set_float_stdimpl,	/* op_set_float */
	extit_if_configurable_set_int8_stdimpl,		/* op_set_int8 */
	extit_if_configurable_set_int16_stdimpl,	/* op_set_int16 */
	extit_if_configurable_set_int32_stdimpl,	/* op_set_int32 */
	extit_if_configurable_set_int64_stdimpl,	/* op_set_int64 */
	extit_if_configurable_set_uint8_stdimpl,	/* op_set_uint8 */
	extit_if_configurable_set_uint16_stdimpl,	/* op_set_uint16 */
	extit_if_configurable_set_uint32_stdimpl,	/* op_set_uint32 */
	extit_if_configurable_set_uint64_stdimpl,	/* op_set_uint64 */
	extit_if_configurable_set_utf8_stdimpl		/* op_set_utf8 */
};
