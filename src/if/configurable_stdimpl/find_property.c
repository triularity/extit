/*
 * @(#) if/configurable_stdimpl/find_property.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>
#include <if/configurable_stdimpl.h>

#ifdef  EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
if_configurable_propref_t *
EXTIT_DECL
if_configurable_stdimpl_find_property__1_0
(
	if_configurable_1_0_t *conf,
	const char *id
)
{
	const if_configurable_descriptor_t *	descriptor;
	const if_configurable_propdef_t **	props;
	uint32_t				count;


#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return NULL;
#endif

	descriptor = conf->ops->v0.op_get_descriptor(conf);

	props = descriptor->properties;
	count = descriptor->count;

	while(count-- != 0)
	{
		if(strcmp((*props)->id, id) == 0)
			return (if_configurable_propref_t *) *props;

		props++;
	}

	return NULL;
}


static
int
prop_compare(const void *key, const void *elem)
{
#define	_id	((const char *) key)
#define	_pp	((const if_configurable_propdef_t **) elem)

	return strcmp(_id, (*_pp)->id);

#undef	_id
#undef	_pp
}


EXTIT_EXPORT
if_configurable_propref_t *
EXTIT_DECL
if_configurable_stdimpl_find_property__1_0_sorted
(
	if_configurable_1_0_t *conf,
	const char *id
)
{
	const if_configurable_descriptor_t *	descriptor;
	void *					pp;


#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, IF_CONFIGURABLE_ABI_1_0))
                return NULL;
#endif

	descriptor = conf->ops->v0.op_get_descriptor(conf);

	pp = bsearch(
		id,
		descriptor->properties,
		sizeof(const if_configurable_propdef_t *),
		descriptor->count,
		prop_compare);

	return (pp != NULL)
		? *((if_configurable_propref_t **) pp)
		: NULL;
}
