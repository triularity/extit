/*
 * @(#) extit/pmodule_impl.h
 *
 * Plugin module implementation.
 *
 * Copyright (c) 2014-2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__pmodule_impl_h
#define	__extit__pmodule_impl_h

#include <stdint.h>

#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _extit_pmodule_descriptor_1_0
					extit_pmodule_descriptor_1_0_t;

typedef struct _extit_pmodule_ops_1_0
{
	extit_status_t		(EXTIT_DECL *op_probe)(
					extit_pmodule_descriptor_1_0_t *descr,
					extit_container_t *container);

	extit_status_t		(EXTIT_DECL *op_create)(
					extit_pmodule_descriptor_1_0_t *descr,
					extit_container_t *container,
					void **ctx_ptr);

	extit_status_t		(EXTIT_DECL *op_destroy)(
					extit_pmodule_descriptor_1_0_t *descr,
					extit_container_t *container,
					void *ctx);

	void *			(EXTIT_DECL *op_get_interface)(
					extit_pmodule_descriptor_1_0_t *descr,
					extit_container_t *container,
					void *ctx,
					const char *iid,
					iv_version_t version);

	iv_version_t		(EXTIT_DECL *op_query_interface)(
					extit_pmodule_descriptor_1_0_t *descr,
					extit_container_t *container,
					void *ctx,
					const char *iid,
					iv_version_t base_version);

	extit_status_t		(EXTIT_DECL *op_unload)(
					extit_pmodule_descriptor_1_0_t *descr,
					extit_container_t *container);
} extit_pmodule_ops_1_0_t;


/*
 * Magic Value for API Descriptor (aka "ExIt")
 */
#define	EXTIT_PMODULE_MAGIC		0x45784974L

/*
 * Plugin Descriptor (base)
 */
typedef struct _extit_pmodule_descriptor_base
{
	uint32_t			magic;		/* EXTIT_PMODULE_MAGIC*/
	iv_version_t			extit_version;	/* EXTIT_ABI_x_x */
} extit_pmodule_descriptor_base_t;

/*
 * Plugin Descriptor (v1.0)
 */
struct _extit_pmodule_descriptor_1_0
{
	/* base */
	uint32_t			magic;		/* EXTIT_PMODULE_MAGIC*/
	iv_version_t			extit_version;	/* EXTIT_ABI_1_0 */

	/* 1.0 */
	const char *			id;		/* Unique ID */
	uint32_t			id_version;	/* Unique ID Version */
	const char *			name;
	const char *			version;

	extit_pmodule_ops_1_0_t *	ops;
};


/*
 * ABI Version
 */
#if	EXTIT_ABI_TARGET == EXTIT_ABI_1_0
typedef	extit_pmodule_descriptor_1_0_t	extit_pmodule_descriptor_t;
#else
#error	Unsupported EXTIT_ABI_TARGET version
#endif


/*
 * Plugin Descriptor Declaration
 */
#define	EXTIT_PMODULE_DESCRIPTOR_NAME	_extit_PMODULE_DESCRIPTOR
#define	EXTIT_PMODULE_DESCRIPTOR_SYMBOL	"_extit_PMODULE_DESCRIPTOR"

EXTIT_EXPORT
extern extit_pmodule_descriptor_t	EXTIT_PMODULE_DESCRIPTOR_NAME;

#define	EXTIT_DECLARE_PMODULE(id, id_version, name, version, ops) \
		EXTIT_EXPORT \
		extit_pmodule_descriptor_t EXTIT_PMODULE_DESCRIPTOR_NAME = \
		{ \
			EXTIT_PMODULE_MAGIC, \
			EXTIT_ABI_TARGET, \
			id, \
			id_version, \
			name, \
			version, \
			ops \
		}; \

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__pmodule_impl_h */
