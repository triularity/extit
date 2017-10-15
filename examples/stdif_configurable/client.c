/*
 * @(#) stdif_configurable/client.c
 *
 * This file is in the Public Domain.
 */

#include <stdlib.h>

#include <iv/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_util.h>

#include "scan_service.h"


int
main(int argc, char **argv)
{
	scan_service_t *		service;
	stdif_configurable_t *		conf;
	stdif_configurable_propref_t *	prop;


	service = scan_service_create();
	conf = scan_service_get_configurable(service);

	prop = stdif_configurable_find_property(conf, "mode");
	stdif_configurable_set_enum32(conf, prop, SCAN_MODE_GRAY);

	prop = stdif_configurable_find_property(conf, "start_x");
	stdif_configurable_set_uint32(conf, prop, 500);

	prop = stdif_configurable_find_property(conf, "start_y");
	stdif_configurable_set_uint32(conf, prop, 300);

	prop = stdif_configurable_find_property(conf, "width");
	stdif_configurable_set_uint32(conf, prop, 900);

	prop = stdif_configurable_find_property(conf, "height");
	stdif_configurable_set_uint32(conf, prop, 900);

	/* invoke scan ... */

	return 0;
}
