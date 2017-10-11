/*
 * @(#) stdif/configurable_util/get_enum32_id.c
 *
 * Find a configurable interface enum descriptor by value.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_util.h>


const stdif_configurable_enum32_t *
EXTIT_DECL
stdif_configurable_enum32_find_by_value
(
	const stdif_configurable_enum32_t *choices,
	uint32_t count,
	uint32_t value
)
{
	while(count-- != 0)
	{
		if(choices->value == value)
			return choices;

		choices++;
	}

	return NULL;
}
