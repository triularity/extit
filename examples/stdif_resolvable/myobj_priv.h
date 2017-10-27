/*
 * @(#) examples/stdif_resolvable/myobj_priv.h
 *
 * This file is in the Public Domain.
 */

#ifndef	__myobj_priv_h
#define	__myobj_priv_h

#include <stdbool.h>

#include <extit/base.h>
#include <extit/util.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>
#include <stdif/referenced_impl.h>
#include <stdif/resolvable_impl.h>

#include "myobj.h"


struct _myobj
{
	stdif_resolvable_1_0_t		resolvable;

	extit_refcount_t		numrefs;
	bool				enabled;
	char *				message;

	void				(EXTIT_DECL *op_send)(myobj_t *obj);

	stdif_referenced_1_0_t		referenced;

	stdif_configurable_stdimpl_1_0_t
					configurable;
};


#endif	/* !__myobj_priv_h */
