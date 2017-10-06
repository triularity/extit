/*
 * @(#) extit/pmodule/Plugin.cc
 *
 * C++ wrappers for extit_plugin_*() API.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string>
#include <stdexcept>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/pmodule.h>
#include <extit/pmodule_cxx.h>


namespace ExtIt
{

Plugin::Plugin
(
	extit_plugin_t *plugin,
	Module *module
)
{
	this->plugin = plugin;
	this->module = module;
}


Plugin::~Plugin()
{
	if(plugin != NULL)
		extit_plugin_destroy(plugin);
}


extit_status_t
Plugin::destroy
(
)
{
	extit_status_t	status;


	if(plugin == NULL)
		throw new std::logic_error("Plugin not valid");

	status = extit_plugin_destroy(plugin);

	if(status == EXTIT_STATUS_OK)
		plugin = NULL;

	return status;
}


void *
Plugin::getContext
(
)
{
	if(plugin == NULL)
		throw new std::logic_error("Plugin not valid");

	return extit_plugin_get_context(plugin);
}


void *
Plugin::getInterface
(
	const char *name,
	iv_version_t version
)
{
	if(plugin == NULL)
		throw new std::logic_error("Plugin not valid");

	return extit_plugin_get_interface(plugin, name, version);
}


void *
Plugin::getInterface
(
	const std::string & name,
	iv_version_t version
)
{
	return getInterface(name.c_str(), version);
}


unsigned int
Plugin::getFlags
(
)
{
	if(plugin == NULL)
		throw new std::logic_error("Plugin not valid");

	return extit_plugin_get_flags(plugin);
}


Module *
Plugin::getModule
(
)
{
	return module;
}


extit_plugin_t *
Plugin::get_struct
(
)
{
	return plugin;
}


iv_version_t
Plugin::queryInterface
(
	const char *name,
	iv_version_t base_version
)
{
	if(plugin == NULL)
		throw new std::logic_error("Plugin not valid");

	return extit_plugin_query_interface(plugin, name, base_version);
}


iv_version_t
Plugin::queryInterface
(
	const std::string & name,
	iv_version_t base_version
)
{
	return queryInterface(name.c_str(), base_version);
}


void
Plugin::setFlags
(
	unsigned int flags
)
{
	if(plugin == NULL)
		throw new std::logic_error("Plugin not valid");

	extit_plugin_set_flags(plugin, flags);
}

// namespace ExtIt
}
