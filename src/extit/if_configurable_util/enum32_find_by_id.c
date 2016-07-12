/*
 * @(#) extit/if_configurable_util/get_enum32_id.c
 *
 * Configurable Interface utilities.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <extit/if/configurable.h>
#include <extit/if/configurable_util.h>


EXTIT_EXPORT
const extit_if_configurable_enum32_t *
EXTIT_DECL
extit_if_configurable_enum32_find_by_id
(
	const extit_if_configurable_enum32_t *choices,
	uint32_t count,
	const char *id
)
{
	while(count-- != 0)
	{
		if(strcmp(choices->id, id) == 0)
			return choices;

		choices++;
	}

	return NULL;
}
