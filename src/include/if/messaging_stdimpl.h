/*
 * @(#) if/messaging_stdimpl.h
 *
 * Message interface standard implementation.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__messaging_stdimpl_h
#define	__if__messaging_stdimpl_h

#include <stddef.h>

#include <extit/base.h>
#include <if/messaging.h>
#include <if/messaging_impl.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_messaging_stdimpl_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


LIBAPI
extern if_messaging_ops_1_0_t		if_messaging_stdimpl_ops_1_0;


#if	IF_MESSAGING_ABI_TARGET == IF_MESSAGING_ABI_1_0
#define	if_messaging_stdimpl_ops	if_messaging_stdimpl_ops_1_0
#else
#error	Unsupported IF_MESSAGING_ABI_TARGET version
#endif


LIBAPI
if_messaging_listener_id_t
			EXTIT_DECL
			if_messaging_add_listener_stdimpl(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				if_messaging_listener_t cb,
				void *client_data);

LIBAPI
if_messaging_bound_t *
			EXTIT_DECL
			if_messaging_bind_stdimpl(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

LIBAPI
if_messaging_listener_id_t
			EXTIT_DECL
			if_messaging_bound_add_listener_stdimpl(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
				if_messaging_listener_t cb,
				void *client_data);

LIBAPI
extit_bool_t
			EXTIT_DECL
			if_messaging_bound_has_listener_stdimpl(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_bound_remove_listener_stdimpl(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
				if_messaging_listener_t cb,
				void *client_data);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_bound_send_stdimpl(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
        			void *data);

LIBAPI
extit_bool_t
			EXTIT_DECL
			if_messaging_has_listener_stdimpl(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_remove_listener_stdimpl(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				if_messaging_listener_t cb,
				void *client_data);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_remove_listener_by_id_stdimpl(
				if_messaging_t *messaging,
				if_messaging_listener_id_t id);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_send_stdimpl(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
        			void *data);

LIBAPI
void				if_messaging_stdimpl_cleanup(
					if_messaging_t *messaging);

LIBAPI
if_messaging_t *
			EXTIT_DECL
			if_messaging_stdimpl_create(void);

LIBAPI
void			EXTIT_DECL
			if_messaging_stdimpl_destroy(
				if_messaging_t *messaging);

LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_unbind_stdimpl(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__messaging_stdimpl_h */
