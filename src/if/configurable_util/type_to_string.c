/*
 * @(#) if/configurable_util/type_to_string.c
 *
 * Get the string representation of a configurable interface property type.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <iv/base.h>
#include <if/configurable.h>
#include <if/configurable_util.h>


const char *
EXTIT_DECL
if_configurable_type_to_string
(
	if_configurable_type_t type
)
{
	switch(type)
	{
		case IF_CONFIGURABLE_TYPE_BOOL:
			return "BOOL";

		case IF_CONFIGURABLE_TYPE_DATA:
			return "DATA";

		case IF_CONFIGURABLE_TYPE_DOUBLE:
			return "DOUBLE";

		case IF_CONFIGURABLE_TYPE_ENUM32:
			return "ENUM32";

		case IF_CONFIGURABLE_TYPE_FLOAT:
			return "FLOAT";

		case IF_CONFIGURABLE_TYPE_FUNCTION:
			return "FUNCTION";

		case IF_CONFIGURABLE_TYPE_INT8:
			return "INT8";

		case IF_CONFIGURABLE_TYPE_INT16:
			return "INT16";

		case IF_CONFIGURABLE_TYPE_INT32:
			return "INT32";

		case IF_CONFIGURABLE_TYPE_INT64:
			return "INT64";

		case IF_CONFIGURABLE_TYPE_UINT8:
			return "UINT8";

		case IF_CONFIGURABLE_TYPE_UINT16:
			return "UINT16";

		case IF_CONFIGURABLE_TYPE_UINT32:
			return "UINT32";

		case IF_CONFIGURABLE_TYPE_UINT64:
			return "UINT64";

		case IF_CONFIGURABLE_TYPE_UTF8:
			return "UTF8";

		default:
			return NULL;
	}
}
