/*
 * @(#) if/configurable_util/dump_enum32.c
 *
 * Dump a configurable interface enum32 descriptor.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <iv/base.h>

#include <if/configurable.h>
#include <if/configurable_util.h>


static
void		findent(FILE *fp, unsigned int indent);


static
void
findent
(
	FILE *fp,
	unsigned int indent
)
{
	while(indent-- != 0)
		fputc(' ', fp);
}


void
EXTIT_DECL
_if_configurable_dump_enum32
(
	FILE *fp,
	unsigned int indent,
	const if_configurable_enum32_t *enum32
)
{
	findent(fp, indent);
	fputs(enum32->id, fp);
	fputc('\n', fp);

	findent(fp, indent);
	fputs("    Name: ", fp);
	fputs(enum32->name, fp);
	fputc('\n', fp);

	if(enum32->description != NULL)
	{
		findent(fp, indent);
		fputs("    Description: ", fp);

		_if_configurable_fprint_utf8(
			fp, enum32->description, EXTIT_TRUE);

		fputc('\n', fp);
	}

	findent(fp, indent);
	fprintf(fp, "    Value: %" PRIu32 "\n", enum32->value);
}
