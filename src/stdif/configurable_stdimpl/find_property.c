/*
 * @(#) stdif/configurable_stdimpl/find_property.c
 *
 * Configurable Interface - find_property@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>


/**
 * Standard implementation to find a property reference by its ID.
 *
 * @param	configurable	The configurable instance.
 * @param	id		The property ID.
 *
 * @return	A pointer to the property reference,
 *		or @{constant NULL} if not found.
 *
 * @since	1.0
 */
stdif_configurable_propref_t *
EXTIT_DECL
stdif_configurable_stdimpl_find_property__1_0
(
	stdif_configurable_1_0_t *configurable,
	const char *id
)
{
	const stdif_configurable_descriptor_t *	descriptor;
	const stdif_configurable_propdef_t **	props;
	uint32_t				count;


	descriptor = configurable->ops->v0.op_get_descriptor(configurable);

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


/**
 * Standard implementation to find a property reference by its ID using
 * a binary search.
 *
 * @note	This function assumes that properties are in lexical order
 *		with regard to the @{func strcmp(const char *, const char *)}
 *		function.
 *
 * @param	configurable	The configurable instance.
 * @param	id		The property ID.
 *
 * @return	A pointer to the property reference,
 *		or @{constant NULL} if not found.
 *
 * @since	1.0
 */
stdif_configurable_propref_t *
EXTIT_DECL
stdif_configurable_stdimpl_find_property__1_0_sorted
(
	stdif_configurable_1_0_t *configurable,
	const char *id
)
{
	const stdif_configurable_descriptor_t *	descriptor;
	void *					pp;


	descriptor = configurable->ops->v0.op_get_descriptor(configurable);

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
