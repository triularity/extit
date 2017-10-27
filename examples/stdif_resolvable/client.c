/*
 * @(#) examples/stdif_resolvable/client.c
 *
 * This file is in the Public Domain.
 */

#include <stddef.h>
#include <stdbool.h>

#include <iv/base.h>
#include <extit/base.h>

/*
 * Select the interface targets we need (before those headers are included)
 */
#define	STDIF_CONFIGURABLE_ABI_TARGET	STDIF_CONFIGURABLE_ABI_1_0
#define	STDIF_REFERENCED_ABI_TARGET	STDIF_REFERENCED_ABI_1_0

#include <stdif/configurable.h>
#include <stdif/referenced.h>
#include <stdif/resolvable.h>

#include "myobj.h"


static
stdif_resolvable_t *
acquire_object_somehow(void)
{
	myobj_t *	obj;


	obj = myobj_secret_create();

	return myobj_get_resolvable(obj);
}


int
main(int argc, char **argv)
{
	stdif_resolvable_t *		resolvable;
	stdif_configurable_t *		configurable;
	stdif_configurable_propref_t *	prop_enabled;
	stdif_configurable_propref_t *	prop_message;
	stdif_referenced_t *		referenced;
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
	configurable = (stdif_configurable_t *) stdif_resolvable_get_interface(
		resolvable,
		STDIF_CONFIGURABLE_IID,
		STDIF_CONFIGURABLE_ABI_1_0);


	/*
	 * Make sure we are enabled
	 */
	prop_enabled = stdif_configurable_find_property(
		configurable, "enabled");

	stdif_configurable_set_bool(configurable, prop_enabled, true);


	/*
	 * Set something to say
	 */
	prop_message = stdif_configurable_find_property(
		configurable, "message");

	stdif_configurable_set_utf8(
		configurable, prop_message, "What are you doing, Dave?");


	/*
	 * Get our object
	 * XXX - Do NULL check in real code!
	 */
	obj = (myobj_t *) stdif_resolvable_get_interface(
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
	stdif_configurable_set_utf8(
		configurable,
		prop_message,
		"They're all dead, Dave. Yes, Dave, they're all dead, Dave.");

	myobj_send(obj);


	/*
	 * Going out drinking.. Disable messages, incase we get totally drunk.
	 */
	stdif_configurable_set_bool(configurable, prop_enabled, false);

	/* Glug.. glug.. glug.. */

	stdif_configurable_set_utf8(
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
	stdif_configurable_set_bool(configurable, prop_enabled, true);

	stdif_configurable_set_utf8(
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
	referenced = (stdif_referenced_t *) stdif_resolvable_get_interface(
		resolvable,
		STDIF_REFERENCED_IID,
		STDIF_REFERENCED_ABI_1_0);

	/*
	 * !!! All interfaces/references derived from resolvable should be
	 * considered invalid [to us] after this call (assuming it succeeds).
	 */
	stdif_referenced_release(referenced);


	return 0;
}
