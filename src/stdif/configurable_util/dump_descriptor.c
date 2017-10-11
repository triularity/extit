/*
 * @(#) stdif/configurable_util/dump_descriptor.c
 *
 * Dump a configurable interface property descriptor.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include <stdif/configurable.h>
#include <stdif/configurable_util.h>


void
EXTIT_DECL
_stdif_configurable_dump_descriptor
(
	FILE *fp,
	unsigned int indent,
	const stdif_configurable_descriptor_t *descr
)
{
	uint32_t	i;


	if(descr->id != NULL)
	{
		fputc('[', fp);
		fputs(descr->id, fp);
		fputs("]\n", fp);
	}

	for(i = 0; i < descr->count; i++)
	{
		_stdif_configurable_dump_propdef(
			fp, indent, descr->properties[i]);
	}
}
