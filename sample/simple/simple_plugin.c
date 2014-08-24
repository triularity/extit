/*
 * @(#) simple_plugin.c
 *
 * This file is in the Public Domain.
 */

#include <extit/base.h>
#include <extit/plugin_spi.h>


static
extit_status_t
EXTIT_DECL
plugin_handler
(
	extit_iv_t api_version,
	const extit_container_t *container,
	unsigned int cmd,
	void *param,
	unsigned int flags
)
{
	switch(cmd)
	{
		case EXTIT_SPI_CMD_PROBE:
			/*
			 * We only need to support v1.0 for what we do
			 */
			if(api_version < EXTIT_API_VERSION_1_0)
				return EXTIT_STATUS_UNSUPPORTED;

			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_CREATE:
			container->log(container, "Creating plugin\n");
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_ACTIVATE:
			container->log(container, "Activating plugin\n");
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_DEACTIVATE:
			container->log(container, "Deactivating plugin\n");
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_DESTROY:
			container->log(container, "Destroying plugin\n");
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_PING:
			container->log(container, "Pong\n");
			return EXTIT_STATUS_OK;

		default:
			return EXTIT_STATUS_UNSUPPORTED;
	}
}

EXTIT_DECLARE_SPI("{16a0590c-1acd-11e4-a457-406186e454c1}", EXTIT_IV(1,0), "Simple Plugin", "1.0", plugin_handler)

