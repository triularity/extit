/*
 * @(#) container_impl.h
 *
 * Container API implementation.
 *
 * Copyright (c) 2014, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__container_impl_h
#define	__container_impl_h

#include <extit/container.h>
#include <extit/plugin_spi.h>

#ifdef	_WIN32
#include <windows.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

struct _extit_module
{
	unsigned int				refcount;
	unsigned int				flags;
	extit_iv_t				api_version;
	const extit_container_t *		container;
	const extit_spi_descriptor_base_t *	descriptor;

#ifdef	_WIN32
	HMODULE					handle;
#else
	void *					handle;
#endif
};


#define	EXTIT_INSTANCE_STATE_ACTIVE	0x00000001

struct _extit_plugin
{
	extit_module_t *			module;
	unsigned int				flags;
	void *					spi_ctx;
	unsigned int				state;
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__container_impl_h */
