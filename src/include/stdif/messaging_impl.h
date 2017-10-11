/*
 * @(#) stdif/messaging_impl.h
 *
 * Messaging Interface - implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__messaging_impl_h
#define	__stdif__messaging_impl_h

#include <iv/base.h>
#include <extit/base.h>
#include <stdif/messaging.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Messaging operations (v1.0 component)
 */
typedef struct _stdif_messaging_ops_comp_1_0
{
	stdif_messaging_listener_id_t
				(EXTIT_DECL *op_add_listener)(
					stdif_messaging_1_0_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version,
					stdif_messaging_listener_t cb,
					void *client_data);

	extit_status_t		(EXTIT_DECL *op_remove_listener)(
					stdif_messaging_1_0_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version,
					stdif_messaging_listener_t cb,
					void *client_data);

	extit_status_t		(EXTIT_DECL *op_remove_listener_by_id)(
					stdif_messaging_1_0_t *messaging,
					stdif_messaging_listener_id_t id);

	extit_bool_t		(EXTIT_DECL *op_has_listener)(
					stdif_messaging_1_0_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version);

	extit_status_t		(EXTIT_DECL *op_send)(
					stdif_messaging_1_0_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version,
					void *data);

	stdif_messaging_bound_t *
				(EXTIT_DECL *op_bind)(
					stdif_messaging_1_0_t *messaging,
					const char *mid,
					const char *iid,
					iv_version_t version);

	extit_status_t		(EXTIT_DECL *op_unbind)(
					stdif_messaging_1_0_t *messaging,
					stdif_messaging_bound_t *bound);

	stdif_messaging_listener_id_t
				(EXTIT_DECL *op_bound_add_listener)(
					stdif_messaging_1_0_t *messaging,
					stdif_messaging_bound_t *bound,
					stdif_messaging_listener_t cb,
					void *client_data);

	extit_status_t		(EXTIT_DECL *op_bound_remove_listener)(
					stdif_messaging_1_0_t *messaging,
					stdif_messaging_bound_t *bound,
					stdif_messaging_listener_t cb,
					void *client_data);

	extit_bool_t		(EXTIT_DECL *op_bound_has_listener)(
					stdif_messaging_1_0_t *messaging,
					stdif_messaging_bound_t *bound);

	extit_status_t		(EXTIT_DECL *op_bound_send)(
					stdif_messaging_1_0_t *messaging,
					stdif_messaging_bound_t *bound,
					void *data);
} stdif_messaging_ops_comp_1_0_t;


/*
 * Messaging operations (v1.0)
 */
typedef struct _stdif_messaging_ops_1_0
{
	stdif_messaging_ops_comp_1_0_t	v0;		/* [1].0 component */
} stdif_messaging_ops_1_0_t;


/*
 * Messaging (base)
 */
struct _stdif_messaging
{
	iv_version_t			version;
};


/*
 * Messaging (v1.0)
 */
struct _stdif_messaging_1_0
{
	/* base */
	iv_version_t			version;	/* 1.0+ */

	/* 1.0+ */
	stdif_messaging_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__stdif__messaging_impl_h */
