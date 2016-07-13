/*
 * @(#) if_configurable/scan_service.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <iv/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>
#include <if/configurable_stdimpl.h>
#include <if/configurable_util.h>

#include "scan_service.h"


typedef struct _scan_service_settings
{
	scan_mode_t	mode;
	uint32_t	start_x;
	uint32_t	start_y;
	uint32_t	width;
	uint32_t	height;
} scan_service_settings_t;


struct _scan_service
{
	if_configurable_t		configurable;
	scan_service_settings_t		settings;
};


static
if_configurable_enum32_t	conf_prop_mode_choices[3] =
{
	{
		"bw",
		"B&W",
		NULL,
		SCAN_MODE_BW
	},
	{
		"gray",
		"Gray",
		NULL,
		SCAN_MODE_GRAY
	},
	{
		"color",
		"Color",
		NULL,
		SCAN_MODE_COLOR
	}
};


static
void
conf_mode_notifier(if_configurable_t *conf, if_configurable_propref_t *prop);


static
if_configurable_propref_t	conf_prop_mode =
{
	{
		"mode",
		"Mode",
		"The format to scan in",
		IF_CONFIGURABLE_TYPE_ENUM32,

		.spec.type_enum32.choices = conf_prop_mode_choices,
		.spec.type_enum32.choice_count = 3,
		.spec.type_enum32.def_value = SCAN_MODE_COLOR
	},
	offsetof(scan_service_t, settings)
		+ offsetof(scan_service_settings_t, mode),
	conf_mode_notifier
};


static
if_configurable_propref_t	conf_prop_x =
{
	{
		"start_x",
		"Starting column",
		"The left starting position of the scan",
		IF_CONFIGURABLE_TYPE_UINT32,

		.spec.type_uint32.min_value = 0,
		.spec.type_uint32.max_value = (8 * 300) - 1,
		.spec.type_uint32.def_value = 0
	},
	offsetof(scan_service_t, settings)
		+ offsetof(scan_service_settings_t, start_x),
	NULL
};


static
if_configurable_propref_t	conf_prop_y =
{
	{
		"start_y",
		"Starting row",
		"The top starting position of the scan",
		IF_CONFIGURABLE_TYPE_UINT32,

		.spec.type_uint32.min_value = 0,
		.spec.type_uint32.max_value = (14 * 300) - 1,
		.spec.type_uint32.def_value = 0
	},
	offsetof(scan_service_t, settings)
		+ offsetof(scan_service_settings_t, start_y),
	NULL
};


static
if_configurable_propref_t	conf_prop_width =
{
	{
		"width",
		"Scan width",
		"The width of the scan area",
		IF_CONFIGURABLE_TYPE_UINT32,

		.spec.type_uint32.min_value = 1,
		.spec.type_uint32.max_value = 8 * 300,
		.spec.type_uint32.def_value = 8 * 300
	},
	offsetof(scan_service_t, settings)
		+ offsetof(scan_service_settings_t, width),
	NULL
};


static
if_configurable_propref_t	conf_prop_height =
{
	{
		"height",
		"Scan height",
		"The height of the scan area",
		IF_CONFIGURABLE_TYPE_UINT32,

		.spec.type_uint32.min_value = 1,
		.spec.type_uint32.max_value = 14 * 300,
		.spec.type_uint32.def_value = 14 * 300
	},
	offsetof(scan_service_t, settings)
		+ offsetof(scan_service_settings_t, height),
	NULL
};


static
const
if_configurable_propdef_t *	conf_props[5] =
{
	&conf_prop_mode.definition,
	&conf_prop_x.definition,
	&conf_prop_y.definition,
	&conf_prop_width.definition,
	&conf_prop_height.definition
};


static
if_configurable_descriptor_t	conf_descriptor =
{
	conf_props,
	5
};


static
void
conf_mode_notifier
(
	if_configurable_t *conf,
	if_configurable_propref_t *prop
)
{
	scan_service_t *			service;
	const if_configurable_enum32_t *	enum32;


	service = (scan_service_t *) conf;

	enum32 = if_configurable_enum32_find_by_value(
		prop->definition.spec.type_enum32.choices,
		prop->definition.spec.type_enum32.choice_count,
		service->settings.mode);

	if(enum32 != NULL)
	{
		printf("Reallocation resources for mode %s...\n",
			enum32->name);
	}
}


scan_service_t *
scan_service_create(void)
{
	scan_service_t *	service;


	/* XXX - Do NULL check in real thing! */
	service = malloc(sizeof(scan_service_t));

	service->configurable.version = IF_CONFIGURABLE_ABI_TARGET;
	service->configurable.ops = &if_configurable_stdimpl_ops;
	service->configurable.descriptor = &conf_descriptor;

	service->settings.mode = SCAN_MODE_COLOR;
	service->settings.start_x = 0;
	service->settings.start_y = 0;
	service->settings.width = 8 * 300;
	service->settings.height = 10 * 300;

	return service;
}


if_configurable_t *
scan_service_get_configurable(scan_service_t *service)
{
	return &service->configurable;
}

