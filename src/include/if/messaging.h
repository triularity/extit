/*
 * @(#) if/messaging.h
 *
 * Messaging Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__messaging_h
#define	__if__messaging_h

#include <stdlib.h>
#include <stdint.h>

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_messaging_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


/*
 * Messaging Interface ID
 */
#define IF_MESSAGING_IID		"{25eb0d84-38ee-11e6-9660-406186e454c1}/messaging"

/*
 * Messaging (v1.0)
 */
#define IF_MESSAGING_ABI_1_0		IV_VERSION(1,0)
typedef struct _if_messaging_1_0	if_messaging_1_0_t;

/*
 * A bound interface message
 */
typedef struct _if_messaging_bound 	if_messaging_bound_t;

#define	IF_MESSAGING_BOUND_NONE		((if_messaging_bound_t *) NULL)

/*
 * Message listener callback
 */
typedef void				(*if_messaging_listener_t)(
						const char *mid,
						void *data,
						void *client_data);

/*
 * A registered listener ID
 */
typedef uint32_t			if_messaging_listener_id_t;

#define	IF_MESSAGING_LISTENER_ID_NONE	0


/*
 * ABI Version
 */
#ifndef	IF_MESSAGING_ABI_TARGET
#define	IF_MESSAGING_ABI_TARGET		IF_MESSAGING_ABI_1_0
#endif

#if	IF_MESSAGING_ABI_TARGET == IF_MESSAGING_ABI_1_0
#define	if_messaging_t			if_messaging_1_0_t
#else
#error	Unsupported IF_MESSAGING_ABI_TARGET version
#endif


/*
 * Public API (v1.0)
 */
LIBAPI
if_messaging_listener_id_t
			EXTIT_DECL
			if_messaging_add_listener(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				if_messaging_listener_t callback,
				void *client_data);

LIBAPI
if_messaging_bound_t *
			EXTIT_DECL
			if_messaging_bind(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

LIBAPI
if_messaging_listener_id_t
			EXTIT_DECL
			if_messaging_bound_add_listener(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
				if_messaging_listener_t callback,
				void *client_data);

LIBAPI
extit_bool_t		EXTIT_DECL
			if_messaging_bound_has_listener(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_bound_remove_listener(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
				if_messaging_listener_t callback,
				void *client_data);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_bound_send(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
				void *data);

LIBAPI
extit_bool_t		EXTIT_DECL
			if_messaging_has_listener(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_remove_listener(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				if_messaging_listener_t callback,
				void *client_data);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_remove_listener_by_id(
				if_messaging_t *messaging,
				if_messaging_listener_id_t id);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_send(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				void *data);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_unbind(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__messaging_h */
