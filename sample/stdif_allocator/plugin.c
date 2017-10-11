/*
 * @(#) sample/stdif_allocator/plugin.c
 *
 * This file is in the Public Domain.
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule_impl.h>
#include <stdif/allocator.h>


typedef struct _myplugin
{
	stdif_allocator_t *	allocator;
	char *			buffer;
} myplugin_t;


static
extit_status_t
EXTIT_DECL
plugin_probe
(
	extit_pmodule_descriptor_1_0_t *descr,
	const extit_container_t *container
)
{
	/*
	 * Verify allocator support
	 */
	if(extit_container_query_interface(
	 container, STDIF_ALLOCATOR_IID, STDIF_ALLOCATOR_ABI_1_0)
	  == IV_VERSION_NONE)
	{
		extit_container_log(
			container, "Allocator interface 1.0 required");

		return EXTIT_STATUS_NOPREREQ;
	}

	return EXTIT_STATUS_OK;
}


static
extit_status_t
EXTIT_DECL
plugin_create
(
	extit_pmodule_descriptor_1_0_t *descr,
	const extit_container_t *container,
	void **ctx_ptr
)
{
	stdif_allocator_t *	allocator;
	myplugin_t *		myplugin;


	extit_container_log(container, "Creating plugin\n");

	/*
	 * Get allocator
	 */
	allocator = extit_container_get_interface(
		container, STDIF_ALLOCATOR_IID, STDIF_ALLOCATOR_ABI_1_0);

	/*
	 * Use allocator to create plugin
	 */
	myplugin = stdif_allocator_alloc(allocator, sizeof(myplugin_t));

	if(myplugin == NULL)
		return EXTIT_STATUS_NOMEM;

	myplugin->allocator = allocator;

	/*
	 * And some data buffer
	 */
	myplugin->buffer = stdif_allocator_alloc(allocator, 1000);

	if(myplugin->buffer == NULL)
	{
		stdif_allocator_free(allocator, myplugin);
		return EXTIT_STATUS_NOMEM;
	}

	*ctx_ptr = myplugin;
	return EXTIT_STATUS_OK;
}


static
extit_status_t
EXTIT_DECL
plugin_destroy
(
	extit_pmodule_descriptor_1_0_t *descr,
	const extit_container_t *container,
	void *ctx
)
{
	myplugin_t *		myplugin;
	stdif_allocator_t *	allocator;


	extit_container_log(container, "Destroying plugin\n");

	myplugin = (myplugin_t *) ctx;
	allocator = myplugin->allocator;

	stdif_allocator_free(allocator, myplugin->buffer);
	stdif_allocator_free(allocator, myplugin);

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
		NULL				/* op_unload */
	}
};

EXTIT_DECLARE_PMODULE("{b61bf752-4562-11e6-9660-406186e454c1}", IV_VERSION(1,0), "Allocating Plugin", "1.0", &plugin_ops)
