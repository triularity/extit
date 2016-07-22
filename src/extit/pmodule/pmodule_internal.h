/*
 * @(#) pmodule_internal.h
 *
 * Plugin module internals.
 *
 * Copyright (c) 2014-2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__pmodule_internal_h
#define	__pmodule_internal_h

#include <iv/base.h>
#include <extit/util.h>
#include <extit/container.h>
#include <extit/pmodule.h>
#include <extit/plugin_spi.h>

#ifdef	_WIN32
#include <windows.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

struct _extit_module
{
	extit_refcount_t			refcount;
	unsigned int				flags;
	iv_version_t				abi_version;
	const extit_container_t *		container;
	const extit_spi_descriptor_base_t *	descriptor;

#ifdef	_WIN32
	HMODULE					handle;
#else
	void *					handle;
#endif
};


struct _extit_plugin
{
	extit_module_t *			module;
	unsigned int				flags;
	void *					spi_ctx;
};


EXTIT_EXPORT
extit_status_t		EXTIT_DECL
			_extit_module_unload(
				extit_module_t *module);

#ifdef	__cplusplus
}
#endif

#endif	/* !__pmodule_internal_h */
