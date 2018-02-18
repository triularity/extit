/*
 * @(#) stdif/referenced.h
 *
 * Referenced Interface.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__referenced_h
#define	__stdif__referenced_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	stdif_referenced_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Referenced Interface ID
 */
#define STDIF_REFERENCED_IID		"referenced@{c1c017b1-44d5-11e6-9660-406186e454c1}"


/*
 * Referenced (base)
 */
typedef struct _stdif_referenced	stdif_referenced_t;


/*
 * Referenced (v1.0)
 */
#define STDIF_REFERENCED_ABI_1_0	IV_VERSION(1,0)

typedef struct _stdif_referenced_1_0	stdif_referenced_1_0_t;

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_referenced_add__1_0(
				stdif_referenced_t *referenced);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_referenced_release__1_0(
				stdif_referenced_t *referenced);


/*
 * ABI Version
 */
#ifndef	STDIF_REFERENCED_ABI_TARGET
#define	STDIF_REFERENCED_ABI_TARGET	STDIF_REFERENCED_ABI_1_0
#endif

#if	IV_VERSION_MAJOR(STDIF_REFERENCED_ABI_TARGET) == 1
#define	stdif_referenced_add		stdif_referenced_add__1_0
#define	stdif_referenced_release	stdif_referenced_release__1_0
#endif

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__stdif__referenced_h */
