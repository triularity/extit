/*
 * @(#) if_configurable/client.c
 *
 * This file is in the Public Domain.
 */

#include <stdlib.h>

#include <iv/base.h>
#include <if/configurable.h>
#include <if/configurable_util.h>

#include "scan_service.h"


int
main(int argc, char **argv)
{
	scan_service_t *		service;
	if_configurable_t *		conf;
	if_configurable_propref_t *	prop;


	service = scan_service_create();
	conf = scan_service_get_configurable(service);

	prop = if_configurable_find_property(conf, "mode");
	if_configurable_set_enum32(conf, prop, SCAN_MODE_GRAY);

	prop = if_configurable_find_property(conf, "start_x");
	if_configurable_set_uint32(conf, prop, 500);

	prop = if_configurable_find_property(conf, "start_y");
	if_configurable_set_uint32(conf, prop, 300);

	prop = if_configurable_find_property(conf, "width");
	if_configurable_set_uint32(conf, prop, 900);

	prop = if_configurable_find_property(conf, "height");
	if_configurable_set_uint32(conf, prop, 900);

	/* invoke scan ... */

	return 0;
}
