/*
 * @(#) simple_server.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <iv/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>
#include <extit/container_stdimpl.h>
#include <extit/pmodule.h>


int
main(int argc, char **argv)
{
	extit_container_t	my_container;
	extit_module_t *	module;
	extit_plugin_t *	plugin;


	if(argc != 2)
	{
		fprintf(stderr, "Usage: simple_server <plugin-path>\n");
		return 1;
	}

	my_container.version = EXTIT_ABI_VERSION_1_0;
	my_container.ops = &extit_container_stdimpl_ops_1_0;

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
			/* Do something with the plugin... */

			/* I guess we are done */
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

