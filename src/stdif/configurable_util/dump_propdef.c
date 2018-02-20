/*
 * @(#) stdif/configurable_util/dump_propdef.c
 *
 * Dump a configurable interface property definition.
 *
 * Copyright (c) 2017-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#include <iv/base.h>
#include <extit/platform.h>

#include <stdif/configurable.h>
#include <stdif/configurable_util.h>


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


/**
 * Dump a configurable property definition in human readable form.
 *
 * @note	This is a utility function and not part of the
 *		standard configurable API. Use with caution.
 *
 * @param	fp		The file pointer to write to.
 * @param	indent		The number of spaces to indent.
 * @param	propdef		The property definition.
 *
 * @since	1.0
 */
void
EXTIT_DECL
_stdif_configurable_dump_propdef
(
	FILE *fp,
	unsigned int indent,
	const stdif_configurable_propdef_t *propdef
)
{
	const stdif_configurable_enum32_t *		enum32;
	const stdif_configurable_propspec_enum32_t *	spec_enum32;
	uint32_t					i;
	unsigned int 					next_indent;
	const char *					type_str;


	findent(fp, indent);
	fputs(propdef->id, fp);
	fputc('\n', fp);

	if((type_str = stdif_configurable_type_to_string(propdef->type))
	 != NULL)
	{
		findent(fp, indent);
		fputs("    Type: STDIF_CONFIGURABLE_TYPE_", fp);
		fputs(type_str, fp);
		fputc('\n', fp);
	}
	else
	{
		findent(fp, indent);
		fputs("    Type: ** Unknown **\n", fp);
	}

	findent(fp, indent);
	fputs("    Name: ", fp);
	_stdif_configurable_fprint_utf8(fp, propdef->name, true);
	fputc('\n', fp);

	if(propdef->description != NULL)
	{
		findent(fp, indent);
		fputs("    Description: ", fp);

		_stdif_configurable_fprint_utf8(
			fp, propdef->description, true);

		fputc('\n', fp);
	}

	switch(propdef->type)
	{
		case STDIF_CONFIGURABLE_TYPE_BOOL:
			findent(fp, indent);
			fputs("    Default: ", fp);

			if(propdef->spec.type_bool.def_value)
				fputs("true\n", fp);
			else
				fputs("false\n", fp);

			break;

		case STDIF_CONFIGURABLE_TYPE_DATA:
			findent(fp, indent);
			fprintf(fp, "    Default: 0x%0*" PRIxPTR "\n",
				(int) sizeof(uintptr_t) * 2,
				(uintptr_t) propdef->spec.type_data.def_value);

			findent(fp, indent);
			fprintf(fp, "    Interface: %s@%u.%u\n",
				propdef->spec.type_data.iid,
				IV_VERSION_MAJOR(
					propdef->spec.type_data.version),
				IV_VERSION_MINOR(
					propdef->spec.type_data.version));

			break;

		case STDIF_CONFIGURABLE_TYPE_DOUBLE:
			findent(fp, indent);
			fprintf(fp, "    Default: %f\n",
				propdef->spec.type_double.def_value);

			findent(fp, indent);
			fprintf(fp, "    Minimum: %f\n",
				propdef->spec.type_double.min_value);

			findent(fp, indent);
			fprintf(fp, "    Maximum: %f\n",
				propdef->spec.type_double.max_value);

			if(propdef->spec.type_double.step_hint != 0.0)
			{
				findent(fp, indent);
				fprintf(fp, "    Step: %f\n",
					propdef->spec.type_double.step_hint);
			}

			break;

		case STDIF_CONFIGURABLE_TYPE_ENUM32:
			spec_enum32 = &propdef->spec.type_enum32;

			enum32 = stdif_configurable_enum32_find_by_value(
				spec_enum32->choices,
				spec_enum32->choice_count,
				spec_enum32->def_value);

			if(enum32 != NULL)
			{
				findent(fp, indent);
				fputs("    Default: ", fp);
				fputs(enum32->id, fp);
				fputc('\n', fp);
			}
			else
			{
				findent(fp, indent);
				fprintf(fp,
					"    Default: %" PRIu32
						" (unmapped)\n",
					spec_enum32->def_value);
			}

			findent(fp, indent);
			fputs("    Choices:\n", fp);

			next_indent = indent + 8;

			for(i = 0; i < spec_enum32->choice_count; i++)
			{
				_stdif_configurable_dump_enum32(
					fp,
					next_indent,
					&spec_enum32->choices[i]);
			}

			break;

		case STDIF_CONFIGURABLE_TYPE_FLOAT:
			findent(fp, indent);
			fprintf(fp, "    Default: %f\n",
				propdef->spec.type_float.def_value);

			findent(fp, indent);
			fprintf(fp, "    Minimum: %f\n",
				propdef->spec.type_float.min_value);

			findent(fp, indent);
			fprintf(fp, "    Maximum: %f\n",
				propdef->spec.type_float.max_value);

			if(propdef->spec.type_float.step_hint != 0.0f)
			{
				findent(fp, indent);
				fprintf(fp, "    Step: %f\n",
					propdef->spec.type_float.step_hint);
			}

			break;

		case STDIF_CONFIGURABLE_TYPE_FUNCTION:
			findent(fp, indent);
			fprintf(fp, "    Default: 0x%0*" PRIxPTR "\n",
				(int) sizeof(extit_func_t) * 2,
				(uintptr_t)
				 propdef->spec.type_function.def_value);

			findent(fp, indent);
			fprintf(fp, "    Interface: %s@%u.%u\n",
				propdef->spec.type_function.iid,
				IV_VERSION_MAJOR(
					propdef->spec.type_function.version),
				IV_VERSION_MINOR(
					propdef->spec.type_function.version));

			break;

		case STDIF_CONFIGURABLE_TYPE_INT8:
			findent(fp, indent);
			fprintf(fp, "    Default: %d\n",
				propdef->spec.type_int8.def_value);

			findent(fp, indent);
			fprintf(fp, "    Minimum: %d\n",
				propdef->spec.type_int8.min_value);

			findent(fp, indent);
			fprintf(fp, "    Maximum: %d\n",
				propdef->spec.type_int8.max_value);

			break;

		case STDIF_CONFIGURABLE_TYPE_INT16:
			findent(fp, indent);
			fprintf(fp, "    Default: %d\n",
				propdef->spec.type_int16.def_value);

			findent(fp, indent);
			fprintf(fp, "    Minimum: %d\n",
				propdef->spec.type_int16.min_value);

			findent(fp, indent);
			fprintf(fp, "    Maximum: %d\n",
				propdef->spec.type_int16.max_value);

			break;

		case STDIF_CONFIGURABLE_TYPE_INT32:
			findent(fp, indent);
			fprintf(fp, "    Default: %" PRId32 "\n",
				propdef->spec.type_int32.def_value);

			findent(fp, indent);
			fprintf(fp, "    Minimum: %" PRId32 "\n",
				propdef->spec.type_int32.min_value);

			findent(fp, indent);
			fprintf(fp, "    Maximum: %" PRId32 "\n",
				propdef->spec.type_int32.max_value);

			break;

		case STDIF_CONFIGURABLE_TYPE_INT64:
			findent(fp, indent);
			fprintf(fp, "    Default: %" PRId64 "\n",
				propdef->spec.type_int64.def_value);

			findent(fp, indent);
			fprintf(fp, "    Minimum: %" PRId64 "\n",
				propdef->spec.type_int64.min_value);

			findent(fp, indent);
			fprintf(fp, "    Maximum: %" PRId64 "\n",
				propdef->spec.type_int64.max_value);

			break;

		case STDIF_CONFIGURABLE_TYPE_UINT8:
			findent(fp, indent);
			fprintf(fp, "    Default: %u\n",
				propdef->spec.type_uint8.def_value);

			findent(fp, indent);
			fprintf(fp, "    Minimum: %u\n",
				propdef->spec.type_uint8.min_value);

			findent(fp, indent);
			fprintf(fp, "    Maximum: %u\n",
				propdef->spec.type_uint8.max_value);

			break;

		case STDIF_CONFIGURABLE_TYPE_UINT16:
			findent(fp, indent);
			fprintf(fp, "    Default: %u\n",
				propdef->spec.type_uint16.def_value);

			findent(fp, indent);
			fprintf(fp, "    Minimum: %u\n",
				propdef->spec.type_uint16.min_value);

			findent(fp, indent);
			fprintf(fp, "    Maximum: %u\n",
				propdef->spec.type_uint16.max_value);

			break;

		case STDIF_CONFIGURABLE_TYPE_UINT32:
			findent(fp, indent);
			fprintf(fp, "    Default: %" PRIu32 "\n",
				propdef->spec.type_uint32.def_value);

			findent(fp, indent);
			fprintf(fp, "    Minimum: %" PRIu32 "\n",
				propdef->spec.type_uint32.min_value);

			findent(fp, indent);
			fprintf(fp, "    Maximum: %" PRIu32 "\n",
				propdef->spec.type_uint32.max_value);

			break;

		case STDIF_CONFIGURABLE_TYPE_UINT64:
			findent(fp, indent);
			fprintf(fp, "    Default: %" PRIu64 "\n",
				propdef->spec.type_uint64.def_value);

			findent(fp, indent);
			fprintf(fp, "    Minimum: %" PRIu64 "\n",
				propdef->spec.type_uint64.min_value);

			findent(fp, indent);
			fprintf(fp, "    Maximum: %" PRIu64 "\n",
				propdef->spec.type_uint64.max_value);

			break;

		case STDIF_CONFIGURABLE_TYPE_UTF8:
			findent(fp, indent);
			fputs("    Default: ", fp);

			if(propdef->spec.type_utf8.def_value != NULL)
			{
				_stdif_configurable_fprint_utf8(
					fp,
					propdef->spec.type_utf8.def_value,
					true);
			}
			else
			{
				fputs("NULL", fp);
			}

			fputc('\n', fp);
			break;
	}
}
