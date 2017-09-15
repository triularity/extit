/*
 * @(#) extit/container_impl.h
 *
 * ExtIt container implementation.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__container_impl_h
#define	__extit__container_impl_h

#include <stddef.h>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Container operations (1.0 component)
 */
typedef struct _extit_container_ops_comp_1_0
{
	/*
	 * Get a raw named symbol
	 */
	void *			(EXTIT_DECL *op_get_symbol)(
					const extit_container_1_0_t *container,
					const char *name);

	/*
	 * Get a raw named function
	 */
	extit_func_t		(EXTIT_DECL *op_get_function)(
					const extit_container_1_0_t *container,
					const char *name);

	/*
	 * Get a named interface object by version
	 */
	void *			(EXTIT_DECL *op_get_interface)(
					const extit_container_1_0_t *container,
					const char *iid,
					iv_version_t version);

	/*
	 * Query the supported version of an interface
	 */
	iv_version_t		(EXTIT_DECL *op_query_interface)(
					const extit_container_1_0_t *container,
					const char *iid,
					iv_version_t base_version);

	/*
	 * Log a simple message
	 */
	void			(EXTIT_DECL *op_log)(
					const extit_container_1_0_t *container,
					const char *message);
} extit_container_ops_comp_1_0_t;


/*
 * Container operations (1.0)
 */
typedef struct _extit_container_ops_1_0
{
	extit_container_ops_comp_1_0_t	v0;		/* [1].0 component */
} extit_container_ops_1_0_t;


/*
 * Container (base)
 */
struct _extit_container
{
	iv_version_t			version;	/* EXTIT_ABI_x_x */
};


/*
 * Container (1.0)
 */
struct _extit_container_1_0
{
	/* base */
	iv_version_t			version;	/* EXTIT_ABI_1_0 */

	/* 1.0+ */
	extit_container_ops_1_0_t *	ops;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__container_impl_h */
