/*
 * @(#) if_configurable_proplist/dump_props.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <iv/base.h>
#include <extit/platform.h>

#define	IF_CONFIGURABLE_ABI_TARGET	IF_CONFIGURABLE_ABI_1_0

#include <if/configurable.h>
#include <if/configurable_stdimpl.h>
#include <if/configurable_util.h>


static
if_configurable_t *	get_configurable(void);

static
void			dump_prop(const if_configurable_propdef_t *);

static
void			dump_enum32_choice(const if_configurable_enum32_t *);


typedef struct _conf_data
{
	if_configurable_stdimpl_1_0_t	configurable;
	uint32_t			color;
	double				height;
	double				width;
	double				depth;
} conf_data_t;


static
if_configurable_enum32_t	conf_prop_color_choices[] =
{
	{
		"red",
		"Red",
		NULL,
		0xFF0000
	},
	{
		"green",
		"Green",
		NULL,
		0x00FF00
	},
	{
		"blue",
		"Blue",
		NULL,
		0x0000FF
	},
	{
		"yellow",
		"Yellow",
		NULL,
		0xFFFF00
	},
	{
		"orange",
		"Orange",
		NULL,
		0xFF8000
	},
	{
		"purple",
		"Purple",
		NULL,
		0xFF00FF
	},
	{
		"black",
		"Black",
		NULL,
		0x000000
	},
	{
		"white",
		"White",
		NULL,
		0xFFFFFF
	},
	{
		"gray",
		"Gray",
		NULL,
		0x808080
	}
};


static
if_configurable_propref_t	conf_prop_color =
{
	{
		"color",
		"Color",
		"The color of the object",
		IF_CONFIGURABLE_TYPE_ENUM32,

		.spec.type_enum32.choices = conf_prop_color_choices,
		.spec.type_enum32.choice_count =
			sizeof(conf_prop_color_choices)
				/ sizeof(conf_prop_color_choices[0]),
		.spec.type_enum32.def_value = 0x808080
	},
	offsetof(conf_data_t, color)
		- (offsetof(conf_data_t, configurable)
			+ offsetof(if_configurable_stdimpl_1_0_t, pub)),
	NULL
};


static
if_configurable_propref_t	conf_prop_height =
{
	{
		"height",
		"Height",
		"The height of the object",
		IF_CONFIGURABLE_TYPE_DOUBLE,

		.spec.type_double.min_value = 0.0,
		.spec.type_double.max_value = 1000.0,
		.spec.type_double.def_value = 1.0
	},
	offsetof(conf_data_t, height)
		- (offsetof(conf_data_t, configurable)
			+ offsetof(if_configurable_stdimpl_1_0_t, pub)),
	NULL
};


static
if_configurable_propref_t	conf_prop_width =
{
	{
		"width",
		"Width",
		"The width of the object",
		IF_CONFIGURABLE_TYPE_DOUBLE,

		.spec.type_double.min_value = 0.0,
		.spec.type_double.max_value = 1000.0,
		.spec.type_double.def_value = 1.0
	},
	offsetof(conf_data_t, width)
		- (offsetof(conf_data_t, configurable)
			+ offsetof(if_configurable_stdimpl_1_0_t, pub)),
	NULL
};


static
if_configurable_propref_t	conf_prop_depth =
{
	{
		"depth",
		"Depth",
		"The depth of the object",
		IF_CONFIGURABLE_TYPE_DOUBLE,

		.spec.type_double.min_value = 0.0,
		.spec.type_double.max_value = 1000.0,
		.spec.type_double.def_value = 1.0
	},
	offsetof(conf_data_t, depth)
		- (offsetof(conf_data_t, configurable)
			+ offsetof(if_configurable_stdimpl_1_0_t, pub)),
	NULL
};


static
const
if_configurable_propdef_t *	conf_props[] =
{
	&conf_prop_color.definition,
	&conf_prop_height.definition,
	&conf_prop_width.definition,
	&conf_prop_depth.definition
};


static
if_configurable_descriptor_t	conf_descriptor =
{
	conf_props,
	sizeof(conf_props) / sizeof(conf_props[0])
};


static
if_configurable_t *
get_configurable(void)
{
	conf_data_t *	data;


	/* XXX - Do NULL check in real thing! */
	data = malloc(sizeof(conf_data_t));

	data->configurable.pub.version = IF_CONFIGURABLE_ABI_TARGET;
	data->configurable.pub.ops = &if_configurable_stdimpl_ops_1_0;
	data->configurable.descriptor = &conf_descriptor;

	data->color = 0x808080;
	data->width = 1.0;
	data->height = 1.0;
	data->depth = 1.0;

	return (if_configurable_t *) &data->configurable.pub;
}


static
void
dump_enum32_choice(const if_configurable_enum32_t *enum32)
{
	printf("        %s\n", enum32->id);
	printf("            Name: %s\n", enum32->name);

	if(enum32->description != NULL)
		printf("        Description: %s\n", enum32->description);

	printf("            Value: %" PRIu32 "\n", enum32->value);
}


static
void
dump_prop(const if_configurable_propdef_t *propdef)
{
	const if_configurable_enum32_t *		enum32;
	const if_configurable_propspec_enum32_t *	spec_enum32;
	uint32_t					i;


	printf("%s\n", propdef->id);
	printf("    Name: %s\n", propdef->name);

	if(propdef->description != NULL)
		printf("    Description: %s\n", propdef->description);

	switch(propdef->type)
	{
		case IF_CONFIGURABLE_TYPE_BOOL:
			printf("    Type: BOOL\n");

			printf("    Default: %s\n",
				(propdef->spec.type_bool.def_value ?
					"EXTIT_TRUE" : "EXTIT_FALSE"));

			break;

		case IF_CONFIGURABLE_TYPE_DOUBLE:
			printf("    Type: DOUBLE\n");

			printf("    Default: %f\n",
				propdef->spec.type_double.def_value);

			printf("    Minimum: %f\n",
				propdef->spec.type_double.min_value);

			printf("    Maximum: %f\n",
				propdef->spec.type_double.max_value);

			if(propdef->spec.type_double.step_hint != 0.0)
			{
				printf("    Step: %f\n",
					propdef->spec.type_double.step_hint);
			}

			break;

		case IF_CONFIGURABLE_TYPE_ENUM32:
			printf("    Type: ENUM32\n");

			spec_enum32 = &propdef->spec.type_enum32;

			enum32 = if_configurable_enum32_find_by_value(
				spec_enum32->choices,
				spec_enum32->choice_count,
				spec_enum32->def_value);

			if(enum32 != NULL)
			{
				printf("    Default: %s\n", enum32->id);
			}
			else
			{
				printf("    Default: %" PRIu32 "  (unmapped)\n",
					spec_enum32->def_value);
			}

			printf("    Choices:\n");

			for(i = 0; i < spec_enum32->choice_count; i++)
			{
				dump_enum32_choice(&spec_enum32->choices[i]);
//-				printf("\n");
			}

			break;

		case IF_CONFIGURABLE_TYPE_FLOAT:
			printf("    Type: FLOAT\n");

			printf("    Default: %f\n",
				propdef->spec.type_float.def_value);

			printf("    Minimum: %f\n",
				propdef->spec.type_float.min_value);

			printf("    Maximum: %f\n",
				propdef->spec.type_float.max_value);

			if(propdef->spec.type_float.step_hint != 0.0f)
			{
				printf("    Step: %f\n",
					propdef->spec.type_float.step_hint);
			}

			break;

		case IF_CONFIGURABLE_TYPE_INT8:
			printf("    Type: INT8\n");

			printf("    Default: %d\n",
				propdef->spec.type_int8.def_value);

			printf("    Minimum: %d\n",
				propdef->spec.type_int8.min_value);

			printf("    Maximum: %d\n",
				propdef->spec.type_int8.max_value);

			break;

		case IF_CONFIGURABLE_TYPE_INT16:
			printf("    Type: INT16\n");

			printf("    Default: %d\n",
				propdef->spec.type_int16.def_value);

			printf("    Minimum: %d\n",
				propdef->spec.type_int16.min_value);

			printf("    Maximum: %d\n",
				propdef->spec.type_int16.max_value);

			break;

		case IF_CONFIGURABLE_TYPE_INT32:
			printf("    Type: INT32\n");

			printf("    Default: %" PRId32 "\n",
				propdef->spec.type_int32.def_value);

			printf("    Minimum: %" PRId32 "\n",
				propdef->spec.type_int32.min_value);

			printf("    Maximum: %" PRId32 "\n",
				propdef->spec.type_int32.max_value);

			break;

		case IF_CONFIGURABLE_TYPE_INT64:
			printf("    Type: INT64\n");

#ifndef	BROKEN_PRINTF_64BIT
			printf("    Default: %" PRId64 "\n",
				propdef->spec.type_int64.def_value);

			printf("    Minimum: %" PRId64 "\n",
				propdef->spec.type_int64.min_value);

			printf("    Maximum: %" PRId64 "\n",
				propdef->spec.type_int64.max_value);
#endif	/* !BROKEN_PRINTF_64BIT */

			break;

		case IF_CONFIGURABLE_TYPE_UINT8:
			printf("    Type: UINT8\n");

			printf("    Default: %u\n",
				propdef->spec.type_uint8.def_value);

			printf("    Minimum: %u\n",
				propdef->spec.type_uint8.min_value);

			printf("    Maximum: %u\n",
				propdef->spec.type_uint8.max_value);

			break;

		case IF_CONFIGURABLE_TYPE_UINT16:
			printf("    Type: UINT16\n");

			printf("    Default: %u\n",
				propdef->spec.type_uint16.def_value);

			printf("    Minimum: %u\n",
				propdef->spec.type_uint16.min_value);

			printf("    Maximum: %u\n",
				propdef->spec.type_uint16.max_value);

			break;

		case IF_CONFIGURABLE_TYPE_UINT32:
			printf("    Type: UINT32\n");

			printf("    Default: %" PRIu32 "\n",
				propdef->spec.type_uint32.def_value);

			printf("    Minimum: %" PRIu32 "\n",
				propdef->spec.type_uint32.min_value);

			printf("    Maximum: %" PRIu32 "\n",
				propdef->spec.type_uint32.max_value);

			break;

		case IF_CONFIGURABLE_TYPE_UINT64:
			printf("    Type: UINT64\n");

#ifndef	BROKEN_PRINTF_64BIT
			printf("    Default: %" PRIu64 "\n",
				propdef->spec.type_uint64.def_value);

			printf("    Minimum: %" PRIu64 "\n",
				propdef->spec.type_uint64.min_value);

			printf("    Maximum: %" PRIu64 "\n",
				propdef->spec.type_uint64.max_value);
#endif	/* !BROKEN_PRINTF_64BIT */

			break;

		case IF_CONFIGURABLE_TYPE_UTF8:
			printf("    Type: UTF8\n");

			if(propdef->spec.type_utf8.def_value != NULL)
			{
				printf("    Default: [%s]\n",
					propdef->spec.type_utf8.def_value);
			}
			else
			{
				printf("    Default: NULL\n");
			}

			break;

		case IF_CONFIGURABLE_TYPE_DATA:
			printf("    Type: DATA\n");

			printf("    Default: 0x%p\n",
				propdef->spec.type_data.def_value);

			printf("    Interface: %s@%u.%u\n",
				propdef->spec.type_data.iid,
				IV_VERSION_MAJOR(
					propdef->spec.type_data.version),
				IV_VERSION_MINOR(
					propdef->spec.type_data.version));

			break;

		case IF_CONFIGURABLE_TYPE_FUNCTION:
			printf("    Type: FUNCTION\n");

			printf("    Default: 0x%p\n",
				FUNCPTR_TO_VOIDPTR(
				 propdef->spec.type_function.def_value));

			printf("    Interface: %s@%u.%u\n",
				propdef->spec.type_function.iid,
				IV_VERSION_MAJOR(
					propdef->spec.type_function.version),
				IV_VERSION_MINOR(
					propdef->spec.type_function.version));

			break;

		default:
			printf("    Type: *** Unknown ***\n");
			break;
	}
}


int
main(int argc, char **argv)
{
	if_configurable_t *			conf;
	const if_configurable_descriptor_t *	descr;
	uint32_t				i;


	conf = get_configurable();

	descr = if_configurable_get_descriptor(conf);

	for(i = 0; i < descr->count; i++)
	{
		dump_prop(descr->properties[i]);
//-		printf("\n");
	}

	return 0;
}
