/*
 * @(#) if/messaging_stdimpl.h
 *
 * Message Interface - standard implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__messaging_stdimpl_h
#define	__if__messaging_stdimpl_h

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>

#ifdef	if_messaging_stdimpl_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Messaging (v1.0)
 */
LIBAPI
extern if_messaging_ops_1_0_t		if_messaging_stdimpl_ops__1_0;

LIBAPI
if_messaging_listener_id_t
			EXTIT_DECL
			if_messaging_stdimpl_add_listener__1_0(
				if_messaging_1_0_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				if_messaging_listener_t cb,
				void *client_data);

LIBAPI
if_messaging_bound_t *	EXTIT_DECL
			if_messaging_stdimpl_bind__1_0(
				if_messaging_1_0_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

LIBAPI
if_messaging_listener_id_t
			EXTIT_DECL
			if_messaging_stdimpl_bound_add_listener__1_0(
				if_messaging_1_0_t *messaging,
				if_messaging_bound_t *bound,
				if_messaging_listener_t cb,
				void *client_data);

LIBAPI
extit_bool_t		EXTIT_DECL
			if_messaging_stdimpl_bound_has_listener__1_0(
				if_messaging_1_0_t *messaging,
				if_messaging_bound_t *bound);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_stdimpl_bound_remove_listener__1_0(
				if_messaging_1_0_t *messaging,
				if_messaging_bound_t *bound,
				if_messaging_listener_t cb,
				void *client_data);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_stdimpl_bound_send__1_0(
				if_messaging_1_0_t *messaging,
				if_messaging_bound_t *bound,
        			void *data);

LIBAPI
extit_bool_t		EXTIT_DECL
			if_messaging_stdimpl_has_listener__1_0(
				if_messaging_1_0_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_stdimpl_remove_listener__1_0(
				if_messaging_1_0_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				if_messaging_listener_t cb,
				void *client_data);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_stdimpl_remove_listener_by_id__1_0(
				if_messaging_1_0_t *messaging,
				if_messaging_listener_id_t id);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_stdimpl_send__1_0(
				if_messaging_1_0_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
        			void *data);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_stdimpl_unbind__1_0(
				if_messaging_1_0_t *messaging,
				if_messaging_bound_t *bound);


/*
 * Management
 */
LIBAPI
void			if_messaging_stdimpl_cleanup(
				if_messaging_t *messaging);

LIBAPI
if_messaging_t *	EXTIT_DECL
			if_messaging_stdimpl_create(
				iv_version_t version);

LIBAPI
void			EXTIT_DECL
			if_messaging_stdimpl_destroy(
				if_messaging_t *messaging);

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__if__messaging_stdimpl_h */
