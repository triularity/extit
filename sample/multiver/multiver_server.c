/*
 * @(#) multiver_server.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <iv/base.h>
#include <iv/repository.h>
#include <extit/base.h>
#include <extit/container.h>

#include "persistence.h"
#include "persistence_impl.h"


static
void *
EXTIT_DECL
my_get_interface(const extit_container_t *container, const char *name, iv_version_t version)
{
	return iv_repository_get(
		(iv_repository_t *) container->_priv, name, version);
}


static
iv_version_t
EXTIT_DECL
my_query_interface(const extit_container_t *container, const char *name, iv_version_t base_version)
{
	return iv_repository_query(
		(iv_repository_t *) container->_priv, name, base_version);
}


static extit_container_t my_container_template =
{
	EXTIT_API_VERSION_1_0,
	NULL,
	extit_container_get_symbol_default,
	extit_container_get_function_default,
	my_get_interface,
	my_query_interface,
	extit_container_log_default
};


int
main(int argc, char **argv)
{
	iv_repository_t *	ir;
	extit_container_t	container;
	extit_module_t *	module;
	extit_plugin_t *	plugin;


	if(argc != 2)
	{
		fprintf(stderr, "Usage: multiver_server <plugin-path>\n");
		return 1;
	}

	if((ir = iv_repository_create()) == NULL)
	{
		fprintf(stderr, "Unable to create interface repository\n");
		return 2;
	}

	iv_repository_setFlags(ir, EXTIT_FLAG_LOG_DEBUG);

	if(iv_repository_set(ir, PERSISTENCE_INTERFACE_NAME,
	 PERSISTENCE_INTERFACE_TARGET, &persistence_interface, NULL)
	 != EXTIT_STATUS_OK)
	{
		fprintf(stderr, "Unable to register interface %s@%u.%u\n",
			PERSISTENCE_INTERFACE_NAME,
			IV_VERSION_MAJOR(PERSISTENCE_INTERFACE_TARGET),
			IV_VERSION_MINOR(PERSISTENCE_INTERFACE_TARGET));

		return 2;
	}

	container = my_container_template;
	container._priv = ir;

	module = extit_module_load(&container, argv[1], EXTIT_FLAG_LOG_TRACE);

	if(module != NULL)
	{
		fprintf(stderr,
			"*** Module ID: %s\n",
			extit_module_getId(module));

		fprintf(stderr,
			"*** Module ID Version: 0x%08x\n",
			extit_module_getIdVersion(module));

		fprintf(stderr,
			"*** Module Name: %s\n",
			extit_module_getName(module));

		fprintf(stderr,
			"*** Module Version: %s\n",
			extit_module_getVersion(module));

		plugin = extit_module_createPlugin(module);

		if(plugin != NULL)
		{
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

	iv_repository_destroy(ir);

	return 0;
}

