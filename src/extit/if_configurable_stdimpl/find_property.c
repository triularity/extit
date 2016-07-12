/*
 * @(#) extit/if_configurable_stdimpl/find_property.c
 *
 * Configurable Interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <extit/if/configurable.h>
#include <extit/if/configurable_impl.h>
#include <extit/if/configurable_stdimpl.h>

#ifdef  EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_if_configurable_propref_t *
EXTIT_DECL
extit_if_configurable_find_property_stdimpl
(
	extit_if_configurable_t *conf,
	const char *id
)
{
	const extit_if_configurable_descriptor_t *	descriptor;
	const extit_if_configurable_propdef_t **	props;
	uint32_t					count;


#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, EXTIT_IF_CONFIGURABLE_ABI_1_0))
                return NULL;
#endif

	descriptor = conf->descriptor;

	props = descriptor->properties;
	count = descriptor->count;

	while(count-- != 0)
	{
		if(strcmp((*props)->id, id) == 0)
			return (extit_if_configurable_propref_t *) *props;

		props++;
	}

	return NULL;
}


static
int
prop_compare(const void *key, const void *elem)
{
#define	_id	((const char *) key)
#define	_pp	((const extit_if_configurable_propdef_t **) elem)

	return strcmp(_id, (*_pp)->id);

#undef	_id
#undef	_pp
}


EXTIT_EXPORT
extit_if_configurable_propref_t *
EXTIT_DECL
extit_if_configurable_find_property_stdimpl_sorted
(
	extit_if_configurable_t *conf,
	const char *id
)
{
	const extit_if_configurable_descriptor_t *	descriptor;
	void *						pp;


#ifdef  EXTIT_PARANOID
        if(!iv_matches(conf->version, EXTIT_IF_CONFIGURABLE_ABI_1_0))
                return NULL;
#endif

	descriptor = conf->descriptor;

	pp = bsearch(
		id,
		descriptor->properties,
		sizeof(const extit_if_configurable_propdef_t *),
		descriptor->count,
		prop_compare);

	return (pp != NULL)
		? *((extit_if_configurable_propref_t **) pp)
		: NULL;
}
