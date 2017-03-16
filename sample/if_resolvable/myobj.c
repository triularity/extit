/*
 * @(#) sample/if_resolvable/myobj.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <extit/util.h>
#include <if/configurable.h>
#include <if/configurable_impl.h>
#include <if/configurable_stdimpl.h>
#include <if/referenced.h>
#include <if/referenced_impl.h>
#include <if/resolvable.h>
#include <if/resolvable_impl.h>

#include "myobj.h"
#include "myobj_priv.h"


#define	DEFAULT_MESSAGE		"I pity the fool that doesn't set a message!"


static
void
my_free_obj(myobj_t *obj);


/**
 ** Configurable
 **/

static
if_configurable_propref_t	conf_prop_enabled =
{
	{
		"enabled",
		"Enabled",
		"Enable the action",
		IF_CONFIGURABLE_TYPE_BOOL,

		.spec.type_bool.def_value = EXTIT_TRUE
	},
	(int) offsetof(myobj_t, enabled)
		- (int) offsetof(myobj_t, configurable),
	NULL
};


static
if_configurable_propref_t	conf_prop_message =
{
	{
		"message",
		"Message",
		"The message to send",
		IF_CONFIGURABLE_TYPE_UTF8,

		.spec.type_utf8.def_value = NULL
	},
	(int) offsetof(myobj_t, message)
		- (int) offsetof(myobj_t, configurable),
	NULL
};


static
const
if_configurable_propdef_t *	conf_props[2] =
{
	&conf_prop_enabled.definition,
	&conf_prop_message.definition
};


static
if_configurable_descriptor_t	conf_descriptor =
{
	conf_props,
	2
};


/**
 ** Resolvable
 **/

static
void *
EXTIT_DECL
my_resolv_get_interface
(
	if_resolvable_t *resolvable,
	const char *id,
	iv_version_t version
)
{
	/*
	 * Just simple if/else if's for example ...
	 */

	if((strcmp(id, MYOBJ_IID) == 0)
	 && iv_matches(MYOBJ_ABI_1_0, version))
	{
		return ((char *) resolvable)
			- offsetof(myobj_t, resolvable);
	}

	if((strcmp(id, IF_REFERENCED_IID) == 0)
	 && iv_matches(IF_REFERENCED_ABI_1_0, version))
	{
		return ((char *) resolvable)
			- offsetof(myobj_t, resolvable)
			+ offsetof(myobj_t, referenced);
	}

	if((strcmp(id, IF_CONFIGURABLE_IID) == 0)
	 && iv_matches(IF_CONFIGURABLE_ABI_1_0, version))
	{
		return ((char *) resolvable)
			- offsetof(myobj_t, resolvable)
			+ offsetof(myobj_t, configurable);
	}

	return NULL;
}


static
iv_version_t
EXTIT_DECL
my_resolv_query_interface
(
	if_resolvable_t *resolvable,
	const char *id,
	iv_version_t base_version
)
{
	if((strcmp(id, MYOBJ_IID) == 0)
	 && iv_matches(MYOBJ_ABI_1_0, base_version))
	{
		return MYOBJ_ABI_1_0;
	}

	if((strcmp(id, IF_REFERENCED_IID) == 0)
	 && iv_matches(IF_REFERENCED_ABI_1_0, base_version))
	{
		return IF_REFERENCED_ABI_1_0;
	}

	if((strcmp(id, IF_CONFIGURABLE_IID) == 0)
	 && iv_matches(IF_CONFIGURABLE_ABI_1_0, base_version))
	{
		return IF_CONFIGURABLE_ABI_1_0;
	}

	return IV_VERSION_NONE;
}


static
if_resolvable_ops_1_0_t		my_resolv_ops =
{
	my_resolv_get_interface,	/* op_get_interface */
	my_resolv_query_interface	/* op_query_interface */
};


/**
 ** Referenced
 **/

static
extit_status_t
EXTIT_DECL
my_referenced_add(if_referenced_t *referenced)
{
	myobj_t *	obj;


	obj = (myobj_t *)
		(((char *) referenced) - offsetof(myobj_t, referenced));

	return extit_refcount_add(&obj->numrefs);
}


static
extit_status_t
EXTIT_DECL
my_referenced_release(if_referenced_t *referenced)
{
	myobj_t *	obj;
	extit_status_t	status;


	obj = (myobj_t *)
		(((char *) referenced) - offsetof(myobj_t, referenced));

	status = extit_refcount_release(&obj->numrefs);

	if(status == EXTIT_STATUS_OK)
		my_free_obj(obj);

	return status;
}


static
if_referenced_ops_1_0_t		my_referenced_ops =
{
	my_referenced_add,		/* op_add */
	my_referenced_release		/* op_release */
};


/**
 ** myobj
 **/

static
void
my_free_obj(myobj_t *obj)
{
	if(obj->message != NULL)
		free(obj->message);

	free(obj);
}


static
void
EXTIT_DECL
my_send(myobj_t *obj)
{
	const char *	msg;


	if(obj->enabled)
	{
		if((msg = obj->message) == NULL)
			msg = DEFAULT_MESSAGE;

		printf("%s\n", msg);
	}
}


myobj_t *
myobj_secret_create(void)
{
	myobj_t *	obj;


	/* XXX - Do NULL check in real thing! */
	obj = malloc(sizeof(myobj_t));

	obj->resolvable.version = IF_RESOLVABLE_ABI_1_0;
	obj->resolvable.ops_1_0 = &my_resolv_ops;

	obj->configurable.version = IF_CONFIGURABLE_ABI_1_0;
	obj->configurable.ops = &if_configurable_stdimpl_ops_1_0;
	obj->configurable.descriptor = &conf_descriptor;

	obj->referenced.version = IF_REFERENCED_ABI_1_0;
	obj->referenced.ops_1_0 = &my_referenced_ops;

	obj->numrefs = EXTIT_REFCOUNT_NONE;
	obj->enabled = EXTIT_TRUE;
	obj->message = NULL;
	obj->op_send = my_send;

	extit_refcount_add(&obj->numrefs);

	return obj;
}

