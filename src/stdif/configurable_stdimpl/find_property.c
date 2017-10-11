/*
 * @(#) stdif/configurable_stdimpl/find_property.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


stdif_configurable_propref_t *
EXTIT_DECL
stdif_configurable_stdimpl_find_property__1_0
(
	stdif_configurable_1_0_t *conf,
	const char *id
)
{
	const stdif_configurable_descriptor_t *	descriptor;
	const stdif_configurable_propdef_t **	props;
	uint32_t				count;


	descriptor = conf->ops->v0.op_get_descriptor(conf);

	props = descriptor->properties;
	count = descriptor->count;

	while(count-- != 0)
	{
		if(strcmp((*props)->id, id) == 0)
			return (stdif_configurable_propref_t *) *props;

		props++;
	}

	return NULL;
}


static
int
prop_compare(const void *key, const void *elem)
{
#define	_id	((const char *) key)
#define	_pp	((const stdif_configurable_propdef_t **) elem)

	return strcmp(_id, (*_pp)->id);

#undef	_id
#undef	_pp
}


stdif_configurable_propref_t *
EXTIT_DECL
stdif_configurable_stdimpl_find_property__1_0_sorted
(
	stdif_configurable_1_0_t *conf,
	const char *id
)
{
	const stdif_configurable_descriptor_t *	descriptor;
	void *					pp;


	descriptor = conf->ops->v0.op_get_descriptor(conf);

	pp = bsearch(
		id,
		descriptor->properties,
		sizeof(const stdif_configurable_propdef_t *),
		descriptor->count,
		prop_compare);

	return (pp != NULL)
		? *((stdif_configurable_propref_t **) pp)
		: NULL;
}
