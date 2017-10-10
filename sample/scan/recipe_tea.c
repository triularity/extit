/*
 * @(#) recipe_tea.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/container_impl.h>
#include <extit/platform.h>
#include <extit/pmodule_impl.h>

#include "recipe.h"


typedef struct _recipe_impl
{
	recipe_t	recipe;

	/*
	 * Some hypothetical state information needed for making tea
	 */
	unsigned int	stage;
	unsigned int	time_passed;
	extit_bool_t	cup_ready;
} recipe_impl_t;


static
void
EXTIT_DECL
prepare_tea(recipe_t *recipe)
{
	recipe_impl_t *	impl;


	impl = (recipe_impl_t *) recipe;
	impl->stage = 0;

	fprintf(stderr, "Making some tea...\n");
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
	recipe_impl_t *	impl;


	if((impl = malloc(sizeof(recipe_impl_t))) == NULL)
		return EXTIT_STATUS_NOMEM;

	impl->recipe.name = "Tea";
	impl->recipe.prep_time = 2;
	impl->recipe.total_time = 10;
	impl->recipe.prepare = prepare_tea;
	impl->cup_ready = EXTIT_FALSE;

	impl->stage = 0;
	impl->time_passed = 0;

	*ctx_ptr = impl;
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
	free(ctx);

	return EXTIT_STATUS_OK;
}


static
void *
EXTIT_DECL
plugin_get_interface
(
	extit_pmodule_descriptor_1_0_t *descr,
	const extit_container_t *container,
	void *ctx,
	const char *iid,
	iv_version_t version
)
{
	recipe_impl_t *	impl;


	/*
	 * Recipe is the only supported interface by this
	 */
	if((EXTIT_STRCASECMP(RECIPE_INTERFACE_ID, iid) == 0)
	 && iv_matches(RECIPE_INTERFACE_VERSION, version))
	{
		impl = (recipe_impl_t *) ctx;

		return &impl->recipe;
	}

	return NULL;
}


static
iv_version_t
EXTIT_DECL
plugin_query_interface
(
	extit_pmodule_descriptor_1_0_t *descr,
	const extit_container_t *container,
	void *ctx,
	const char *iid,
	iv_version_t base_version
)
{
	/*
	 * Recipe is the only supported interface by this
	 */
	if((EXTIT_STRCASECMP(RECIPE_INTERFACE_ID, iid) == 0)
	 && iv_matches(RECIPE_INTERFACE_VERSION, base_version))
	{
		return RECIPE_INTERFACE_VERSION;
	}

	return IV_VERSION_NONE;
}


static
extit_pmodule_ops_1_0_t		plugin_ops =
{
	/* v0 */
	{
		NULL,				/* op_probe */
		plugin_create,			/* op_create */
		plugin_destroy,			/* op_destroy */
		plugin_get_interface,		/* op_get_interface */
		plugin_query_interface,		/* op_query_interface */
		NULL				/* op_unload */
	}
};


EXTIT_DECLARE_PMODULE("{cfd28bad-232d-11e4-a457-406186e454c1}", IV_VERSION(1,0), "Tea Recipe", "1.0", &plugin_ops)
