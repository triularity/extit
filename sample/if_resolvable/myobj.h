/*
 * @(#) if_resolvable/myobj.h
 *
 * This file is in the Public Domain.
 */

#ifndef	__myobj_h
#define	__myobj_h

#include <iv/base.h>
#include <if/resolvable.h>


#define	MYOBJ_IID		"myobj"
#define	MYOBJ_ABI_1_0		IV_VERSION(1, 0)

typedef struct _myobj		myobj_t;


myobj_t *			myobj_secret_create(void);


if_resolvable_t *		EXTIT_DECL
				myobj_get_resolvable(myobj_t *obj);

void				EXTIT_DECL
				myobj_send(myobj_t *obj);

#endif	/* !__myobj_h */
