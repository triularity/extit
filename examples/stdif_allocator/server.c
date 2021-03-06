/*
 * @(#) examples/stdif_allocator/server.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <string.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/container.h>
#include <extit/container_impl.h>
#include <extit/container_stdimpl.h>
#include <extit/platform.h>
#include <extit/pmodule.h>
#include <stdif/allocator.h>
#include <stdif/allocator_stdimpl.h>


static
void *
EXTIT_DECL
my_get_interface
(
	const extit_container_1_0_t *container,
	const char *id,
	iv_version_t version
)
{
	if((IV_IID_STRCMP(id, STDIF_ALLOCATOR_IID) == 0)
	 && (version == STDIF_ALLOCATOR_ABI_1_0))
	{
		return &stdif_allocator_stdimpl_1_0;
	}

	return NULL;
}


static
iv_version_t
EXTIT_DECL
my_query_interface
(
	const extit_container_1_0_t *container,
	const char *id,
	iv_version_t base_version
)
{
	if((IV_IID_STRCMP(id, STDIF_ALLOCATOR_IID) == 0)
	 && (base_version == STDIF_ALLOCATOR_ABI_1_0))
	{
		return STDIF_ALLOCATOR_ABI_1_0;
	}

	return IV_VERSION_NONE;
}


static
extit_container_ops_1_0_t	my_container_ops =
{
	/* v0 */
	{
		/* op_get_symbol */
		extit_container_stdimpl_get_symbol__1_0,

		/* op_get_function */
		extit_container_stdimpl_get_function__1_0,

		/* op_get_interface */
		my_get_interface,

		/* op_query_interface*/
		my_query_interface,

		/* op_log */
		extit_container_stdimpl_log__1_0
	}
};

static
extit_container_1_0_t		my_container =
{
	EXTIT_ABI_1_0,					/* version */
	&my_container_ops				/* ops */
};



int
main(int argc, char **argv)
{
	extit_module_t *	module;
	extit_plugin_t *	plugin;


	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <plugin-path>\n", argv[0]);
		return 1;
	}

	module = extit_module_load(
			(extit_container_t *) &my_container,
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
