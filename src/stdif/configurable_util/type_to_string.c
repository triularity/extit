/*
 * @(#) stdif/configurable_util/type_to_string.c
 *
 * Get the string representation of a configurable interface property type.
 *
 * Copyright (c) 2017-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <iv/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_util.h>

/**
 * Map a @{code STDIF_CONFIGURABLE_TYPE_}* value to its string.
 * The value returned is the same as its constant, minus the
 * @{code STDIF_CONFIGURABLE_TYPE_} prefix.
 *
 * @param	type		A configurable type.
 *
 * @return	A string representation, or @{constant NULL} if unknown.
 *
 * @since	1.0
 */
const char *
EXTIT_DECL
stdif_configurable_type_to_string
(
	stdif_configurable_type_t type
)
{
	switch(type)
	{
		case STDIF_CONFIGURABLE_TYPE_BOOL:
			return "BOOL";

		case STDIF_CONFIGURABLE_TYPE_DATA:
			return "DATA";

		case STDIF_CONFIGURABLE_TYPE_DOUBLE:
			return "DOUBLE";

		case STDIF_CONFIGURABLE_TYPE_ENUM32:
			return "ENUM32";

		case STDIF_CONFIGURABLE_TYPE_FLOAT:
			return "FLOAT";

		case STDIF_CONFIGURABLE_TYPE_FUNCTION:
			return "FUNCTION";

		case STDIF_CONFIGURABLE_TYPE_INT8:
			return "INT8";

		case STDIF_CONFIGURABLE_TYPE_INT16:
			return "INT16";

		case STDIF_CONFIGURABLE_TYPE_INT32:
			return "INT32";

		case STDIF_CONFIGURABLE_TYPE_INT64:
			return "INT64";

		case STDIF_CONFIGURABLE_TYPE_UINT8:
			return "UINT8";

		case STDIF_CONFIGURABLE_TYPE_UINT16:
			return "UINT16";

		case STDIF_CONFIGURABLE_TYPE_UINT32:
			return "UINT32";

		case STDIF_CONFIGURABLE_TYPE_UINT64:
			return "UINT64";

		case STDIF_CONFIGURABLE_TYPE_UTF8:
			return "UTF8";

		default:
			return NULL;
	}
}
