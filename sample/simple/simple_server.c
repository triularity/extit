/*
 * @(#) simple_server.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <iv/base.h>
#include <extit/container.h>


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
	EXTIT_ABI_VERSION_1_0,				/* version */
	&my_container_ops				/* ops */
};


int
main(int argc, char **argv)
{
	extit_module_t *	module;
	extit_plugin_t *	plugin;


	if(argc != 2)
	{
		fprintf(stderr, "Usage: simple_server <plugin-path>\n");
		return 1;
	}

	module = extit_module_load(
			&my_container,
			argv[1],
			EXTIT_FLAG_LOG_TRACE);

	if(module != NULL)
	{
		fprintf(stderr,
			"*** Module ABI: %u.%u\n",
			IV_VERSION_MAJOR(extit_module_get_abi_version(module)),
			IV_VERSION_MINOR(extit_module_get_abi_version(module)));

		fprintf(stderr,
			"*** Module Effective ABI: %u.%u\n",
			IV_VERSION_MAJOR(
				extit_module_get_effective_abi_version(
					module)),
			IV_VERSION_MINOR(
				extit_module_get_effective_abi_version(
					module)));

		fprintf(stderr,
			"*** Module ID: %s\n",
			extit_module_get_id(module));

		fprintf(stderr,
			"*** Module ID Version: 0x%08x\n",
			extit_module_get_id_version(module));

		fprintf(stderr,
			"*** Module Name: %s\n",
			extit_module_get_name(module));

		fprintf(stderr,
			"*** Module Version: %s\n",
			extit_module_get_version(module));

		plugin = extit_module_create_plugin(module);

		if(plugin != NULL)
		{
			if(extit_plugin_activate(plugin) == EXTIT_STATUS_OK)
			{
				/* Do something with the plugin */

				extit_plugin_ping(plugin);


				/* I guess we are done */

				extit_plugin_deactivate(plugin);
			}
			else
			{
				fprintf(stderr, "Unable to activate plugin\n");
			}

			extit_plugin_destroy(plugin);
		}
		else
		{
			fprintf(stderr, "Unable to create plugin\n");
		}

		extit_module_release(module);
	}
	else
	{
		fprintf(stderr, "Unable to load module\n");
	}

	return 0;
}

