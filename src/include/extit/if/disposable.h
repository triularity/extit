/*
 * @(#) extit/if/disposable.h
 *
 * Disposable Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__disposable_h
#define	__extit__if__disposable_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Disposable Interface ID
 */
#define EXTIT_IF_DISPOSABLE_IID		"{c20950b5-310a-11e6-9b95-406186e454c1}/disposable"

/*
 * Disposable (v1.0)
 */
#define EXTIT_IF_DISPOSABLE_VERSION_1_0	IV_VERSION(1,0)

typedef struct _extit_if_disposable_1_0	extit_if_disposable_1_0_t;


#ifndef	EXTIT_IF_DISPOSABLE_VERSION
#define	EXTIT_IF_DISPOSABLE_VERSION	EXTIT_IF_DISPOSABLE_VERSION_1_0
#endif

#if	EXTIT_IF_DISPOSABLE_VERSION == EXTIT_IF_DISPOSABLE_VERSION_1_0
#define	extit_if_disposable_t		extit_if_disposable_1_0_t
#else
#error	Unsupported EXTIT_IF_DISPOSABLE_VERSION
#endif


/*
 * Public API (v1.0)
 */
EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_if_disposable_free(
				extit_if_disposable_t *iface);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__disposable_h */