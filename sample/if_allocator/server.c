/*
 * @(#) sample/if_allocator/server.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <string.h>

#include <iv/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>
#include <if/allocator.h>
#include <if/allocator_stdimpl.h>


static
void *
EXTIT_DECL
my_get_interface
(
	const extit_container_t *container,
	const char *id,
	iv_version_t version
)
{
	if((strcmp(id, IF_ALLOCATOR_IID) == 0)
	 && (version == IF_ALLOCATOR_ABI_1_0))
	{
		return &if_allocator_stdimpl_1_0;
	}

	return NULL;
}


static
iv_version_t
EXTIT_DECL
my_query_interface
(
	const extit_container_t *container,
	const char *id,
	iv_version_t base_version
)
{
	if((strcmp(id, IF_ALLOCATOR_IID) == 0)
	 && (base_version == IF_ALLOCATOR_ABI_1_0))
	{
		return IF_ALLOCATOR_ABI_1_0;
	}

	return IV_VERSION_NONE;
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
		fprintf(stderr, "Usage: if_allocator_server <plugin-path>\n");
		return 1;
	}

	module = extit_module_load(
			&my_container,
			argv[1],
			EXTIT_FLAG_LOG_TRACE);

	if(module != NULL)
	{
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

	return 0;
}
