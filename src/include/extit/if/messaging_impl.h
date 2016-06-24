/*
 * @(#) extit/if/messaging_impl.h
 *
 * Messaging Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__messaging_impl_h
#define	__extit__if__messaging_impl_h

#include <iv/base.h>
#include <extit/base.h>
#include <extit/if/messaging.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _extit_if_messaging_ops_1_0
{
	extit_if_messaging_listener_id_t
				(EXTIT_DECL *add_listener)(
					extit_if_messaging_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version,
					extit_if_messaging_listener_t cb,
					void *client_data);

	extit_status_t		(EXTIT_DECL *remove_listener)(
					extit_if_messaging_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version,
					extit_if_messaging_listener_t cb,
					void *client_data);

	extit_status_t		(EXTIT_DECL *remove_listener_by_id)(
					extit_if_messaging_t *messaging,
					extit_if_messaging_listener_id_t id);

	extit_bool_t		(EXTIT_DECL *has_listener)(
					extit_if_messaging_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version);

	extit_status_t		(EXTIT_DECL *send)(
					extit_if_messaging_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version,
					void *data);

	extit_if_messaging_bound_t
				(EXTIT_DECL *bind)(
					extit_if_messaging_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version);

	extit_status_t		(EXTIT_DECL *unbind)(
					extit_if_messaging_t *messaging,
					extit_if_messaging_bound_t bound);

	extit_if_messaging_listener_id_t
				(EXTIT_DECL *bound_add_listener)(
					extit_if_messaging_t *messaging,
					extit_if_messaging_bound_t bound,
					extit_if_messaging_listener_t cb,
					void *client_data);

	extit_status_t		(EXTIT_DECL *bound_remove_listener)(
					extit_if_messaging_t *messaging,
					extit_if_messaging_bound_t bound,
					extit_if_messaging_listener_t cb,
					void *client_data);

	extit_bool_t		(EXTIT_DECL *bound_has_listener)(
					extit_if_messaging_t *messaging,
					extit_if_messaging_bound_t bound);

	extit_status_t		(EXTIT_DECL *bound_send)(
					extit_if_messaging_t *messaging,
					extit_if_messaging_bound_t bound,
					void *data);
} extit_if_messaging_ops_1_0_t;

struct _extit_if_messaging_1_0
{
	iv_version_t			version;	/* 1.0+ */
	extit_if_messaging_ops_1_0_t *	ops;
};


#define	EXTIT_IF_MESSAGING_ADD_LISTENER(messaging, mid, iid, version, callback, client_data)	\
			((messaging)->ops->add_listener((messaging), (mid), (iid), (version), (callback), (client_data)))

#define	EXTIT_IF_MESSAGING_BIND(messaging, mid, iid, version)	\
			((messaging)->ops->bind((messaging), (mid), (iid), (version)))

#define	EXTIT_IF_MESSAGING_BOUND_ADD_LISTENER(messaging, bound, callback, client_data)	\
			((messaging)->ops->bound_add_listener((messaging), (bound), (callback), (client_data)))

#define	EXTIT_IF_MESSAGING_BOUND_HAS_LISTENER(messaging, bound)	\
			((messaging)->ops->bound_has_listener((messaging), (bound)))

#define	EXTIT_IF_MESSAGING_BOUND_REMOVE_LISTENER(messaging, bound, callback, client_data)	\
			((messaging)->ops->bound_remove_listener((messaging), (bound), (callback), (client_data)))

#define	EXTIT_IF_MESSAGING_BOUND_SEND(messaging, bound, data)	\
			((messaging)->ops->bound_send((messaging), (bound), (data)))

#define	EXTIT_IF_MESSAGING_HAS_LISTENER(messaging, mid, iid, version)	\
			((messaging)->ops->has_listener((messaging), (mid), (iid), (version)))

#define	EXTIT_IF_MESSAGING_REMOVE_LISTENER(messaging, mid, iid, version, callback, client_data)	\
			((messaging)->ops->remove_listener((messaging), (mid), (iid), (version), (callback), (client_data)))

#define	EXTIT_IF_MESSAGING_REMOVE_LISTENER_BY_ID(messaging, id)	\
			((messaging)->ops->remove_listener_by_id((messaging), (id)))

#define	EXTIT_IF_MESSAGING_SEND(messaging, mid, iid, version, data)	\
			((messaging)->ops->send((messaging), (mid), (iid), (version), (data)))

#define	EXTIT_IF_MESSAGING_UNBIND(messaging, bound)	\
			((messaging)->ops->unbind((messaging), (bound)))

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__messaging_impl_h */
