/*
 * @(#) sample/if_referenced/myobj.h
 *
 * This file is in the Public Domain.
 */

#ifndef	__myobj_h
#define	__myobj_h

#include <if/referenced.h>


typedef enum myobj_type
{
	MYOBJ_TYPE_FOO,
	MYOBJ_TYPE_BAR,
	MYOBJ_TYPE_FIZBIN
} myobj_type_t;


typedef struct myobj		myobj_t;

struct myobj
{
	myobj_type_t		type;
	if_referenced_t *	(*get_if_referenced)(myobj_t *obj);
};

#endif	/* !__myobj_h */
