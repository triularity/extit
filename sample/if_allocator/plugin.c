/*
 * @(#) sample/if_allocator/plugin.c
 *
 * This file is in the Public Domain.
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/plugin_spi.h>
#include <if/allocator.h>


typedef struct _myplugin
{
	if_allocator_t *	allocator;
	char *			buffer;
} myplugin_t;


static
extit_status_t
EXTIT_DECL
plugin_handler
(
	iv_version_t abi_version,
	const extit_container_t *container,
	extit_spi_command_t cmd,
	void *param,
	unsigned int flags
)
{
	if_allocator_t *		allocator;
	myplugin_t *			myplugin;
	extit_spi_param_create_t *	param_create;
	extit_spi_param_destroy_t *	param_destroy;


	switch(cmd)
	{
		case EXTIT_SPI_CMD_PROBE:
			/*
			 * We only need to support v1.0 for what we do
			 */
			if(!iv_matches(abi_version, EXTIT_ABI_1_0))
				return EXTIT_STATUS_UNSUPPORTED;

			/*
			 * Verify allocator support
			 */
			if(extit_container_query_interface(
			 container,
			 IF_ALLOCATOR_IID,
			 IF_ALLOCATOR_ABI_1_0)
			  == IV_VERSION_NONE)
			{
				extit_container_log(
					container,
					"Allocator interface 1.0 required");

				return EXTIT_STATUS_FAIL;
			}

			/*
			 * No need to check abi_version for other commands
			 * since they will only be called if v1.0+ after this
			 */
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_CREATE:
			extit_container_log(container, "Creating plugin\n");

			param_create = (extit_spi_param_create_t *) param;

			/*
			 * Get allocator
			 */
			allocator = extit_container_get_interface(
				container,
				IF_ALLOCATOR_IID,
				IF_ALLOCATOR_ABI_1_0);

			/*
			 * Use allocator to create plugin
			 */
			myplugin = if_allocator_alloc(
				allocator, sizeof(myplugin_t));

			myplugin->allocator = allocator;

			/*
			 * And some data buffer
			 */
			myplugin->buffer = if_allocator_alloc(
				allocator, 1000);

			if(myplugin->buffer == NULL)
			{
				if_allocator_free(allocator, myplugin);
				return EXTIT_STATUS_NOMEM;
			}

			param_create->spi_ctx = myplugin;

			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_DESTROY:
			extit_container_log(container, "Destroying plugin\n");

			param_destroy = (extit_spi_param_destroy_t *) param;

			myplugin = (myplugin_t *) param_destroy->spi_ctx;
			allocator = myplugin->allocator;

			if_allocator_free(allocator, myplugin->buffer);
			if_allocator_free(allocator, myplugin);

			return EXTIT_STATUS_OK;

		default:
			return EXTIT_STATUS_NOTIMPLEMENTED;
	}
}

EXTIT_DECLARE_SPI("{b61bf752-4562-11e6-9660-406186e454c1}", IV_VERSION(1,0), "Allocating Plugin", "1.0", plugin_handler)

