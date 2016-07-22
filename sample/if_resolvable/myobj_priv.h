/*
 * @(#) sample/if_resolvable/myobj_priv.h
 *
 * This file is in the Public Domain.
 */

#ifndef	__myobj_priv_h
#define	__myobj_priv_h

#include <extit/base.h>
#include <extit/util.h>
#include <if/configurable_impl.h>
#include <if/referenced_impl.h>
#include <if/resolvable_impl.h>

#include "myobj.h"


struct _myobj
{
	if_resolvable_t		resolvable;

	extit_refcount_t	numrefs;
	extit_bool_t		enabled;
	char *			message;

	void			(EXTIT_DECL *op_send)(myobj_t *obj);

	if_referenced_t		referenced;
	if_configurable_t	configurable;
};


#endif	/* !__myobj_priv_h */
