/*
 * @(#) multiver_plugin.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <iv/base.h>
#include <iv/util.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule_impl.h>

#include "persistence.h"


static
extit_status_t
EXTIT_DECL
my_probe
(
	extit_pmodule_descriptor_1_0_t *descr,
	extit_container_t *container
)
{
	iv_version_t	version;


	/*
	 * Quick check for dependencies
	 */
	version = extit_container_query_interface(
		container, 
		PERSISTENCE_IID,
		PERSISTENCE_ABI_TARGET);

	if(version == IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Interface %s@%u.%u required\n",
			PERSISTENCE_IID,
			IV_VERSION_MAJOR(PERSISTENCE_ABI_TARGET),
			IV_VERSION_MINOR(PERSISTENCE_ABI_TARGET));

		return EXTIT_STATUS_UNSUPPORTED;
	}

	if(version < PERSISTENCE_ABI_TARGET)
	{
		fprintf(stderr,
			"Interface %s@%u.%u required (found %u.%u)\n",
			PERSISTENCE_IID,
			IV_VERSION_MAJOR(PERSISTENCE_ABI_TARGET),
			IV_VERSION_MINOR(PERSISTENCE_ABI_TARGET),
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));

		return EXTIT_STATUS_UNSUPPORTED;
	}

	return EXTIT_STATUS_OK;
}


static
extit_pmodule_ops_1_0_t		my_ops =
{
	/* v0 */
	{
		my_probe,			/* op_probe */
		NULL,				/* op_create */
		NULL,				/* op_destroy */
		NULL,				/* op_get_interface */
		NULL,				/* op_query_interface */
		NULL				/* op_unload */
	}
};


#if	PERSISTENCE_ABI_TARGET >= PERSISTENCE_ABI_1_2
EXTIT_DECLARE_PMODULE("{80df29d5-2cf8-11e4-aa20-406186e454c1}", IV_VERSION(1,2), "Multiver Plugin", "1.2", &my_ops)
#elif	PERSISTENCE_ABI_TARGET >= PERSISTENCE_ABI_1_1
EXTIT_DECLARE_PMODULE("{87e52ec2-2cf8-11e4-aa20-406186e454c1}", IV_VERSION(1,1), "Multiver Plugin", "1.1", &my_ops)
#else
EXTIT_DECLARE_PMODULE("{236c4317-2cf8-11e4-aa20-406186e454c1}", IV_VERSION(1,0), "Multiver Plugin", "1.0", &my_ops)
#endif
