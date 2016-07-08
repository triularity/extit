/*
 * @(#) extit/if/messaging.h
 *
 * Messaging Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__messaging_h
#define	__extit__if__messaging_h

#include <stdlib.h>
#include <stdint.h>

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Messaging Interface ID
 */
#define EXTIT_IF_MESSAGING_IID		"{25eb0d84-38ee-11e6-9660-406186e454c1}/messaging"

/*
 * Messaging (v1.0)
 */
#define EXTIT_IF_MESSAGING_ABI_1_0	IV_VERSION(1,0)

typedef struct _extit_if_messaging_1_0	extit_if_messaging_1_0_t;

/*
 * A bound interface message
 */
typedef struct _extit_if_messaging_bound *
					extit_if_messaging_bound_t;

#define	EXTIT_IF_MESSAGING_BOUND_NONE	((extit_if_messaging_bound_t) NULL)

/*
 * Message listener callback
 */
typedef void				(*extit_if_messaging_listener_t)(
						const char *mid,
						void *data,
						void *client_data);

/*
 * A registered listener ID
 */
typedef uint32_t			extit_if_messaging_listener_id_t;

#define	EXTIT_IF_MESSAGING_LISTENER_ID_NONE	0


/*
 * ABI Version
 */
#ifndef	EXTIT_IF_MESSAGING_ABI
#define	EXTIT_IF_MESSAGING_ABI		EXTIT_IF_MESSAGING_ABI_1_0
#endif

#if	EXTIT_IF_MESSAGING_ABI == EXTIT_IF_MESSAGING_ABI_1_0
#define	extit_if_messaging_t		extit_if_messaging_1_0_t
#else
#error	Unsupported EXTIT_IF_MESSAGING_ABI
#endif


/*
 * Public API (v1.0)
 */
EXTIT_EXPORT
extit_if_messaging_listener_id_t
			EXTIT_DECL
			extit_if_messaging_add_listener(
				extit_if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				extit_if_messaging_listener_t callback,
				void *client_data);

EXTIT_EXPORT
extit_if_messaging_bound_t
			EXTIT_DECL
			extit_if_messaging_bind(
				extit_if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

EXTIT_EXPORT
extit_if_messaging_listener_id_t
			EXTIT_DECL
			extit_if_messaging_bound_add_liistener(
				extit_if_messaging_t *messaging,
				extit_if_messaging_bound_t bound,
				extit_if_messaging_listener_t callback,
				void *client_data);

EXTIT_EXPORT
extit_bool_t		EXTIT_DECL
			extit_if_messaging_bound_has_listener(
				extit_if_messaging_t *messaging,
				extit_if_messaging_bound_t bound);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_if_messaging_bound_remove_listener(
				extit_if_messaging_t *messaging,
				extit_if_messaging_bound_t bound,
				extit_if_messaging_listener_t callback,
				void *client_data);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_if_messaging_bound_send(
				extit_if_messaging_t *messaging,
				extit_if_messaging_bound_t bound,
				void *data);

EXTIT_EXPORT
extit_bool_t		EXTIT_DECL
			extit_if_messaging_has_listener(
				extit_if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_if_messaging_remove_listener(
				extit_if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				extit_if_messaging_listener_t callback,
				void *client_data);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_if_messaging_remove_listener_by_id(
				extit_if_messaging_t *messaging,
				extit_if_messaging_listener_id_t id);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_if_messaging_send(
				extit_if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				void *data);

EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			extit_if_messaging_unbind(
				extit_if_messaging_t *messaging,
				extit_if_messaging_bound_t bound);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__messaging_h */
