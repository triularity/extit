/*
 * @(#) multiver_plugin.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/plugin_spi.h>

#include "persistence.h"


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
	iv_version_t	version;


	switch(cmd)
	{
		case EXTIT_SPI_CMD_PROBE:
			/*
			 * We only need to support v1.0 for what we do
			 */
			if(!iv_matches(abi_version, EXTIT_ABI_1_0))
				return EXTIT_STATUS_UNSUPPORTED;

			/*
			 * Quick check for dependencies
			 */
			version = extit_container_query_interface(
				container, 
				PERSISTENCE_IID,
				PERSISTENCE_ABI_TARGET);

			if(version == IV_VERSION_NONE)
			{
				fprintf(stderr,
					"Interface %s@%u.%u required\n",
					PERSISTENCE_IID,
					IV_VERSION_MAJOR(PERSISTENCE_ABI_TARGET),
					IV_VERSION_MINOR(PERSISTENCE_ABI_TARGET));

				return EXTIT_STATUS_UNSUPPORTED;
			}

			if(version < PERSISTENCE_ABI_TARGET)
			{
				fprintf(stderr,
					"Interface %s@%u.%u required (found %u.%u)\n",
					PERSISTENCE_IID,
					IV_VERSION_MAJOR(PERSISTENCE_ABI_TARGET),
					IV_VERSION_MINOR(PERSISTENCE_ABI_TARGET),
					IV_VERSION_MAJOR(version),
					IV_VERSION_MINOR(version));

				return EXTIT_STATUS_UNSUPPORTED;
			}

			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_CREATE:
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_DESTROY:
			return EXTIT_STATUS_OK;

		default:
			return EXTIT_STATUS_NOTIMPLEMENTED;
	}
}

#if	PERSISTENCE_ABI_TARGET >= PERSISTENCE_ABI_1_2
EXTIT_DECLARE_SPI("{80df29d5-2cf8-11e4-aa20-406186e454c1}", IV_VERSION(1,2), "Multiver Plugin", "1.2", plugin_handler)
#elif	PERSISTENCE_ABI_TARGET >= PERSISTENCE_ABI_1_1
EXTIT_DECLARE_SPI("{87e52ec2-2cf8-11e4-aa20-406186e454c1}", IV_VERSION(1,1), "Multiver Plugin", "1.1", plugin_handler)
#else
EXTIT_DECLARE_SPI("{236c4317-2cf8-11e4-aa20-406186e454c1}", IV_VERSION(1,0), "Multiver Plugin", "1.0", plugin_handler)
#endif


