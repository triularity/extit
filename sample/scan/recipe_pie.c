/*
 * @(#) recipe_pie.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <extit/plugin_spi.h>

#include "recipe.h"


typedef struct _recipe_impl
{
	recipe_t	recipe;

	/*
	 * Some hypothetical state information needed for making pie
	 */
	unsigned int	stage;
	unsigned int	time_passed;
} recipe_impl_t;


static
void
EXTIT_DECL
prepare_pie(recipe_t *recipe)
{
	recipe_impl_t *	impl;


	impl = (recipe_impl_t *) recipe;
	impl->stage = 0;

	fprintf(stderr, "Making some pie...\n");
}


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
	recipe_impl_t *				ctx;
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
			if(!iv_matches(abi_version, EXTIT_ABI_VERSION_1_0))
				return EXTIT_STATUS_UNSUPPORTED;

			/*
			 * No need to check abi_version for other commands
			 * since they will only be called if v1.0+ after this
			 */
			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_CREATE:
			param_create = (extit_spi_param_create_t *) param;

			if((ctx = malloc(sizeof(recipe_impl_t))) == NULL)
				return EXTIT_STATUS_NOMEM;

			ctx->recipe.name = "Pie";
			ctx->recipe.prep_time = 10;
			ctx->recipe.total_time = 13;
			ctx->recipe.prepare = prepare_pie;

			ctx->stage = 0;
			ctx->time_passed = 0;

			param_create->spi_ctx = ctx;
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
			if(strcmp(RECIPE_INTERFACE_ID,
			 param_get_interface->id) != 0)
			{
				return EXTIT_STATUS_NOTFOUND;
			}

			if(!iv_matches(RECIPE_INTERFACE_VERSION,
			 param_get_interface->version))
			{
				return EXTIT_STATUS_NOTFOUND;
			}

			ctx = (recipe_impl_t *) param_get_interface->spi_ctx;
			param_get_interface->interface_ptr = &ctx->recipe;

			return EXTIT_STATUS_OK;

		case EXTIT_SPI_CMD_QUERY_INTERFACE:
			param_query_interface =
				(extit_spi_param_query_interface_t *) param;

			/*
			 * Recipe is the only supported interface by this
			 */
			if(strcmp(RECIPE_INTERFACE_ID,
			 param_query_interface->id) != 0)
			{
				return EXTIT_STATUS_NOTFOUND;
			}

			if(!iv_matches(RECIPE_INTERFACE_VERSION,
			 param_query_interface->base_version))
			{
				return EXTIT_STATUS_NOTFOUND;
			}

			param_query_interface->version =
				RECIPE_INTERFACE_VERSION;

			return EXTIT_STATUS_OK;

		default:
			return EXTIT_STATUS_NOTIMPLEMENTED;
	}
}

EXTIT_DECLARE_SPI("{3e29e568-234d-11e4-a457-406186e454c1}", IV_VERSION(1,0), "Pecan Pie Recipe", "1.0", plugin_handler)

