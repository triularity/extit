/*
 * @(#) recipe_tea.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/plugin_spi.h>

#include "recipe.h"


typedef struct _tea_env
{
	/*
	 * Some hypothetical state information needed for making tea
	 */
	unsigned int	stage;
	unsigned int	time_passed;
} tea_env_t;


static
void
EXTIT_DECL
prepare_tea(void *ctx)
{
	tea_env_t *	tea_env;


	tea_env = (tea_env_t *) ctx;
	tea_env->stage = 0;

	fprintf(stderr, "Making some tea...\n");
}


static recipe_t	tea_recipe =
{
	"Tea",
	10,
	26,
	prepare_tea
};


static
extit_status_t
EXTIT_DECL
plugin_handler
(
	iv_version_t api_version,
	const extit_container_t *container,
	unsigned int cmd,
	void *param,
	unsigned int flags
)
{
	tea_env_t *				tea_env;
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

			if((tea_env = calloc(1, sizeof(tea_env_t))) == NULL)
				return EXTIT_STATUS_NOMEM;

			param_create->spi_ctx = tea_env;
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

			param_get_interface->interface_ptr = &tea_recipe;
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

			if(IV_VERSION_MAJOR(param_query_interface->base_version)
			 != IV_VERSION_MAJOR(RECIPE_INTERFACE_VERSION))
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

EXTIT_DECLARE_SPI("{cfd28bad-232d-11e4-a457-406186e454c1}", IV_VERSION(1,0), "Tea Recipe", "1.0", plugin_handler)

