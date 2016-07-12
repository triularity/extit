/*
 * @(#) if_configurable/client.c
 *
 * This file is in the Public Domain.
 */

#include <stdlib.h>

#include <iv/base.h>
#include <extit/if/configurable.h>
#include <extit/if/configurable_util.h>

#include "scan_service.h"


int
main(int argc, char **argv)
{
	scan_service_t *			service;
	extit_if_configurable_t *		conf;
	extit_if_configurable_propref_t *	prop;


	service = scan_service_create();
	conf = scan_service_get_configurable(service);

	prop = extit_if_configurable_find_property(conf, "mode");
	extit_if_configurable_set_enum32(conf, prop, SCAN_MODE_GRAY);

	prop = extit_if_configurable_find_property(conf, "start_x");
	extit_if_configurable_set_uint32(conf, prop, 500);

	prop = extit_if_configurable_find_property(conf, "start_y");
	extit_if_configurable_set_uint32(conf, prop, 300);

	prop = extit_if_configurable_find_property(conf, "width");
	extit_if_configurable_set_uint32(conf, prop, 900);

	prop = extit_if_configurable_find_property(conf, "height");
	extit_if_configurable_set_uint32(conf, prop, 900);

	/* invoke scan ... */

	return 0;
}
