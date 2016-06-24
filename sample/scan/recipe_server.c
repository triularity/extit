/*
 * @(#) recipe_server.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/container.h>
#include <extit/platform.h>

#include "recipe.h"


typedef struct _module_list	module_link_t;

struct _module_list
{
	extit_module_t *	module;
	module_link_t *		next;
};


static
extit_container_ops_1_0_t	my_container_ops =
{
	extit_container_get_symbol_default,		/* get_symbol */
	extit_container_get_function_default,		/* get_function */
	extit_container_get_interface_default,		/* get_interface */
	extit_container_query_interface_default,	/* query_interface */
	extit_container_log_default			/* log */
};


static
extit_container_t		my_container =
{
	EXTIT_API_VERSION_1_0,				/* version */
	&my_container_ops,				/* ops */
	NULL,						/* _priv */
};


unsigned int
EXTIT_DECL
recipe_fnfilter(const char *basename, size_t length);

extit_status_t
EXTIT_DECL
process_module_load(extit_module_t *module, void *client_data);

void
prepare_recipe(extit_module_t *module);


int
main(int argc, char **argv)
{
	module_link_t *		modules;
	module_link_t *		link;
	extit_status_t		status;


	if(argc != 2)
	{
		fprintf(stderr, "Usage: recipe_server <plugins-directory>\n");
		return 1;
	}

	modules = NULL;

	status = extit_module_scan(
			&my_container,
			argv[1],
			process_module_load,
			&modules,
			recipe_fnfilter,
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


unsigned int
EXTIT_DECL
recipe_fnfilter
(
	const char *basename,
	size_t length
)
{
	if(!extit_module_scan_fnfilter_default(basename, length))
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


	plugin = extit_module_createPlugin(module);

	if(plugin == NULL)
	{
		fprintf(stderr, "Unable to create plugin\n");
		return;
	}

	recipe = (recipe_t *) extit_plugin_getInterface(
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
			extit_module_getName(module),
			extit_module_getVersion(module));
	}

	extit_plugin_destroy(plugin);
}

