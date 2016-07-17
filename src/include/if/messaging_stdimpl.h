/*
 * @(#) if/messaging_stdimpl.h
 *
 * Configurable Interface standard implementation.
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
#define	IF_MESSAGING_STDIMPL_LIBAPI	EXTIT_EXPORT
#else
#define	IF_MESSAGING_STDIMPL_LIBAPI	EXTIT_IMPORT
#endif


IF_MESSAGING_STDIMPL_LIBAPI
extern if_messaging_ops_1_0_t		if_messaging_stdimpl_ops_1_0;


#if	IF_MESSAGING_ABI_TARGET == IF_MESSAGING_ABI_1_0
#define	if_messaging_stdimpl_ops	if_messaging_stdimpl_ops_1_0
#else
#error	Unsupported IF_MESSAGING_ABI_TARGET version
#endif


IF_MESSAGING_STDIMPL_LIBAPI
if_messaging_listener_id_t
			EXTIT_DECL
			if_messaging_add_listener_stdimpl(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				if_messaging_listener_t cb,
				void *client_data);

IF_MESSAGING_STDIMPL_LIBAPI
if_messaging_bound_t *
			EXTIT_DECL
			if_messaging_bind_stdimpl(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

IF_MESSAGING_STDIMPL_LIBAPI
if_messaging_listener_id_t
			EXTIT_DECL
			if_messaging_bound_add_listener_stdimpl(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
				if_messaging_listener_t cb,
				void *client_data);

IF_MESSAGING_STDIMPL_LIBAPI
extit_bool_t
			EXTIT_DECL
			if_messaging_bound_has_listener_stdimpl(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound);

IF_MESSAGING_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_bound_remove_listener_stdimpl(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
				if_messaging_listener_t cb,
				void *client_data);

IF_MESSAGING_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_bound_send_stdimpl(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
        			void *data);

IF_MESSAGING_STDIMPL_LIBAPI
extit_bool_t
			EXTIT_DECL
			if_messaging_has_listener_stdimpl(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

IF_MESSAGING_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_remove_listener_stdimpl(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				if_messaging_listener_t cb,
				void *client_data);

IF_MESSAGING_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_remove_listener_by_id_stdimpl(
				if_messaging_t *messaging,
				if_messaging_listener_id_t id);

IF_MESSAGING_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_send_stdimpl(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
        			void *data);

IF_MESSAGING_STDIMPL_LIBAPI
void				if_messaging_stdimpl_cleanup(
					if_messaging_t *messaging);

IF_MESSAGING_STDIMPL_LIBAPI
if_messaging_t *
			EXTIT_DECL
			if_messaging_stdimpl_create(void);

IF_MESSAGING_STDIMPL_LIBAPI
void			EXTIT_DECL
			if_messaging_stdimpl_destroy(
				if_messaging_t *messaging);

IF_MESSAGING_STDIMPL_LIBAPI
extit_status_t
			EXTIT_DECL
			if_messaging_unbind_stdimpl(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound);

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__messaging_stdimpl_h */
