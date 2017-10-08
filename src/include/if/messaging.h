/*
 * @(#) if/messaging.h
 *
 * Messaging Interface.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__messaging_h
#define	__if__messaging_h

#include <stdlib.h>
#include <stdint.h>

#include <iv/base.h>
#include <extit/base.h>

#ifdef	if_messaging_EXPORTS
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
 * Messaging Interface ID
 */
#define IF_MESSAGING_IID		"{c1c017b1-44d5-11e6-9660-406186e454c1}/messaging"


/*
 * Messaging (base)
 */
typedef struct _if_messaging		if_messaging_t;


/*
 * Messaging (v1.0)
 */
#define IF_MESSAGING_ABI_1_0		IV_VERSION(1,0)

typedef struct _if_messaging_1_0	if_messaging_1_0_t;

LIBAPI
if_messaging_listener_id_t
			EXTIT_DECL
			if_messaging_add_listener__1_0(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				if_messaging_listener_t callback,
				void *client_data);

LIBAPI
if_messaging_bound_t *	EXTIT_DECL
			if_messaging_bind__1_0(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

LIBAPI
if_messaging_listener_id_t
			EXTIT_DECL
			if_messaging_bound_add_listener__1_0(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
				if_messaging_listener_t callback,
				void *client_data);

LIBAPI
extit_bool_t		EXTIT_DECL
			if_messaging_bound_has_listener__1_0(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_bound_remove_listener__1_0(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
				if_messaging_listener_t callback,
				void *client_data);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_bound_send__1_0(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound,
				void *data);

LIBAPI
extit_bool_t		EXTIT_DECL
			if_messaging_has_listener__1_0(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_remove_listener__1_0(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				if_messaging_listener_t callback,
				void *client_data);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_remove_listener_by_id__1_0(
				if_messaging_t *messaging,
				if_messaging_listener_id_t id);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_send__1_0(
				if_messaging_t *messaging,
				const char *mid,
				const char *iid,
				iv_version_t version,
				void *data);

LIBAPI
extit_status_t		EXTIT_DECL
			if_messaging_unbind__1_0(
				if_messaging_t *messaging,
				if_messaging_bound_t *bound);


/*
 * ABI Version
 */
#ifndef	IF_MESSAGING_ABI_TARGET
#define	IF_MESSAGING_ABI_TARGET		IF_MESSAGING_ABI_1_0
#endif

#if	IV_VERSION_MAJOR(IF_MESSAGING_ABI_TARGET) == 1
#define	if_messaging_add_listener	if_messaging_add_listener__1_0
#define	if_messaging_bind		if_messaging_bind__1_0
#define	if_messaging_bound_add_listener	if_messaging_bound_add_listener__1_0
#define	if_messaging_bound_has_listener	if_messaging_bound_has_listener__1_0

#define	if_messaging_bound_remove_listener \
					if_messaging_bound_remove_listener__1_0

#define	if_messaging_bound_send		if_messaging_bound_send__1_0
#define	if_messaging_has_listener	if_messaging_has_listener__1_0
#define	if_messaging_remove_listener	if_messaging_remove_listener__1_0

#define	if_messaging_remove_listener_by_id \
					if_messaging_remove_listener_by_id__1_0

#define	if_messaging_send		if_messaging_send__1_0
#define	if_messaging_unbind		if_messaging_unbind__1_0
#endif	/* IV_VERSION_MAJOR(IF_MESSAGING_ABI_TARGET) == 1 */

#ifdef	__cplusplus
}
#endif

#undef	LIBAPI

#endif	/* !__if__messaging_h */
