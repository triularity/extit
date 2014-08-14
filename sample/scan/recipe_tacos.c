/*
 * @(#) recipe_tacos.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <extit/plugin_spi.h>

#include "recipe.h"


typedef struct _tacos_env
{
	/*
	 * Some hypothetical state information needed for making tacos
	 */
	unsigned int	stage;
	unsigned int	time_passed;
} tacos_env_t;


static
void
EXTIT_DECL
prepare_tacos(void *ctx)
{
	tacos_env_t *	tacos_env;


	tacos_env = (tacos_env_t *) ctx;

	fprintf(stderr, "Making some tacos...\n");
}


static recipe_t	tacos_recipe =
{
	"Tacos",
	10,
	50,
	prepare_tacos
};


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
	tacos_env_t *				tacos_env;
	extit_spi_param_create_t *		param_create;
	extit_spi_param_destroy_t *		param_destroy;
	extit_spi_param_get_interface_t *	param_get_interface;
	extit_spi_param_query_interface_t *	param_query_interface;


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
			param_create = (extit_spi_param_create_t *) param;

			if((tacos_env = calloc(1, sizeof(tacos_env_t))) == NULL)
				return EXTIT_STATUS_NOMEM;

			param_create->spi_ctx = tacos_env;
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_DESTROY:
			param_destroy = (extit_spi_param_destroy_t *) param;

			free(param_destroy->spi_ctx);
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_GET_INTERFACE:
			param_get_interface =
				(extit_spi_param_get_interface_t *) param;

			/*
			 * Recipe is the only supported interface by this
			 */
			if(strcmp(param_get_interface->name,
			 RECIPE_INTERFACE_NAME) != 0)
			{
				return EXTIT_STATUS_UNSUPPORTED;
			}

			if(param_get_interface->version
			 != RECIPE_INTERFACE_VERSION)
			{
				return EXTIT_STATUS_UNSUPPORTED;
			}

			param_get_interface->interface_ptr = &tacos_recipe;
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_QUERY_INTERFACE:
			param_query_interface =
				(extit_spi_param_query_interface_t *) param;

			/*
			 * Recipe is the only supported interface by this
			 */
			if(strcmp(param_query_interface->name,
			 RECIPE_INTERFACE_NAME) != 0)
			{
				return EXTIT_STATUS_UNSUPPORTED;
			}

			if(EXTIT_IV_MAJOR(param_query_interface->base_version)
			 != EXTIT_IV_MAJOR(RECIPE_INTERFACE_VERSION))
			{
				return EXTIT_STATUS_UNSUPPORTED;
			}

			if(param_query_interface->base_version
			 > RECIPE_INTERFACE_VERSION)
			{
				return EXTIT_STATUS_UNSUPPORTED;
			}

			param_query_interface->version =
				RECIPE_INTERFACE_VERSION;

			return EXTIT_STATUS_OK;

		default:
			return EXTIT_STATUS_UNSUPPORTED;
	}
}

EXTIT_DECLARE_SPI("{eaeb9b4b-234e-11e4-a457-406186e454c1}", EXTIT_IV(1,0), "Tacos Recipe", "1.0", plugin_handler)

