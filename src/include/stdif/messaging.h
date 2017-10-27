/*
 * @(#) stdif/messaging.h
 *
 * Messaging Interface.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__messaging_h
#define	__stdif__messaging_h

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <iv/base.h>
#include <extit/base.h>

#ifdef	stdif_messaging_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * A bound interface message
 */
typedef struct _stdif_messaging_bound 	stdif_messaging_bound_t;

#define	STDIF_MESSAGING_BOUND_NONE	((stdif_messaging_bound_t *) NULL)


/*
 * Message listener callback
 */
typedef void				(*stdif_messaging_listener_t)(
						const char *mid,
						void *data,
						void *client_data);


/*
 * A registered listener ID
 */
typedef uint32_t			stdif_messaging_listener_id_t;

#define	STDIF_MESSAGING_LISTENER_ID_NONE	0


/*
 * Messaging Interface ID
 */
#define STDIF_MESSAGING_IID		"{c1c017b1-44d5-11e6-9660-406186e454c1}/messaging"


/*
 * Messaging (base)
 */
typedef struct _stdif_messaging		stdif_messaging_t;


/*
 * Messaging (v1.0)
 */
#define STDIF_MESSAGING_ABI_1_0		IV_VERSION(1,0)

typedef struct _stdif_messaging_1_0	stdif_messaging_1_0_t;

LIBAPI
stdif_messaging_listener_id_t
			EXTIT_DECL
			stdif_messaging_add_listener__1_0(
				stdif_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				stdif_messaging_listener_t callback,
				void *client_data);

LIBAPI
stdif_messaging_bound_t *	EXTIT_DECL
			stdif_messaging_bind__1_0(
				stdif_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

LIBAPI
stdif_messaging_listener_id_t
			EXTIT_DECL
			stdif_messaging_bound_add_listener__1_0(
				stdif_messaging_t *messaging,
				stdif_messaging_bound_t *bound,
				stdif_messaging_listener_t callback,
				void *client_data);

LIBAPI
bool			EXTIT_DECL
			stdif_messaging_bound_has_listener__1_0(
				stdif_messaging_t *messaging,
				stdif_messaging_bound_t *bound);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_messaging_bound_remove_listener__1_0(
				stdif_messaging_t *messaging,
				stdif_messaging_bound_t *bound,
				stdif_messaging_listener_t callback,
				void *client_data);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_messaging_bound_send__1_0(
				stdif_messaging_t *messaging,
				stdif_messaging_bound_t *bound,
				void *data);

LIBAPI
bool			EXTIT_DECL
			stdif_messaging_has_listener__1_0(
				stdif_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_messaging_remove_listener__1_0(
				stdif_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				stdif_messaging_listener_t callback,
				void *client_data);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_messaging_remove_listener_by_id__1_0(
				stdif_messaging_t *messaging,
				stdif_messaging_listener_id_t id);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_messaging_send__1_0(
				stdif_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				void *data);

LIBAPI
extit_status_t		EXTIT_DECL
			stdif_messaging_unbind__1_0(
				stdif_messaging_t *messaging,
				stdif_messaging_bound_t *bound);


/*
 * ABI Version
 */
#ifndef	STDIF_MESSAGING_ABI_TARGET
#define	STDIF_MESSAGING_ABI_TARGET	STDIF_MESSAGING_ABI_1_0
#endif

#if	IV_VERSION_MAJOR(STDIF_MESSAGING_ABI_TARGET) == 1
#define	stdif_messaging_add_listener	stdif_messaging_add_listener__1_0
#define	stdif_messaging_bind		stdif_messaging_bind__1_0

#define	stdif_messaging_bound_add_listener	\
					stdif_messaging_bound_add_listener__1_0

#define	stdif_messaging_bound_has_listener	\
					stdif_messaging_bound_has_listener__1_0

#define	stdif_messaging_bound_remove_listener \
				stdif_messaging_bound_remove_listener__1_0

#define	stdif_messaging_bound_send	stdif_messaging_bound_send__1_0
#define	stdif_messaging_has_listener	stdif_messaging_has_listener__1_0
#define	stdif_messaging_remove_listener	stdif_messaging_remove_listener__1_0

#define	stdif_messaging_remove_listener_by_id \
				stdif_messaging_remove_listener_by_id__1_0

#define	stdif_messaging_send		stdif_messaging_send__1_0
#define	stdif_messaging_unbind		stdif_messaging_unbind__1_0
#endif	/* IV_VERSION_MAJOR(STDIF_MESSAGING_ABI_TARGET) == 1 */

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__stdif__messaging_h */
