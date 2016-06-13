/*
 * @(#) extit/iface/refcount.h
 *
 * Reference Count Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__iface__refcount_h
#define	__extit__iface__refcount_h

#include <iv/base.h>
#include <extit/base.h>
#include <extit/util.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Reference Count Interface ID
 */
#define EXTIT_IFACE_REFCOUNT_IID	"{e8fc9c0b-30fa-11e6-9b95-406186e454c1}/refcount"

/*
 * Reference Count (v1.0)
 */
#define EXTIT_IFACE_REFCOUNT_VERSION_1_0	\
					IV_VERSION(1,0)

typedef struct _extit_iface_refcount_1_0	\
					extit_iface_refcount_1_0_t;


#define	EXTIT_IFACE_REFCOUNT_VERSION	EXTIT_IFACE_REFCOUNT_VERSION_1_0
#define	extit_iface_refcount_t		extit_iface_refcount_1_0_t


/*
 * Public API (v1.0)
 */
EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_iface_refcount_add(
				extit_iface_refcount_t *iface);

EXTIT_EXPORT
extit_refcount_t	EXTIT_DECL
			extit_iface_refcount_get(
				extit_iface_refcount_t *iface);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_iface_refcount_release(
				extit_iface_refcount_t *iface);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__iface__refcount_h */
