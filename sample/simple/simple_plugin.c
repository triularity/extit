/*
 * @(#) simple_plugin.c
 *
 * This file is in the Public Domain.
 */

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/plugin_spi.h>


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
	switch(cmd)
	{
		case EXTIT_SPI_CMD_PROBE:
			/*
			 * We only need to support v1.0 for what we do
			 */
			if(!iv_matches(abi_version, EXTIT_ABI_VERSION_1_0))
				return EXTIT_STATUS_UNSUPPORTED;

			/*
			 * No need to check abi_version for other commands
			 * since they will only be called if v1.0+ after this
			 */
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_CREATE:
			extit_container_log(container, "Creating plugin\n");
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_DESTROY:
			extit_container_log(container, "Destroying plugin\n");
			return EXTIT_STATUS_OK;

		default:
			return EXTIT_STATUS_NOTIMPLEMENTED;
	}
}

EXTIT_DECLARE_SPI("{16a0590c-1acd-11e4-a457-406186e454c1}", IV_VERSION(1,0), "Simple Plugin", "1.0", plugin_handler)

