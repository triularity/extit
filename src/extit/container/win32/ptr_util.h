/*
 * @(#) ptr_util.h
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__ptr_util_h
#define	__ptr_util_h

#include <windows.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__GNUC__
/* Inline this, somehow? */
extern void *				_extit_funcptr_to_voidptr(FARPROC ptr);

#define	FUNCPTR_TO_VOIDPTR(x)		_extit_funcptr_to_voidptr(x)
#else
#define	FUNCPTR_TO_VOIDPTR(x)		((void *) (x))
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* !__ptr_util_h */
