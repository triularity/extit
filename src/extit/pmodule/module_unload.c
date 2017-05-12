/*
 * @(#) pmodule/container_common.c
 *
 * Platform neutral container library implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>

#include <extit/base.h>
#include <extit/util.h>
#include <extit/container.h>
#include <extit/pmodule.h>
#include <extit/pmodule_impl.h>

#include "pmodule_internal.h"


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
_extit_module_unload
(
	extit_module_t *module
)
{
	unsigned int				flags;
	extit_pmodule_descriptor_1_0_t *	descriptor;
	extit_status_t				status;


	flags = module->flags;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:module] Unloading module, ID: %s.\n",
			extit_module_get_id(module));
	}
#endif

	if(!extit_refcount_isnone(&module->refcount))
	{
#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		{
			fprintf(stderr,
			 "[extit:module] Module is busy, refcount = %u.\n",
				module->refcount);
		}
#endif

		return EXTIT_STATUS_BUSY;
	}

#ifdef	EXTIT_PARANOID
	if(IV_VERSION_MAJOR(module->abi_version) != 1)
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	descriptor = (extit_pmodule_descriptor_1_0_t *) module->descriptor;

	if(descriptor->ops->v0.op_unload == NULL)
		return EXTIT_STATUS_OK;

	status = descriptor->ops->v0.op_unload(descriptor, module->container);

	if(status == EXTIT_STATUS_NOTIMPLEMENTED)
	{
		status = EXTIT_STATUS_OK;

#ifdef	EXTIT_DEBUG
		if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		{
			fprintf(stderr,
 				"[extit:module] Unload not implemented\n");
		}
#endif	/* EXTIT_DEBUG */
	}

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
	{
		if(status != EXTIT_STATUS_OK)
		{
			fprintf(stderr,
 				"[extit:module] Unload failed, status = %u.\n",
				status);
		}
	}
#endif	/* EXTIT_DEBUG */

	return status;
}
