/*
 * @(#) extit/pmodule_cxx.h
 *
 * ExtIt plugin module C++ wrapper.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__pmodule_cxx_h
#define	__extit__pmodule_cxx_h

#ifndef	__cplusplus
#error	C++ only
#endif

#ifdef	EXTIT_WCHAR
#include <wchar.h>
#endif

#include <string>

#include <extit/container_cxx.h>
#include <extit/pmodule.h>

#ifdef	extit_pmodule_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

namespace ExtIt
{

class Plugin;
class Module;

typedef extit_status_t	(*ModuleScanCallback)(
				Module * module,
				void *client_data);

typedef bool		(*ModuleScanStringFilter)(
				const std::string & basename,
				void *client_data);

#ifdef	EXTIT_WCHAR
typedef bool		(*ModuleScanWStringFilter)(
				const std::wstring & basename,
				void *client_data);
#endif	/* EXTIT_WCHAR */

class Module
{
	public:
		Module(extit_module_t *module);

		Module(
			Container *container,
			const void *descriptor,
			unsigned int flags);

		Module(
			Container *container,
			const char *path,
			unsigned int flags);

		Module(
			Container *container,
			const std::string & path,
			unsigned int flags);

#ifdef	EXTIT_WCHAR
		Module(
			Container *container,
			const wchar_t *path,
			unsigned int flags);

		Module(
			Container *container,
			const std::wstring & path,
			unsigned int flags);
#endif	/* EXTIT_WCHAR */

		~Module();

		Plugin *		createPlugin();

		iv_version_t		getABIVersion();

		iv_version_t		getEffectiveABIVersion();

		unsigned int		getFlags();

		extit_func_t		getFunction(
						const char *name);

		extit_func_t		getFunction(
						const std::string & name);

		const std::string *	getId();

		uint32_t		getIdVersion();

		const std::string *	getName();

		void *			getSymbol(
						const char *name);

		void *			getSymbol(
						const std::string & name);

		const std::string *	getVersion();

		extit_status_t		release();

		static
		extit_status_t		scan(
						Container *container,
						const char *directory,
						extit_module_scan_callback_t callback,
						void *callback_client_data,
						extit_module_scan_fnfilter_t fnfilter,
						void *fnfilter_client_data,
						unsigned int flags);

		static
		extit_status_t		scan(
						Container *container,
						const std::string & directory,
						ModuleScanCallback callback,
						void *callback_client_data,
						ModuleScanStringFilter fnfilter,
						void *fnfilter_client_data,
						unsigned int flags);

#ifdef	EXTIT_WCHAR
		static
		extit_status_t		scan(
						Container *container,
						const wchar_t *directory,
						extit_module_scan_callback_t callback,
						void *callback_client_data,
						extit_module_scan_fnfilter_wc_t fnfilter,
						void *fnfilter_client_data,
						unsigned int flags);

		static
		extit_status_t		scan(
						Container *container,
						const std::wstring & directory,
						ModuleScanCallback callback,
						void *callback_client_data,
						ModuleScanWStringFilter fnfilter,
						void *fnfilter_client_data,
						unsigned int flags);
#endif	/* EXTIT_WCHAR */

		void			setFlags(
						unsigned int flags);

	protected:
		extit_module_t *	module;
		const std::string *	id;
		const std::string *	name;
		const std::string *	version;

		void			init_load(
						Container *container,
						const char *path,
						unsigned int flags);

#ifdef	EXTIT_WCHAR
		void			init_load(
						Container *container,
						const wchar_t *path,
						unsigned int flags);
#endif	/* EXTIT_WCHAR */
};


class Plugin
{
	public:
		Plugin(
			extit_plugin_t *plugin,
			Module *module);

		~Plugin();

		extit_status_t		destroy();

		void *			getContext();

		void *			getInterface(
						const char *name,
						iv_version_t version);

		void *			getInterface(
						const std::string & name,
						iv_version_t version);

		unsigned int		getFlags();

		Module *		getModule();

		extit_plugin_t *	get_struct();

		iv_version_t		queryInterface(
						const char *name,
						iv_version_t base_version);

		iv_version_t		queryInterface(
						const std::string & name,
						iv_version_t base_version);

		void			setFlags(
						unsigned int flags);

	protected:
		extit_plugin_t *	plugin;
		Module *		module;
};

// namespace ExtIt
}

#undef	LIBAPI
#undef	LIBAPI_STATIC

#endif	/* !__extit__pmodule_cxx_h */
