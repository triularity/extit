project(extit)

cmake_minimum_required(VERSION 2.8)

#
# Defaults
#
set(DEFAULT_WCHAR FALSE)
set(DEFAULT_HAVE_DLFUNC FALSE)

if(CMAKE_HOST_WIN32)
	set(DEFAULT_LIB_LOADER "win32")
	set(DEFAULT_WCHAR TRUE)
elseif(CMAKE_HOST_APPLE)
	set(DEFAULT_LIB_LOADER "dylib")
else()
	set(DEFAULT_LIB_LOADER "dl")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "BSD$")
	set(DEFAULT_HAVE_DLFUNC TRUE)
endif()

set(EXTIT_PARANOID TRUE CACHE BOOL "Enable Paranoid Code Checks")
set(EXTIT_DEBUG TRUE CACHE BOOL "Enable Runtime Debugging")
set(EXTIT_WARNFREE FALSE CACHE BOOL "Enable Error on Compile Warnings")
##+set(EXTIT_WITH_CXX FALSE CACHE BOOL "Enable C++ Wrappers")
set(EXTIT_COMPILE_SAMPLES FALSE CACHE BOOL "Compile Sample Programs")
set(EXTIT_COMPILE_TESTS FALSE CACHE BOOL "Compile Unit Tests")
set(EXTIT_LIB_LOADER ${DEFAULT_LIB_LOADER} CACHE STRING "Library Loader (dl|win32|dylib)")
set(EXTIT_WCHAR ${DEFAULT_WCHAR} CACHE BOOL "Enable wchar_t support")
set(EXTIT_HAVE_DLFUNC ${DEFAULT_HAVE_DLFUNC} CACHE BOOL "Platform supports dlfunc()")
set(EXTIT_COMPAT FALSE CACHE BOOL "Enable Backward Compatibility")


include_directories(BEFORE src/include)


# ExtIt core
set(EXTIT_HEADER_FILES 
	src/include/extit/base.h
	src/include/extit/platform.h)


# ExtIt container (client side)
set(EXTIT_CONTAINER_HEADER_FILES 
	src/include/extit/container.h
	src/include/extit/container_impl.h)

set(EXTIT_CONTAINER_SOURCE_FILES
	src/extit/container/get_function.c
	src/extit/container/get_interface.c
	src/extit/container/get_symbol.c
	src/extit/container/log.c
	src/extit/container/query_interface.c)


# ExtIt plugin module (server side)
set(EXTIT_PMODULE_HEADER_FILES 
	src/include/extit/pmodule.h
	src/include/extit/plugin_spi.h)

set(EXTIT_PMODULE_SOURCE_FILES
	src/extit/pmodule/container_defaults.c
	src/extit/pmodule/module_bind.c
	src/extit/pmodule/module_create_plugin.c
	src/extit/pmodule/module_get_abi_version.c
	src/extit/pmodule/module_get_effective_abi_version.c
	src/extit/pmodule/module_get_flags.c
	src/extit/pmodule/module_get_id.c
	src/extit/pmodule/module_get_id_version.c
	src/extit/pmodule/module_get_name.c
	src/extit/pmodule/module_get_version.c
	src/extit/pmodule/module_set_flags.c
	src/extit/pmodule/module_unload.c
	src/extit/pmodule/plugin_activate.c
	src/extit/pmodule/plugin_deactivate.c
	src/extit/pmodule/plugin_destroy.c
	src/extit/pmodule/plugin_get_context.c
	src/extit/pmodule/plugin_get_flags.c
	src/extit/pmodule/plugin_get_interface.c
	src/extit/pmodule/plugin_get_module.c
	src/extit/pmodule/plugin_ping.c
	src/extit/pmodule/plugin_query_interface.c
	src/extit/pmodule/plugin_set_flags.c
	src/extit/pmodule/version.c)


# ExtIt utilities
set(EXTIT_UTIL_HEADER_FILES 
	src/include/extit/util.h)

set(EXTIT_UTIL_SOURCE_FILES
	src/extit/util/refcount.c)


# Standard interfaces (client side)
set(IF_ALLOCATOR_HEADER_FILES 
	src/include/if/allocator.h
	src/include/if/allocator_impl.h)

set(IF_ALLOCATOR_SOURCE_FILES
	src/if/allocator/alloc.c
	src/if/allocator/dup.c
	src/if/allocator/free.c
	src/if/allocator/realloc.c
	src/if/allocator/zalloc.c)

set(IF_CONFIGURABLE_HEADER_FILES 
	src/include/if/configurable.h
	src/include/if/configurable_impl.h)

set(IF_CONFIGURABLE_SOURCE_FILES
	src/if/configurable/find_property.c
	src/if/configurable/get_bool.c
	src/if/configurable/get_custom.c
	src/if/configurable/get_descriptor.c
	src/if/configurable/get_double.c
	src/if/configurable/get_enum32.c
	src/if/configurable/get_float.c
	src/if/configurable/get_int8.c
	src/if/configurable/get_int16.c
	src/if/configurable/get_int32.c
	src/if/configurable/get_int64.c
	src/if/configurable/get_uint8.c
	src/if/configurable/get_uint16.c
	src/if/configurable/get_uint32.c
	src/if/configurable/get_uint64.c
	src/if/configurable/get_utf8.c
	src/if/configurable/reset.c
	src/if/configurable/set_bool.c
	src/if/configurable/set_custom.c
	src/if/configurable/set_double.c
	src/if/configurable/set_enum32.c
	src/if/configurable/set_float.c
	src/if/configurable/set_int8.c
	src/if/configurable/set_int16.c
	src/if/configurable/set_int32.c
	src/if/configurable/set_int64.c
	src/if/configurable/set_uint8.c
	src/if/configurable/set_uint16.c
	src/if/configurable/set_uint32.c
	src/if/configurable/set_uint64.c
	src/if/configurable/set_utf8.c)

set(IF_CONFIGURABLE_UTIL_HEADER_FILES 
	src/include/if/configurable_util.h)

set(IF_CONFIGURABLE_UTIL_SOURCE_FILES
	src/if/configurable_util/enum32_find_by_id.c
	src/if/configurable_util/enum32_find_by_value.c)

set(IF_DISPOSABLE_HEADER_FILES 
	src/include/if/disposable.h
	src/include/if/disposable_impl.h)

set(IF_DISPOSABLE_SOURCE_FILES
	src/if/disposable/free.c)

set(IF_MESSAGING_HEADER_FILES 
	src/include/if/messaging.h
	src/include/if/messaging_impl.h)

set(IF_MESSAGING_SOURCE_FILES
	src/if/messaging/add_listener.c
	src/if/messaging/bind.c
	src/if/messaging/bound_add_listener.c
	src/if/messaging/bound_has_listener.c
	src/if/messaging/bound_remove_listener.c
	src/if/messaging/bound_send.c
	src/if/messaging/has_listener.c
	src/if/messaging/remove_listener.c
	src/if/messaging/remove_listener_by_id.c
	src/if/messaging/send.c
	src/if/messaging/unbind.c)

set(IF_REFCOUNT_HEADER_FILES 
	src/include/if/refcount.h
	src/include/if/refcount_impl.h)

set(IF_REFCOUNT_SOURCE_FILES
	src/if/refcount/add.c
	src/if/refcount/get.c
	src/if/refcount/release.c)

set(IF_RESOLVABLE_HEADER_FILES 
	src/include/if/resolvable.h
	src/include/if/resolvable_impl.h)

set(IF_RESOLVABLE_SOURCE_FILES
	src/if/resolvable/get_interface.c
	src/if/resolvable/query_interface.c)


# Standard interface implementations
set(IF_ALLOCATOR_STDIMPL_HEADER_FILES
	src/include/if/allocator_stdimpl.h)

set(IF_ALLOCATOR_STDIMPL_SOURCE_FILES
	src/if/allocator_stdimpl/stdimpl.c)

set(IF_CONFIGURABLE_STDIMPL_HEADER_FILES 
	src/include/if/configurable_stdimpl.h)

set(IF_CONFIGURABLE_STDIMPL_SOURCE_FILES
	src/if/configurable_stdimpl/find_property.c
	src/if/configurable_stdimpl/get_bool.c
	src/if/configurable_stdimpl/get_custom.c
	src/if/configurable_stdimpl/get_double.c
	src/if/configurable_stdimpl/get_enum32.c
	src/if/configurable_stdimpl/get_float.c
	src/if/configurable_stdimpl/get_int8.c
	src/if/configurable_stdimpl/get_int16.c
	src/if/configurable_stdimpl/get_int32.c
	src/if/configurable_stdimpl/get_int64.c
	src/if/configurable_stdimpl/get_uint8.c
	src/if/configurable_stdimpl/get_uint16.c
	src/if/configurable_stdimpl/get_uint32.c
	src/if/configurable_stdimpl/get_uint64.c
	src/if/configurable_stdimpl/get_utf8.c
	src/if/configurable_stdimpl/ops.c
	src/if/configurable_stdimpl/reset.c
	src/if/configurable_stdimpl/set_bool.c
	src/if/configurable_stdimpl/set_custom.c
	src/if/configurable_stdimpl/set_double.c
	src/if/configurable_stdimpl/set_enum32.c
	src/if/configurable_stdimpl/set_float.c
	src/if/configurable_stdimpl/set_int8.c
	src/if/configurable_stdimpl/set_int16.c
	src/if/configurable_stdimpl/set_int32.c
	src/if/configurable_stdimpl/set_int64.c
	src/if/configurable_stdimpl/set_uint8.c
	src/if/configurable_stdimpl/set_uint16.c
	src/if/configurable_stdimpl/set_uint32.c
	src/if/configurable_stdimpl/set_uint64.c
	src/if/configurable_stdimpl/set_utf8.c)

set(IF_MESSAGING_STDIMPL_HEADER_FILES
	src/include/if/messaging_stdimpl.h)

set(IF_MESSAGING_STDIMPL_SOURCE_FILES
	src/if/messaging_stdimpl/add_listener.c
	src/if/messaging_stdimpl/bind.c
	src/if/messaging_stdimpl/bound.c
	src/if/messaging_stdimpl/bound_add_listener.c
	src/if/messaging_stdimpl/bound_has_listener.c
	src/if/messaging_stdimpl/bound_remove_listener.c
	src/if/messaging_stdimpl/bound_send.c
	src/if/messaging_stdimpl/cleanup.c
	src/if/messaging_stdimpl/create.c
	src/if/messaging_stdimpl/destroy.c
	src/if/messaging_stdimpl/has_listener.c
	src/if/messaging_stdimpl/keybuf.c
	src/if/messaging_stdimpl/ops.c
	src/if/messaging_stdimpl/remove_listener.c
	src/if/messaging_stdimpl/remove_listener_by_id.c
	src/if/messaging_stdimpl/send.c
	src/if/messaging_stdimpl/unbind.c)


# IV core
set(IV_HEADER_FILES 
	src/include/iv/base.h)


# IV repository
set(IV_REPOSITORY_HEADER_FILES 
	src/include/iv/repository.h)

set(IV_REPOSITORY_SOURCE_FILES
	src/iv/repository.c)


# IV utilities
set(IV_UTIL_HEADER_FILES 
	src/include/iv/util.h)

set(IV_UTIL_SOURCE_FILES
	src/iv/util/keymap.c
	src/iv/util/matches.c)


#
# Library Loader
#
if(EXTIT_LIB_LOADER STREQUAL "dl")
	set(EXTIT_PMODULE_SOURCE_FILES
		${EXTIT_PMODULE_SOURCE_FILES}
		src/extit/pmodule/dl/container_defaults.c
		src/extit/pmodule/dl/module_defaults.c
		src/extit/pmodule/dl/module_get_function.c
		src/extit/pmodule/dl/module_get_symbol.c
		src/extit/pmodule/dl/module_load.c
		src/extit/pmodule/dl/module_release.c
		src/extit/pmodule/dl/module_scan.c)
elseif(EXTIT_LIB_LOADER STREQUAL "win32")
	set(EXTIT_PMODULE_SOURCE_FILES
		${EXTIT_PMODULE_SOURCE_FILES}
		src/extit/pmodule/win32/container_defaults.c
		src/extit/pmodule/win32/module_defaults.c
		src/extit/pmodule/win32/module_get_function.c
		src/extit/pmodule/win32/module_get_symbol.c
		src/extit/pmodule/win32/module_load.c
		src/extit/pmodule/win32/module_release.c
		src/extit/pmodule/win32/module_scan.c
		src/extit/pmodule/win32/ptr_util.c
		src/extit/pmodule/win32/ptr_util.h)
##+elseif(EXTIT_LIB_LOADER STREQUAL "dylib")
##+	set(EXTIT_PMODULE_SOURCE_FILES
##+		${EXTIT_PMODULE_SOURCE_FILES}
##+		src/extit/pmodule/dylib/container_defaults.c
##+		src/extit/pmodule/dylib/module_defaults.c
##+		src/extit/pmodule/dylib/module_get_function.c
##+		src/extit/pmodule/dylib/module_get_symbol.c
##+		src/extit/pmodule/dylib/module_load.c
##+		src/extit/pmodule/dylib/module_release.c
##+		src/extit/pmodule/dylib/module_scan.c)
else()
	message(FATAL_ERROR "Unsupported library loader: ${EXTIT_LIB_LOADER}")
endif()


#
# C++ Support
#
if(EXTIT_WITH_CXX)
##+	set(EXTIT_PMODULE_SOURCE_FILES
##+		${EXTIT_PMODULE_SOURCE_FILES}
##+		src/extit/pmodule/container_cxx.cc)
endif()


#
# Configuration Options
#
if(EXTIT_PARANOID)
	add_definitions("-DEXTIT_PARANOID")
endif()

if(EXTIT_DEBUG)
	add_definitions("-DEXTIT_DEBUG")
	add_definitions("-DIV_REPOSITORY_DEBUG")
endif()

if(EXTIT_WCHAR)
	add_definitions("-DEXTIT_WCHAR")
endif()

if(EXTIT_HAVE_DLFUNC)
	add_definitions("-DEXTIT_HAVE_DLFUNC")
endif()

if(EXTIT_COMPAT)
	add_definitions("-DEXTIT_COMPAT")
endif()


#
# [lib]extit_pmodule
#
add_library(
	extit_pmodule
		${EXTIT_PMODULE_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${EXTIT_PMODULE_HEADER_FILES}
		${EXTIT_CONTAINER_HEADER_FILES}
		${EXTIT_UTIL_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

set_target_properties(
	extit_pmodule PROPERTIES
		POSITION_INDEPENDENT_CODE ON)

target_link_libraries(
	extit_pmodule
		extit_util)

if(EXTIT_PARANOID)
	target_link_libraries(
		extit_pmodule
			iv_util)
endif()


#
# [lib]extit_container
#
add_library(
	extit_container
		${EXTIT_CONTAINER_SOURCE_FILES}
		${IV_HEADER_FILES}
		${EXTIT_HEADER_FILES})

set_target_properties(
	extit_container PROPERTIES
		POSITION_INDEPENDENT_CODE ON)


#
# [lib]extit_util
#
add_library(
	extit_util
		${EXTIT_UTIL_SOURCE_FILES}
		${IV_HEADER_FILES}
		${EXTIT_HEADER_FILES}
		${EXTIT_UTIL_HEADER_FILES})

set_target_properties(
	extit_util PROPERTIES
		POSITION_INDEPENDENT_CODE ON)


#
# [lib]if_allocator
#
add_library(
	if_allocator
		${IF_ALLOCATOR_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${IF_ALLOCATOR_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

set_target_properties(
	if_allocator PROPERTIES
		POSITION_INDEPENDENT_CODE ON)

if(EXTIT_PARANOID)
	target_link_libraries(
		if_allocator
			iv_util)
endif()


#
# [lib]if_allocator_stdimpl
#
add_library(
	if_allocator_stdimpl
		${IF_ALLOCATOR_STDIMPL_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${IF_ALLOCATOR_HEADER_FILES}
		${IF_ALLOCATOR_STDIMPL_HEADER_FILES}
		${IV_HEADER_FILES})

set_target_properties(
	if_allocator_stdimpl PROPERTIES
		POSITION_INDEPENDENT_CODE ON)


#
# [lib]if_configurable
#
add_library(
	if_configurable
		${IF_CONFIGURABLE_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${IF_CONFIGURABLE_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

set_target_properties(
	if_configurable PROPERTIES
		POSITION_INDEPENDENT_CODE ON)

if(EXTIT_PARANOID)
	target_link_libraries(
		if_configurable
			iv_util)
endif()


#
# [lib]if_configurable_stdimpl
#
add_library(
	if_configurable_stdimpl
		${IF_CONFIGURABLE_STDIMPL_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${IF_CONFIGURABLE_HEADER_FILES}
		${IF_CONFIGURABLE_STDIMPL_HEADER_FILES}
		${IV_HEADER_FILES})

set_target_properties(
	if_configurable_stdimpl PROPERTIES
		POSITION_INDEPENDENT_CODE ON)

target_link_libraries(
	if_configurable_stdimpl
		if_configurable_util)

if(EXTIT_PARANOID)
	target_link_libraries(
		if_configurable_stdimpl
			iv_util)
endif()


#
# [lib]if_configurable_util
#
add_library(
	if_configurable_util
		${IF_CONFIGURABLE_UTIL_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${IF_CONFIGURABLE_HEADER_FILES}
		${IF_CONFIGURABLE_UTIL_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

set_target_properties(
	if_configurable_util PROPERTIES
		POSITION_INDEPENDENT_CODE ON)


#
# [lib]if_disposable
#
add_library(
	if_disposable
		${IF_DISPOSABLE_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${IF_DISPOSABLE_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

set_target_properties(
	if_disposable PROPERTIES
		POSITION_INDEPENDENT_CODE ON)

if(EXTIT_PARANOID)
	target_link_libraries(
		if_disposable
			iv_util)
endif()


#
# [lib]if_messaging
#
add_library(
	if_messaging
		${IF_MESSAGING_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${IF_MESSAGING_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

set_target_properties(
	if_messaging PROPERTIES
		POSITION_INDEPENDENT_CODE ON)

if(EXTIT_PARANOID)
	target_link_libraries(
		if_messaging
			iv_util)
endif()


#
# [lib]if_messaging_stdimpl
#
add_library(
	if_messaging_stdimpl
		${IF_MESSAGING_STDIMPL_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${IF_MESSAGING_HEADER_FILES}
		${IF_MESSAGING_STDIMPL_HEADER_FILES}
		${IV_HEADER_FILES})

set_target_properties(
	if_messaging_stdimpl PROPERTIES
		POSITION_INDEPENDENT_CODE ON)

	target_link_libraries(
		if_messaging_stdimpl
			iv_util
			extit_util)


#
# [lib]if_refcount
#
add_library(
	if_refcount
		${IF_REFCOUNT_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${IF_REFCOUNT_HEADER_FILES}
		${EXTIT_UTIL_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

set_target_properties(
	if_refcount PROPERTIES
		POSITION_INDEPENDENT_CODE ON)

target_link_libraries(
	if_refcount
		extit_util)

if(EXTIT_PARANOID)
	target_link_libraries(
		if_refcount
			iv_util)
endif()


#
# [lib]if_resolvable
#
add_library(
	if_resolvable
		${IF_RESOLVABLE_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${IF_RESOLVABLE_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

set_target_properties(
	if_resolvable PROPERTIES
		POSITION_INDEPENDENT_CODE ON)

if(EXTIT_PARANOID)
	target_link_libraries(
		if_resolvable
			iv_util)
endif()


#
# [lib]iv_repository
#
add_library(
	iv_repository
		${IV_REPOSITORY_SOURCE_FILES}
		${IV_HEADER_FILES}
		${IV_REPOSITORY_HEADER_FILES})

set_target_properties(
	iv_repository PROPERTIES
		POSITION_INDEPENDENT_CODE ON)


#
# [lib]iv_util
#
add_library(
	iv_util
		${IV_UTIL_SOURCE_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

set_target_properties(
	iv_util PROPERTIES
		POSITION_INDEPENDENT_CODE ON)


#
# Platform Specific
#
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_definitions("-D_GNU_SOURCE")
	target_link_libraries(extit_pmodule dl)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "BSD")
	add_definitions("-DEXTIT_HAVE_DLFUNC_T")
endif()

if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-prototypes -Wstrict-prototypes")

	if(EXTIT_WARNFREE)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
	endif()
elseif(MSVC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /wd4054 /wd4100")

	# Get rid of annoying D9025 warning for /W3 /W4
	string(REPLACE "/W3 " "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})

	if(EXTIT_WARNFREE)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /WX")
	endif()

	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()


#
# Special static/shared naming
#
if(NOT DEFINED LIBNAME_POSTFIX)
	if(BUILD_SHARED_LIBS)
		if(DEFINED LIBNAME_POSTFIX_SHARED)
			set(LIBNAME_POSTFIX ${LIBNAME_POSTFIX_SHARED})
		endif()
	else()
		if(DEFINED LIBNAME_POSTFIX_STATIC)
			set(LIBNAME_POSTFIX ${LIBNAME_POSTFIX_STATIC})
		endif()
	endif()
endif(NOT DEFINED LIBNAME_POSTFIX)

if(DEFINED LIBNAME_POSTFIX)
	set_target_properties(
		extit_pmodule PROPERTIES
			OUTPUT_NAME "extit_pmodule${LIBNAME_POSTFIX}")

	set_target_properties(
		if_allocator PROPERTIES
			OUTPUT_NAME "if_allocator${LIBNAME_POSTFIX}")

	set_target_properties(
		if_allocator_stdimpl PROPERTIES
			OUTPUT_NAME "if_allocator_stdimpl${LIBNAME_POSTFIX}")

	set_target_properties(
		if_disposable PROPERTIES
			OUTPUT_NAME "if_disposable${LIBNAME_POSTFIX}")

	set_target_properties(
		if_messaging PROPERTIES
			OUTPUT_NAME "if_messaging${LIBNAME_POSTFIX}")

	set_target_properties(
		if_messaging_stdimpl PROPERTIES
			OUTPUT_NAME "if_messaging_stdimpl${LIBNAME_POSTFIX}")

	set_target_properties(
		if_refcount PROPERTIES
			OUTPUT_NAME "if_refcount${LIBNAME_POSTFIX}")

	set_target_properties(
		if_resolvable PROPERTIES
			OUTPUT_NAME "if_resolvable${LIBNAME_POSTFIX}")

	set_target_properties(
		extif_util PROPERTIES
			OUTPUT_NAME "extif_util${LIBNAME_POSTFIX}")

	set_target_properties(
		iv_repository PROPERTIES
			OUTPUT_NAME "iv_repository${LIBNAME_POSTFIX}")

	set_target_properties(
		iv_util PROPERTIES
			OUTPUT_NAME "iv_util${LIBNAME_POSTFIX}")
endif(DEFINED LIBNAME_POSTFIX)


#
# Install
#
install(
	TARGETS
		extit_pmodule
		if_allocator
		if_allocator_stdimpl
		if_configurable
		if_configurable_stdimpl
		if_configurable_util
		if_disposable
		if_messaging
		if_messaging_stdimpl
		if_refcount
		if_resolvable
		extit_util
		iv_repository
		iv_util
	DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(
	FILES
		${EXTIT_HEADER_FILES}
		${EXTIT_CONTAINER_HEADER_FILES}
		${EXTIT_PMODULE_HEADER_FILES}
		${EXTIT_REPOSITORY_HEADER_FILES}
		${EXTIT_UTIL_HEADER_FILES}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/extit)

install(
	FILES
		${IF_ALLOCATOR_HEADER_FILES}
		${IF_ALLOCATOR_STDIMPL_HEADER_FILES}
		${IF_CONFIGURABLE_HEADER_FILES}
		${IF_CONFIGURABLE_STDIMPL_HEADER_FILES}
		${IF_CONFIGURABLE_UTIL_HEADER_FILES}
		${IF_DISPOSABLE_HEADER_FILES}
		${IF_MESSAGING_HEADER_FILES}
		${IF_MESSAGING_STDIMPL_HEADER_FILES}
		${IF_REFCOUNT_HEADER_FILES}
		${IF_RESOLVABLE_HEADER_FILES}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/if)

install(
	FILES
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/iv)


#
# Sample Code
#
if(EXTIT_COMPILE_SAMPLES)
	#
	# Allocator Interface Plugin
	#
	add_library(
		sample_if_allocator_plugin SHARED
			sample/if_allocator/plugin.c
			${EXTIT_HEADER_FILES}
			${EXTIT_ALLOCATOR_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_if_allocator_plugin
			if_allocator
			extit_container
			iv_util)


	#
	# Allocator Interface Server
	#
	add_executable(
		sample_if_allocator_server
			sample/if_allocator/server.c
			${EXTIT_HEADER_FILES}
			${EXTIT_ALLOCATOR_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_if_allocator_server
			if_allocator_stdimpl
			extit_pmodule)


	#
	# Configurable Interface
	#
	add_executable(
		sample_if_configurable
			sample/if_configurable/client.c
			sample/if_configurable/scan_service.c
			sample/if_configurable/scan_service.h
			${EXTIT_HEADER_FILES}
			${IF_CONFIGURABLE_HEADER_FILES}
			${IF_CONFIGURABLE_STDIMPL_HEADER_FILES}
			${IF_CONFIGURABLE_UTIL_HEADER_FILES}
			${IV_HEADER_FILES})

	target_link_libraries(
		sample_if_configurable
			if_configurable
			if_configurable_stdimpl
			if_configurable_util)


	#
	# Disposable Interface
	#
	add_executable(
		sample_if_disposable
			sample/if_disposable/client.c
			sample/if_disposable/item.c
			sample/if_disposable/item.h
			sample/if_disposable/itemsource.c
			sample/if_disposable/itemsource.h
			${EXTIT_HEADER_FILES}
			${IF_DISPOSABLE_HEADER_FILES}
			${IF_DISPOSABLE_IMPL_HEADER_FILES}
			${IV_HEADER_FILES})

	target_link_libraries(
		sample_if_disposable
			if_disposable)


	#
	# Messaging Interface (alarm)
	#
	add_executable(
		sample_if_messaging_alarm
			sample/if_messaging/alarm.h
			sample/if_messaging/demo.c
			${EXTIT_HEADER_FILES}
			${EXTIT_MESSAGING_HEADER_FILES}
			${EXTIT_MESSAGING_STDIMPL_HEADER_FILES}
			${IV_HEADER_FILES})

	target_link_libraries(
		sample_if_messaging_alarm
			if_messaging
			if_messaging_stdimpl)


	#
	# Refcount Interface
	#
	add_executable(
		sample_if_refcount
			sample/if_refcount/client.c
			sample/if_refcount/myobj.h
			sample/if_refcount/provider.c
			sample/if_refcount/provider.h
			sample/if_refcount/worklist.c
			sample/if_refcount/worklist.h
			${EXTIT_HEADER_FILES}
			${IF_REFCOUNT_HEADER_FILES}
			${EXTIT_UTIL_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_if_refcount
			if_refcount)


	#
	# Resolvable Interface
	#
	add_executable(
		sample_if_resolvable
			sample/if_resolvable/client.c
			sample/if_resolvable/myobj.c
			sample/if_resolvable/myobj.h
			sample/if_resolvable/myobj_client.c
			sample/if_resolvable/myobj_priv.h
			${EXTIT_HEADER_FILES}
			${IF_REFCOUNT_HEADER_FILES}
			${IF_REFCOUNT_IMPL_HEADER_FILES}
			${IF_CONFIGURABLE_HEADER_FILES}
			${IF_CONFIGURABLE_IMPL_HEADER_FILES}
			${IF_CONFIGURABLE_STDIMPL_HEADER_FILES}
			${IF_RESOLVABLE_HEADER_FILES}
			${IF_RESOLVABLE_IMPL_HEADER_FILES}
			${EXTIT_UTIL_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_if_resolvable
			extit_util
			if_refcount
			if_resolvable
			if_configurable
			if_configurable_stdimpl
			iv_util)


	#
	# Interface Repository
	#
	add_executable(
		sample_iv_repository
			sample/iv_repository/repository.c
			${IV_HEADER_FILES}
			${IV_REPOSITORY_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_iv_repository
			iv_repository)


	#
	# Multi-Version
	#
	add_executable(
		sample_multiver_server_1_0
			sample/multiver/persistence_impl.c
			sample/multiver/multiver_server.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_REPOSITORY_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	set_target_properties(
		sample_multiver_server_1_0 PROPERTIES
			COMPILE_DEFINITIONS
				"PERSISTENCE_INTERFACE_TARGET=PERSISTENCE_INTERFACE_VERSION_1_0")

	target_link_libraries(
		sample_multiver_server_1_0
			extit_pmodule
			iv_repository)


	add_executable(
		sample_multiver_server_1_1
			sample/multiver/persistence_impl.c
			sample/multiver/multiver_server.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_REPOSITORY_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	set_target_properties(
		sample_multiver_server_1_1 PROPERTIES
			COMPILE_DEFINITIONS
				"PERSISTENCE_INTERFACE_TARGET=PERSISTENCE_INTERFACE_VERSION_1_1")

	target_link_libraries(
		sample_multiver_server_1_1
			extit_pmodule
			iv_repository)


	add_executable(
		sample_multiver_server_1_2
			sample/multiver/persistence_impl.c
			sample/multiver/multiver_server.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_REPOSITORY_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	set_target_properties(
		sample_multiver_server_1_2 PROPERTIES
			COMPILE_DEFINITIONS
				"PERSISTENCE_INTERFACE_TARGET=PERSISTENCE_INTERFACE_VERSION_1_2")

	target_link_libraries(
		sample_multiver_server_1_2
			extit_pmodule
			iv_repository)


	add_library(
		sample_multiver_plugin_1_0 SHARED
			sample/multiver/multiver_plugin.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_multiver_plugin_1_0
			extit_container
			iv_util)

	set_target_properties(
		sample_multiver_plugin_1_0 PROPERTIES
			COMPILE_DEFINITIONS
				"PERSISTENCE_INTERFACE_TARGET=IV_VERSION(1,0)")


	add_library(
		sample_multiver_plugin_1_1 SHARED
			sample/multiver/multiver_plugin.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_multiver_plugin_1_1
			extit_container
			iv_util)

	set_target_properties(
		sample_multiver_plugin_1_1 PROPERTIES
			COMPILE_DEFINITIONS
				"PERSISTENCE_INTERFACE_TARGET=IV_VERSION(1,1)")


	add_library(
		sample_multiver_plugin_1_2 SHARED
			sample/multiver/multiver_plugin.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_multiver_plugin_1_2
			extit_container
			iv_util)

	set_target_properties(
		sample_multiver_plugin_1_2 PROPERTIES
			COMPILE_DEFINITIONS
			"PERSISTENCE_INTERFACE_TARGET=IV_VERSION(1,2)")


	#
	# Plugin Scanning
	#
	add_executable(
		sample_scan_server
			sample/scan/recipe_server.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_scan_server
			extit_pmodule)


	add_library(
		sample_scan_plugin_pie SHARED
			sample/scan/recipe_pie.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_scan_plugin_pie
			iv_util)

	set_target_properties(
		sample_scan_plugin_pie PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-pie")


	add_library(
		sample_scan_plugin_tea SHARED
			sample/scan/recipe_tea.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_scan_plugin_tea
			iv_util)

	set_target_properties(
		sample_scan_plugin_tea PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-tea")


	add_library(
		sample_scan_plugin_tacos SHARED
			sample/scan/recipe_tacos.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_scan_plugin_tacos
			iv_util)

	set_target_properties(
		sample_scan_plugin_tacos PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-tacos")


	#
	# Simple Plugin
	#
	add_executable(
		sample_simple_server
			sample/simple/simple_server.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_simple_server
			extit_pmodule)


	add_library(
		sample_simple_plugin SHARED
			sample/simple/simple_plugin.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_simple_plugin
			extit_container
			iv_util)
endif(EXTIT_COMPILE_SAMPLES)


if(EXTIT_COMPILE_TESTS)
	add_executable(
		test_extit_bool_t
			tests/extit_bool_t/test_bool.c
			${EXTIT_HEADER_FILES})

	add_executable(
		test_extit_refcount
			tests/extit_refcount/test_refcount.c
			${EXTIT_HEADER_FILES}
			${EXTIT_UTIL_HEADER_FILES})

	target_link_libraries(
		test_extit_refcount
			extit_util)

	add_executable(
		test_iv_version
			tests/iv_version/test_iv_version.c
			${IV_HEADER_FILES})

	add_executable(
		test_iv_bool_t
			tests/iv_bool_t/test_iv_bool.c
			${IV_HEADER_FILES})

	add_executable(
		test_iv_keymap
			tests/iv_keymap/test_keymap.c
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		test_iv_keymap
			iv_util)

	add_executable(
		test_iv_matches
			tests/iv_matches/test_iv_matches.c
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		test_iv_matches
			iv_util)
endif(EXTIT_COMPILE_TESTS)

