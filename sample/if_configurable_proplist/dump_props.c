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


typedef struct _conf_data
{
	if_configurable_stdimpl_1_0_t	configurable;
	uint32_t			color;
	double				height;
	double				width;
	double				depth;
	void				(*onclick)(void);
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
		"The color Blue\xe2\x84\xa2",
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
		"Not blue\nNot green\nNot grey",
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
		"Like a piano key, \xf0\x9d\x85\x9f\xf0\x9d\x85\x9f\xf0\x9d\x85\x9f",
		0x000000
	},
	{
		"white",
		"White",
		"Like a piano key, \xf0\x9d\x85\x9e\xf0\x9d\x85\x9e\xf0\x9d\x85\x9e",
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
void
def_onlick(void)
{
	/* Do Nothing */
}


static
if_configurable_propref_t	conf_prop_onclick =
{
	{
		"onclick",
		"On-Click Callback",
		"Function to call when object is clicked",
		IF_CONFIGURABLE_TYPE_FUNCTION,

		.spec.type_function.iid = "notify-void",
		.spec.type_function.version = IV_VERSION(1, 0),
		.spec.type_function.def_value = (extit_func_t) &def_onlick
	},
	offsetof(conf_data_t, onclick)
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
	&conf_prop_depth.definition,
	&conf_prop_onclick.definition
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


int
main(int argc, char **argv)
{
	if_configurable_t *	conf;


	conf = get_configurable();

	_if_configurable_dump_descriptor(
		stdout, 0, if_configurable_get_descriptor(conf));

	return 0;
}
