/*
 * @(#) recipe_server.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/container.h>
#include <extit/container_impl.h>
#include <extit/container_stdimpl.h>
#include <extit/pmodule.h>
#include <extit/platform.h>

#include "recipe.h"


typedef struct _module_list	module_link_t;

struct _module_list
{
	extit_module_t *	module;
	module_link_t *		next;
};


bool
EXTIT_DECL
recipe_fnfilter(const char *basename, size_t length, void *client_data);

extit_status_t
EXTIT_DECL
process_module_load(extit_module_t *module, void *client_data);

void
prepare_recipe(extit_module_t *module);


int
main(int argc, char **argv)
{
	extit_container_1_0_t	my_container;
	module_link_t *		modules;
	module_link_t *		link;
	extit_status_t		status;


	if(argc != 2)
	{
		fprintf(stderr, "Usage: recipe_server <plugins-directory>\n");
		return 1;
	}

	modules = NULL;

	my_container.version = EXTIT_ABI_1_0;
	my_container.ops = &extit_container_stdimpl_ops_1_0;

	status = extit_module_scan(
			(extit_container_t *) &my_container,
			argv[1],
			process_module_load,
			&modules,
			recipe_fnfilter,
			NULL,
			EXTIT_FLAG_LOG_TRACE);

	if(status != EXTIT_STATUS_OK)
	{
		fprintf(stderr, "Scan failed, status = #%u\n", status);
		return 2;
	}


	/*
	 * Prepare all recipes
	 */
	link = modules;

	while(link != NULL)
	{
		prepare_recipe(link->module);
		link = link->next;
	}


	/*
	 * Free the modules
	 */
	link = modules;

	while(link != NULL)
	{
		extit_module_release(link->module);
		link = link->next;

		/*
		 * XXX - module_link_t is leaked, but skiping the free since
		 * we are about to exit anyway
		 */
	}

	return 0;
}


bool
EXTIT_DECL
recipe_fnfilter
(
	const char *basename,
	size_t length,
	void *client_data
)
{
	if(!extit_module_scan_fnfilter_default(basename, length, NULL))
		return 0;

	/*
	 * Must have a "recipe-" prefix
	 */
	if(length < 8)
		return 0;

	return (EXTIT_FN_STRNCMP(basename, "recipe-", 7) == 0);
}


extit_status_t
EXTIT_DECL
process_module_load(extit_module_t *module, void *client_data)
{
	module_link_t *		link;
	module_link_t **	link_p;


	if((link = malloc(sizeof(module_link_t))) == NULL)
		return EXTIT_STATUS_NOMEM;

	link_p = (module_link_t **) client_data;

	link->module = module;
	link->next = *link_p;
	*link_p = link;

	return EXTIT_STATUS_OK;
}


void
prepare_recipe(extit_module_t *module)
{
	extit_plugin_t *	plugin;
	recipe_t *		recipe;


	plugin = extit_module_create_plugin(module);

	if(plugin == NULL)
	{
		fprintf(stderr, "Unable to create plugin\n");
		return;
	}

	recipe = (recipe_t *) extit_plugin_get_interface(
		plugin, RECIPE_INTERFACE_ID, RECIPE_INTERFACE_VERSION);

	if(recipe != NULL)
	{
		recipe->prepare(recipe);
	}
	else
	{
		fprintf(stderr,
		"Unable to find plugin interface %s:%u.%u in module %s (%s)\n",
			RECIPE_INTERFACE_ID,
			IV_VERSION_MAJOR(RECIPE_INTERFACE_VERSION),
			IV_VERSION_MINOR(RECIPE_INTERFACE_VERSION),
			extit_module_get_name(module),
			extit_module_get_version(module));
	}

	extit_plugin_destroy(plugin);
}

