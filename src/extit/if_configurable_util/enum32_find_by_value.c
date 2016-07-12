/*
 * @(#) extit/if_configurable_util/get_enum32_id.c
 *
 * Configurable Interface utilities.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <extit/if/configurable.h>
#include <extit/if/configurable_util.h>


EXTIT_EXPORT
const extit_if_configurable_enum32_t *
EXTIT_DECL
extit_if_configurable_enum32_find_by_value
(
	const extit_if_configurable_enum32_t *choices,
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
