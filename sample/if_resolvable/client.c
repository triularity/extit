/*
 * @(#) if_resolvable/client.c
 *
 * This file is in the Public Domain.
 */

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>

/*
 * Select the interface targets we need (before those headers are included)
 */
#define	IF_CONFIGURABLE_ABI_TARGET	IF_CONFIGURABLE_ABI_1_0
#define	IF_REFCOUNT_ABI_TARGET		IF_REFCOUNT_ABI_1_0

#include <if/configurable.h>
#include <if/refcount.h>
#include <if/resolvable.h>

#include "myobj.h"


static
if_resolvable_t *
acquire_object_somehow(void)
{
	myobj_t *	obj;


	obj = myobj_secret_create();

	return myobj_get_resolvable(obj);
}


int
main(int argc, char **argv)
{
	if_resolvable_t *		resolvable;
	if_configurable_t *		configurable;
	if_configurable_propref_t *	prop_enabled;
	if_configurable_propref_t *	prop_message;
	if_refcount_t *			refcount;
	myobj_t *			obj;


	/*
	 * Get our generic resolvable object.
	 * Its implementation is a mystery to this part of the code.
	 */
	resolvable = acquire_object_somehow();

	/*
	 * Let's configure it
	 * XXX - Do NULL check in real code!
	 */
	configurable = (if_configurable_t *) if_resolvable_get_interface(
		resolvable,
		IF_CONFIGURABLE_IID,
		IF_CONFIGURABLE_ABI_1_0);


	/*
	 * Make sure we are enabled
	 */
	prop_enabled = if_configurable_find_property(configurable, "enabled");

	if_configurable_set_bool(configurable, prop_enabled, EXTIT_TRUE);


	/*
	 * Set something to say
	 */
	prop_message = if_configurable_find_property(configurable, "message");

	if_configurable_set_utf8(
		configurable, prop_message, "What are you doing, Dave?");


	/*
	 * Get our object
	 * XXX - Do NULL check in real code!
	 */
	obj = (myobj_t *) if_resolvable_get_interface(
		resolvable,
		MYOBJ_IID,
		MYOBJ_ABI_1_0);

	/*
	 * Send it
	 */
	myobj_send(obj);


	/*
	 * So many Dave quotes!
	 */
	if_configurable_set_utf8(
		configurable,
		prop_message,
		"They're all dead, Dave. Yes, Dave, they're all dead, Dave.");

	myobj_send(obj);


	/*
	 * Going out drinking.. Disable messages, incase we get totally drunk.
	 */
	if_configurable_set_bool(configurable, prop_enabled, EXTIT_FALSE);

	/* Glug.. glug.. glug.. */

	if_configurable_set_utf8(
		configurable,
		prop_message,
		"Youu kno sumbin, yuuu errr the best!");

	/*
	 * Try to send it
	 */
	myobj_send(obj);


	/*
	 * [Next day]
	 */
	if_configurable_set_bool(configurable, prop_enabled, EXTIT_TRUE);

	if_configurable_set_utf8(
		configurable,
		prop_message,
		"Ugh. What a night. Why is the sun so bright?");

	/*
	 * Send it
	 */
	myobj_send(obj);


	/*
	 * Done with it
	 * XXX - Do NULL check in real code!
	 */
	refcount = (if_refcount_t *) if_resolvable_get_interface(
		resolvable,
		IF_REFCOUNT_IID,
		IF_REFCOUNT_ABI_1_0);

	/*
	 * !!! All interfaces/references derived from resolvable should be
	 * considered invalid [to us] after this call (assuming it succeeds).
	 */
	if_refcount_release(refcount);


	return 0;
}
