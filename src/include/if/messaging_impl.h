/*
 * @(#) if/messaging_impl.h
 *
 * Messaging Interface implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__messaging_impl_h
#define	__if__messaging_impl_h

#include <iv/base.h>
#include <extit/base.h>
#include <if/messaging.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _if_messaging_ops_1_0
{
	if_messaging_listener_id_t
				(EXTIT_DECL *op_add_listener)(
					if_messaging_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version,
					if_messaging_listener_t cb,
					void *client_data);

	extit_status_t		(EXTIT_DECL *op_remove_listener)(
					if_messaging_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version,
					if_messaging_listener_t cb,
					void *client_data);

	extit_status_t		(EXTIT_DECL *op_remove_listener_by_id)(
					if_messaging_t *messaging,
					if_messaging_listener_id_t id);

	extit_bool_t		(EXTIT_DECL *op_has_listener)(
					if_messaging_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version);

	extit_status_t		(EXTIT_DECL *op_send)(
					if_messaging_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version,
					void *data);

	if_messaging_bound_t *
				(EXTIT_DECL *op_bind)(
					if_messaging_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version);

	extit_status_t		(EXTIT_DECL *op_unbind)(
					if_messaging_t *messaging,
					if_messaging_bound_t *bound);

	if_messaging_listener_id_t
				(EXTIT_DECL *op_bound_add_listener)(
					if_messaging_t *messaging,
					if_messaging_bound_t *bound,
					if_messaging_listener_t cb,
					void *client_data);

	extit_status_t		(EXTIT_DECL *op_bound_remove_listener)(
					if_messaging_t *messaging,
					if_messaging_bound_t *bound,
					if_messaging_listener_t cb,
					void *client_data);

	extit_bool_t		(EXTIT_DECL *op_bound_has_listener)(
					if_messaging_t *messaging,
					if_messaging_bound_t *bound);

	extit_status_t		(EXTIT_DECL *op_bound_send)(
					if_messaging_t *messaging,
					if_messaging_bound_t *bound,
					void *data);
} if_messaging_ops_1_0_t;


struct _if_messaging_1_0
{
	iv_version_t			version;	/* 1.0+ */
	if_messaging_ops_1_0_t *	ops;
};


#define	IF_MESSAGING_ADD_LISTENER(messaging, mid, iid, version, callback, client_data)	\
			((messaging)->ops->op_add_listener((messaging), (mid), (iid), (version), (callback), (client_data)))

#define	IF_MESSAGING_BIND(messaging, mid, iid, version)	\
			((messaging)->ops->op_bind((messaging), (mid), (iid), (version)))

#define	IF_MESSAGING_BOUND_ADD_LISTENER(messaging, bound, callback, client_data)	\
			((messaging)->ops->op_bound_add_listener((messaging), (bound), (callback), (client_data)))

#define	IF_MESSAGING_BOUND_HAS_LISTENER(messaging, bound)	\
			((messaging)->ops->op_bound_has_listener((messaging), (bound)))

#define	IF_MESSAGING_BOUND_REMOVE_LISTENER(messaging, bound, callback, client_data)	\
			((messaging)->ops->op_bound_remove_listener((messaging), (bound), (callback), (client_data)))

#define	IF_MESSAGING_BOUND_SEND(messaging, bound, data)	\
			((messaging)->ops->op_bound_send((messaging), (bound), (data)))

#define	IF_MESSAGING_HAS_LISTENER(messaging, mid, iid, version)	\
			((messaging)->ops->op_has_listener((messaging), (mid), (iid), (version)))

#define	IF_MESSAGING_REMOVE_LISTENER(messaging, mid, iid, version, callback, client_data)	\
			((messaging)->ops->op_remove_listener((messaging), (mid), (iid), (version), (callback), (client_data)))

#define	IF_MESSAGING_REMOVE_LISTENER_BY_ID(messaging, id)	\
			((messaging)->ops->op_remove_listener_by_id((messaging), (id)))

#define	IF_MESSAGING_SEND(messaging, mid, iid, version, data)	\
			((messaging)->ops->op_send((messaging), (mid), (iid), (version), (data)))

#define	IF_MESSAGING_UNBIND(messaging, bound)	\
			((messaging)->ops->op_unbind((messaging), (bound)))

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__messaging_impl_h */
