/*
 * @(#) simple_plugin.c
 *
 * This file is in the Public Domain.
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>
#include <extit/pmodule_impl.h>


static
extit_status_t
EXTIT_DECL
plugin_probe
(
	extit_pmodule_descriptor_1_0_t *descr,
	extit_container_t *container
)
{
	/*
	 * We only need to support v1.0 for what we do
	 */
	if(!iv_matches(container->version, EXTIT_ABI_1_0))
		return EXTIT_STATUS_UNSUPPORTED;

	/*
	 * No need to check ABI version for other commands
	 * since they will only be called if v1.0+ after this
	 */
	return EXTIT_STATUS_OK;
}


static
extit_status_t
EXTIT_DECL
plugin_create
(
	extit_pmodule_descriptor_1_0_t *descr,
	extit_container_t *container,
	void **ctx_ptr
)
{
	extit_container_log(container, "Creating plugin\n");
	return EXTIT_STATUS_OK;
}


static
extit_status_t
EXTIT_DECL
plugin_destroy
(
	extit_pmodule_descriptor_1_0_t *descr,
	extit_container_t *container,
	void *ctx
)
{
	extit_container_log(container, "Destroying plugin\n");
	return EXTIT_STATUS_OK;
}


static
extit_status_t
EXTIT_DECL
plugin_unload
(
	extit_pmodule_descriptor_1_0_t *descr,
	extit_container_t *container
)
{
	extit_container_log(container, "Unloading module\n");
	return EXTIT_STATUS_OK;
}


static
extit_pmodule_ops_1_0_t		plugin_ops =
{
	/* v0 */
	{
		plugin_probe,			/* op_probe */
		plugin_create,			/* op_create */
		plugin_destroy,			/* op_destroy */
		NULL,				/* op_get_interface */
		NULL,				/* op_query_interface */
		plugin_unload			/* op_unload */
	}
};

EXTIT_DECLARE_PMODULE("{16a0590c-1acd-11e4-a457-406186e454c1}", IV_VERSION(1,0), "Simple Plugin", "1.0", &plugin_ops)
