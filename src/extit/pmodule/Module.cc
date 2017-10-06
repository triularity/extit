/*
 * @(#) extit/pmodule/Module.cc
 *
 * C++ wrappers for extit_module_*() API.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string>
#include <stdexcept>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container.h>
#include <extit/pmodule.h>
#include <extit/pmodule_cxx.h>


namespace
{
extern "C"
{
EXTIT_DECL
extit_status_t
proxy_callback(extit_module_t *module, void *client_data);

EXTIT_DECL
extit_bool_t
proxy_fnfilter(const char *basename, size_t length, void *client_data);

#ifdef	EXTIT_WCHAR
EXTIT_DECL
extit_bool_t
proxy_fnfilter_wc(const wchar_t *basename, size_t length, void *client_data);
#endif
} // extern "C"
} // namespace


namespace ExtIt
{

Module::Module
(
	extit_module_t *module
)
{
	if(module == NULL)
		throw std::invalid_argument("Module is NULL");

	this->module = module;

	id = NULL;
	name = NULL;
	version = NULL;
}


Module::Module
(
	Container *container,
	const void *descriptor,
	unsigned int flags
)
{
	module = extit_module_bind(
		container->get_struct(),
		descriptor,
		flags);

	if(module == NULL)
		throw std::logic_error("Module bind failed");

	id = NULL;
	name = NULL;
	version = NULL;
}


Module::Module
(
	Container *container,
	const char *path,
	unsigned int flags
)
{
	init_load(container, path, flags);
}


Module::Module
(
	Container *container,
	const std::string & path,
	unsigned int flags
)
{
	init_load(container, path.c_str(), flags);
}


#ifdef	EXTIT_WCHAR
Module::Module
(
	Container *container,
	const wchar_t *path,
	unsigned int flags
)
{
	init_load(container, path, flags);
}


Module::Module
(
	Container *container,
	const std::wstring & path,
	unsigned int flags
)
{
	init_load(container, path.c_str(), flags);
}
#endif	/* EXTIT_WCHAR */


Module::~Module()
{
	if(id != NULL)
		delete id;

	if(name != NULL)
		delete name;

	if(version != NULL)
		delete version;

	if(module != NULL)
		extit_module_release(module);
}


Plugin *
Module::createPlugin
(
)
{
	extit_plugin_t *	plugin;


	if(module == NULL)
		throw new std::logic_error("Module not valid");

	if((plugin = extit_module_create_plugin(module)) == NULL)
		return NULL;

	return new Plugin(plugin, this);
}


iv_version_t
Module::getABIVersion
(
)
{
	if(module == NULL)
		throw new std::logic_error("Module not valid");

	return extit_module_get_abi_version(module);
}


iv_version_t
Module::getEffectiveABIVersion
(
)
{
	if(module == NULL)
		throw new std::logic_error("Module not valid");

	return extit_module_get_effective_abi_version(module);
}


unsigned int
Module::getFlags
(
)
{
	if(module == NULL)
		throw new std::logic_error("Module not valid");

	return extit_module_get_flags(module);
}


extit_func_t
Module::getFunction
(
	const char *name
)
{
	if(module == NULL)
		throw new std::logic_error("Module not valid");

	return extit_module_get_function(module, name);
}


extit_func_t
Module::getFunction
(
	const std::string & name
)
{
	return getFunction(name.c_str());
}


const std::string *
Module::getId
(
)
{
	const char *	c_id;


	if(module == NULL)
		throw new std::logic_error("Module not valid");

	if(id == NULL)
	{
		if((c_id = extit_module_get_id(module)) == NULL)
			throw new std::logic_error("Module id is NULL");

		id = new std::string(c_id);
	}

	return id;
}


uint32_t
Module::getIdVersion
(
)
{
	if(module == NULL)
		throw new std::logic_error("Module not valid");

	return extit_module_get_id_version(module);
}


const std::string *
Module::getName
(
)
{
	const char *	c_name;


	if(module == NULL)
		throw new std::logic_error("Module not valid");

	if(name == NULL)
	{
		if((c_name = extit_module_get_name(module)) == NULL)
			throw new std::logic_error("Module name is NULL");

		name = new std::string(c_name);
	}

	return name;
}


void *
Module::getSymbol
(
	const char *name
)
{
	if(module == NULL)
		throw new std::logic_error("Module not valid");

	return extit_module_get_symbol(module, name);
}


void *
Module::getSymbol
(
	const std::string & name
)
{
	return getSymbol(name.c_str());
}


const std::string *
Module::getVersion
(
)
{
	const char *	c_version;


	if(module == NULL)
		throw new std::logic_error("Module not valid");

	if(version == NULL)
	{
		if((c_version = extit_module_get_version(module)) == NULL)
			throw new std::logic_error("Module version is NULL");

		version = new std::string(c_version);
	}

	return version;
}


void
Module::init_load
(
	Container *container,
	const char *path,
	unsigned int flags
)
{
	module = extit_module_load(
		container->get_struct(),
		path,
		flags);

	if(module == NULL)
		throw std::logic_error("Module load failed");

	id = NULL;
	name = NULL;
	version = NULL;
}


#ifdef	EXTIT_WCHAR
void
Module::init_load
(
	Container *container,
	const wchar_t *path,
	unsigned int flags
)
{
	module = extit_module_load_wc(
		container->get_struct(),
		path,
		flags);

	if(module == NULL)
		throw std::logic_error("Module load failed");

	id = NULL;
	name = NULL;
	version = NULL;
}
#endif	/* EXTIT_WCHAR */


extit_status_t
Module::release
(

)
{
	extit_status_t	status;


	if(module == NULL)
		throw new std::logic_error("Module not valid");

	status = extit_module_release(module);

	if(status == EXTIT_STATUS_OK)
		module = NULL;

	return status;
}


extit_status_t
Module::scan
(
	Container *container,
	const char *directory,
	extit_module_scan_callback_t callback,
	void *callback_client_data,
	extit_module_scan_fnfilter_t fnfilter,
	void *fnfilter_client_data,
	unsigned int flags
)
{
	return extit_module_scan(
		container->get_struct(),
		directory,
		callback,
		callback_client_data,
		fnfilter,
		fnfilter_client_data,
		flags);
}


struct callback_object_info
{
	ModuleScanCallback	callback;
	void *			client_data;
};


namespace
{
extern "C"
EXTIT_DECL
extit_status_t
proxy_callback(extit_module_t *module, void *client_data)
{
	struct callback_object_info *	info;
	Module *			module_obj;
	extit_status_t			status;


	info = (struct callback_object_info *) client_data;

	module_obj = new Module(module);

	try
	{
		status = info->callback(module_obj, info->client_data);
	}
	catch(...)
	{
		delete module_obj;

		return EXTIT_STATUS_FAIL;
	}

	if(status != EXTIT_STATUS_OK)
		delete module_obj;

	return status;
}
}


struct fnfilter_string_info
{
	ModuleScanStringFilter	fnfilter;
	void *			client_data;
};


namespace
{
extern "C"
EXTIT_DECL
extit_bool_t
proxy_fnfilter(const char *basename, size_t length, void *client_data)
{
	std::string			str(basename, length);
	struct fnfilter_string_info *	info;


	info = (struct fnfilter_string_info *) client_data;

	return (extit_bool_t) info->fnfilter(str, info->client_data);
}
}


extit_status_t
Module::scan
(
	Container * container,
	const std::string & directory,
	ModuleScanCallback callback,
	void *callback_client_data,
	ModuleScanStringFilter fnfilter,
	void *fnfilter_client_data,
	unsigned int flags
)
{
	struct callback_object_info	callback_info;
	struct fnfilter_string_info	fnfilter_info;


	callback_info.callback = callback;
	callback_info.client_data = callback_client_data;

	fnfilter_info.fnfilter = fnfilter;
	fnfilter_info.client_data = fnfilter_client_data;

	return extit_module_scan(
		container->get_struct(),
		directory.c_str(),
		proxy_callback,
		&callback_info,
		proxy_fnfilter,
		&fnfilter_info,
		flags);
}


#ifdef	EXTIT_WCHAR
extit_status_t
Module::scan
(
	Container *container,
	const wchar_t *directory,
	extit_module_scan_callback_t callback,
	void *callback_client_data,
	extit_module_scan_fnfilter_wc_t fnfilter,
	void *fnfilter_client_data,
	unsigned int flags
)
{
	return extit_module_scan_wc(
		container->get_struct(),
		directory,
		callback,
		callback_client_data,
		fnfilter,
		fnfilter_client_data,
		flags);
}


struct fnfilter_wstring_info
{
	ModuleScanWStringFilter	fnfilter;
	void *			client_data;
};


namespace
{
extern "C"
EXTIT_DECL
extit_bool_t
proxy_fnfilter_wc(const wchar_t *basename, size_t length, void *client_data)
{
	std::wstring			str(basename, length);
	struct fnfilter_wstring_info *	info;


	info = (struct fnfilter_wstring_info *) client_data;

	return (extit_bool_t) info->fnfilter(str, info->client_data);
}
}


extit_status_t
Module::scan
(
	Container * container,
	const std::wstring & directory,
	ModuleScanCallback callback,
	void *callback_client_data,
	ModuleScanWStringFilter fnfilter,
	void *fnfilter_client_data,
	unsigned int flags
)
{
	struct callback_object_info	callback_info;
	struct fnfilter_wstring_info	fnfilter_info;


	callback_info.callback = callback;
	callback_info.client_data = callback_client_data;

	fnfilter_info.fnfilter = fnfilter;
	fnfilter_info.client_data = fnfilter_client_data;

	return extit_module_scan_wc(
		container->get_struct(),
		directory.c_str(),
		proxy_callback,
		&callback_info,
		proxy_fnfilter_wc,
		&fnfilter_info,
		flags);
}
#endif	/* EXTIT_WCHAR */


void
Module::setFlags
(
	unsigned int flags
)
{
	if(module == NULL)
		throw new std::logic_error("Module not valid");

	extit_module_set_flags(module, flags);
}

// namespace ExtIt
}
