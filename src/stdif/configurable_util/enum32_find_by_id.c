/*
 * @(#) stdif/configurable_util/get_enum32_id.c
 *
 * Find a configurable interface enum descriptor by ID.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_util.h>


/**
 * Find a configurable enum32 choice by ID.
 *
 * @param	choices		The enum32 choices.
 * @param	count		The number of choices.
 * @param	id		The choice ID.
 *
 * @return	The matching enum32 choice, or @{constant NULL} if not found.
 *
 * @since	1.0
 */
const stdif_configurable_enum32_t *
EXTIT_DECL
stdif_configurable_enum32_find_by_id
(
	const stdif_configurable_enum32_t *choices,
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
