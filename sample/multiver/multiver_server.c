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


typedef struct my_container_impl
{
	extit_container_t	container;
	iv_repository_t *	ir;
} my_container_impl_t;


static
void *
EXTIT_DECL
my_get_interface(const extit_container_t *container, const char *name, iv_version_t version)
{
	return iv_repository_get(
		((const my_container_impl_t *) container)->ir,
		name, version);
}


static
iv_version_t
EXTIT_DECL
my_query_interface(const extit_container_t *container, const char *name, iv_version_t base_version)
{
	return iv_repository_query(
		((const my_container_impl_t *) container)->ir,
		name, base_version);
}


static
extit_container_ops_1_0_t	my_container_ops =
{
	extit_container_get_symbol_default,		/* get_symbol */
	extit_container_get_function_default,		/* get_function */
	my_get_interface,				/* get_interface */
	my_query_interface,				/* query_interface */
	extit_container_log_default			/* log */
};



int
main(int argc, char **argv)
{
	my_container_impl_t	container_impl;
	iv_repository_t *	ir;
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

	iv_repository_set_flags(ir, EXTIT_FLAG_LOG_DEBUG);

	if(iv_repository_set(ir, PERSISTENCE_INTERFACE_ID,
	 PERSISTENCE_INTERFACE_TARGET, &persistence_interface, NULL)
	 != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr, "Unable to register interface %s@%u.%u\n",
			PERSISTENCE_INTERFACE_ID,
			IV_VERSION_MAJOR(PERSISTENCE_INTERFACE_TARGET),
			IV_VERSION_MINOR(PERSISTENCE_INTERFACE_TARGET));

		return 2;
	}

	container_impl.container.version = EXTIT_API_VERSION_1_0;
	container_impl.container.ops = &my_container_ops;
	container_impl.ir = ir;

	module = extit_module_load(
		&container_impl.container, argv[1], EXTIT_FLAG_LOG_TRACE);

	if(module != NULL)
	{
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

