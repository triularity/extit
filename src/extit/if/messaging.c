/*
 * @(#) extit/if/messaging.c
 *
 * Messaging Interface client API wrappers.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/base.h>
#include <extit/if/messaging_impl.h>

#ifdef	EXTIT_PARANOID
#include <iv/util.h>
#endif


EXTIT_EXPORT
extit_if_messaging_listener_id_t
EXTIT_DECL
extit_if_messaging_addListener
(
	extit_if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	extit_if_messaging_listener_t callback,
	void *client_data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_IF_MESSAGING_LISTENER_ID_NONE;
#endif

	return EXTIT_IF_MESSAGING_ADD_LISTENER(
		messaging, mid, iid, version, callback, client_data);
}


EXTIT_EXPORT
extit_if_messaging_bound_t
EXTIT_DECL
extit_if_messaging_bind
(
	extit_if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_IF_MESSAGING_BOUND_NONE;
#endif

	return EXTIT_IF_MESSAGING_BIND(messaging, mid, iid, version);
}


EXTIT_EXPORT
extit_if_messaging_listener_id_t
EXTIT_DECL
extit_if_messaging_boundAddListener
(
	extit_if_messaging_t *messaging,
	extit_if_messaging_bound_t bound,
	extit_if_messaging_listener_t callback,
	void *client_data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_IF_MESSAGING_LISTENER_ID_NONE;
#endif

	return EXTIT_IF_MESSAGING_BOUND_ADD_LISTENER(
		messaging, bound, callback, client_data);
}


EXTIT_EXPORT
extit_bool_t
EXTIT_DECL
extit_if_messaging_boundHasListener
(
	extit_if_messaging_t *messaging,
	extit_if_messaging_bound_t bound
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_FALSE;
#endif

	return EXTIT_IF_MESSAGING_BOUND_HAS_LISTENER(messaging, bound);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_messaging_boundRemoveListener
(
	extit_if_messaging_t *messaging,
	extit_if_messaging_bound_t bound,
	extit_if_messaging_listener_t callback,
	void *client_data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IF_MESSAGING_BOUND_REMOVE_LISTENER(
		messaging, bound, callback, client_data);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_messaging_boundSend
(
	extit_if_messaging_t *messaging,
	extit_if_messaging_bound_t bound,
	void *data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IF_MESSAGING_BOUND_SEND(messaging, bound, data);
}


EXTIT_EXPORT
extit_bool_t
EXTIT_DECL
extit_if_messaging_hasListener
(
	extit_if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_FALSE;
#endif

	return EXTIT_IF_MESSAGING_HAS_LISTENER(messaging, mid, iid, version);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_messaging_removeListener
(
	extit_if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	extit_if_messaging_listener_t callback,
	void *client_data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IF_MESSAGING_REMOVE_LISTENER(
		messaging, mid, iid, version, callback, client_data);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_messaging_removeListenerById
(
	extit_if_messaging_t *messaging,
	extit_if_messaging_listener_id_t id
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IF_MESSAGING_REMOVE_LISTENER_BY_ID(messaging, id);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_messaging_send
(
	extit_if_messaging_t *messaging,
	const char *mid,
	const char *iid,
	iv_version_t version,
	void *data
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IF_MESSAGING_SEND(messaging, mid, iid, version, data);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_if_messaging_unbind
(
	extit_if_messaging_t *messaging,
	extit_if_messaging_bound_t bound
)
{
#ifdef	EXTIT_PARANOID
	if(!iv_matches(messaging->version, EXTIT_IF_MESSAGING_VERSION_1_0))
		return EXTIT_STATUS_UNSUPPORTED;
#endif

	return EXTIT_IF_MESSAGING_UNBIND(messaging, bound);
}
