project(extit)

cmake_minimum_required(VERSION 2.8.12)

#
# Defaults
#
set(DEFAULT_WCHAR FALSE)
set(DEFAULT_HAVE_DLFUNC FALSE)

if(WIN32)
	set(DEFAULT_LIB_LOADER "win32")
	set(DEFAULT_WCHAR TRUE)
else()
	set(DEFAULT_LIB_LOADER "dl")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
	set(DEFAULT_HAVE_DLFUNC TRUE)
endif()

set(EXTIT_PARANOID TRUE CACHE BOOL "Enable Paranoid Code Checks")
set(EXTIT_DEBUG TRUE CACHE BOOL "Enable Runtime Debugging")
set(EXTIT_WARNFREE FALSE CACHE BOOL "Enable Error on Compile Warnings")
set(EXTIT_WITH_CXX TRUE CACHE BOOL "Enable C++ Wrappers")
set(EXTIT_COMPILE_SAMPLES FALSE CACHE BOOL "Compile Sample Programs")
set(EXTIT_COMPILE_TESTS FALSE CACHE BOOL "Compile Unit Tests")
set(EXTIT_LIB_LOADER ${DEFAULT_LIB_LOADER} CACHE STRING "Library Loader (dl|win32|dylib)")
set(EXTIT_WCHAR ${DEFAULT_WCHAR} CACHE BOOL "Enable wchar_t support")
set(EXTIT_HAVE_DLFUNC ${DEFAULT_HAVE_DLFUNC} CACHE BOOL "Platform supports dlfunc()")
set(EXTIT_COMPAT FALSE CACHE BOOL "Enable Backward Compatibility")
set(EXTIT_MALLOC_0_SUCCEEDS FALSE CACHE BOOL "malloc/realloc succeeds with size 0")


# Piggy back off of ExtIt setting for now
set(IV_COMPAT ${EXTIT_COMPAT})


include_directories(BEFORE src/include)


# ExtIt core
set(EXTIT_HEADER_FILES 
	src/include/extit/base.h
	src/include/extit/platform.h
	src/include/extit/version.h)


# ExtIt container (client side)
set(EXTIT_CONTAINER_HEADER_FILES 
	src/include/extit/container.h
	src/include/extit/container_impl.h)

set(EXTIT_CONTAINER_SOURCE_FILES
	src/extit/container/get_function.c
	src/extit/container/get_interface.c
	src/extit/container/get_symbol.c
	src/extit/container/get_version.c
	src/extit/container/log.c
	src/extit/container/query_interface.c)


# ExtIt container standard implementation (server side)
set(EXTIT_CONTAINER_STDIMPL_HEADER_FILES 
	src/include/extit/container_stdimpl.h)

set(EXTIT_CONTAINER_STDIMPL_SOURCE_FILES
	src/extit/container_stdimpl/get_interface.c
	src/extit/container_stdimpl/log.c
	src/extit/container_stdimpl/ops.c
	src/extit/container_stdimpl/query_interface.c)


# ExtIt plugin module (server side)
set(EXTIT_PMODULE_HEADER_FILES 
	src/include/extit/pmodule.h
	src/include/extit/pmodule_impl.h)

set(EXTIT_PMODULE_SOURCE_FILES
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
	src/extit/pmodule/plugin_destroy.c
	src/extit/pmodule/plugin_get_context.c
	src/extit/pmodule/plugin_get_flags.c
	src/extit/pmodule/plugin_get_interface.c
	src/extit/pmodule/plugin_get_module.c
	src/extit/pmodule/plugin_query_interface.c
	src/extit/pmodule/plugin_set_flags.c
	src/extit/pmodule/pmodule_internal.h
	src/extit/pmodule/version.c)


# ExtIt utilities
set(EXTIT_UTIL_HEADER_FILES 
	src/include/extit/util.h)

set(EXTIT_UTIL_SOURCE_FILES
	src/extit/util/refcount_add.c
	src/extit/util/refcount_isnone.c
	src/extit/util/refcount_release.c)

# Standard Interfaces (core)
set(STDIF_HEADER_FILES 
	src/include/stdif/version.h)

# Standard interfaces (client side)
set(STDIF_ALLOCATOR_HEADER_FILES 
	src/include/stdif/allocator.h
	src/include/stdif/allocator_impl.h)

set(STDIF_ALLOCATOR_SOURCE_FILES
	src/stdif/allocator/alloc.c
	src/stdif/allocator/dup.c
	src/stdif/allocator/free.c
	src/stdif/allocator/realloc.c
	src/stdif/allocator/zalloc.c)

set(STDIF_CONFIGURABLE_HEADER_FILES 
	src/include/stdif/configurable.h
	src/include/stdif/configurable_impl.h)

set(STDIF_CONFIGURABLE_SOURCE_FILES
	src/stdif/configurable/find_property.c
	src/stdif/configurable/get_bool.c
	src/stdif/configurable/get_data.c
	src/stdif/configurable/get_descriptor.c
	src/stdif/configurable/get_double.c
	src/stdif/configurable/get_enum32.c
	src/stdif/configurable/get_float.c
	src/stdif/configurable/get_function.c
	src/stdif/configurable/get_int8.c
	src/stdif/configurable/get_int16.c
	src/stdif/configurable/get_int32.c
	src/stdif/configurable/get_int64.c
	src/stdif/configurable/get_uint8.c
	src/stdif/configurable/get_uint16.c
	src/stdif/configurable/get_uint32.c
	src/stdif/configurable/get_uint64.c
	src/stdif/configurable/get_utf8.c
	src/stdif/configurable/reset.c
	src/stdif/configurable/set_bool.c
	src/stdif/configurable/set_data.c
	src/stdif/configurable/set_double.c
	src/stdif/configurable/set_enum32.c
	src/stdif/configurable/set_float.c
	src/stdif/configurable/set_function.c
	src/stdif/configurable/set_int8.c
	src/stdif/configurable/set_int16.c
	src/stdif/configurable/set_int32.c
	src/stdif/configurable/set_int64.c
	src/stdif/configurable/set_uint8.c
	src/stdif/configurable/set_uint16.c
	src/stdif/configurable/set_uint32.c
	src/stdif/configurable/set_uint64.c
	src/stdif/configurable/set_utf8.c)

set(STDIF_CONFIGURABLE_UTIL_HEADER_FILES 
	src/include/stdif/configurable_util.h)

set(STDIF_CONFIGURABLE_UTIL_SOURCE_FILES
	src/stdif/configurable_util/dump_descriptor.c
	src/stdif/configurable_util/dump_enum32.c
	src/stdif/configurable_util/dump_propdef.c
	src/stdif/configurable_util/enum32_find_by_id.c
	src/stdif/configurable_util/enum32_find_by_value.c
	src/stdif/configurable_util/fprint_property.c
	src/stdif/configurable_util/fprint_utf8.c
	src/stdif/configurable_util/type_to_string.c)

set(STDIF_DISPOSABLE_HEADER_FILES 
	src/include/stdif/disposable.h
	src/include/stdif/disposable_impl.h)

set(STDIF_DISPOSABLE_SOURCE_FILES
	src/stdif/disposable/free.c)

set(STDIF_MESSAGING_HEADER_FILES 
	src/include/stdif/messaging.h
	src/include/stdif/messaging_impl.h)

set(STDIF_MESSAGING_SOURCE_FILES
	src/stdif/messaging/add_listener.c
	src/stdif/messaging/bind.c
	src/stdif/messaging/bound_add_listener.c
	src/stdif/messaging/bound_has_listener.c
	src/stdif/messaging/bound_remove_listener.c
	src/stdif/messaging/bound_send.c
	src/stdif/messaging/has_listener.c
	src/stdif/messaging/remove_listener.c
	src/stdif/messaging/remove_listener_by_id.c
	src/stdif/messaging/send.c
	src/stdif/messaging/unbind.c)

set(STDIF_REFERENCED_HEADER_FILES 
	src/include/stdif/referenced.h
	src/include/stdif/referenced_impl.h)

set(STDIF_REFERENCED_SOURCE_FILES
	src/stdif/referenced/add.c
	src/stdif/referenced/release.c)

set(STDIF_RESOLVABLE_HEADER_FILES 
	src/include/stdif/resolvable.h
	src/include/stdif/resolvable_impl.h)

set(STDIF_RESOLVABLE_SOURCE_FILES
	src/stdif/resolvable/get_interface.c
	src/stdif/resolvable/query_interface.c)


# Standard interface implementations
set(STDIF_ALLOCATOR_STDIMPL_HEADER_FILES
	src/include/stdif/allocator_stdimpl.h)

set(STDIF_ALLOCATOR_STDIMPL_SOURCE_FILES
	src/stdif/allocator_stdimpl/stdimpl.c)

set(STDIF_CONFIGURABLE_STDIMPL_HEADER_FILES 
	src/include/stdif/configurable_stdimpl.h)

set(STDIF_CONFIGURABLE_STDIMPL_SOURCE_FILES
	src/stdif/configurable_stdimpl/find_property.c
	src/stdif/configurable_stdimpl/get_bool.c
	src/stdif/configurable_stdimpl/get_data.c
	src/stdif/configurable_stdimpl/get_descriptor.c
	src/stdif/configurable_stdimpl/get_double.c
	src/stdif/configurable_stdimpl/get_enum32.c
	src/stdif/configurable_stdimpl/get_float.c
	src/stdif/configurable_stdimpl/get_function.c
	src/stdif/configurable_stdimpl/get_int8.c
	src/stdif/configurable_stdimpl/get_int16.c
	src/stdif/configurable_stdimpl/get_int32.c
	src/stdif/configurable_stdimpl/get_int64.c
	src/stdif/configurable_stdimpl/get_uint8.c
	src/stdif/configurable_stdimpl/get_uint16.c
	src/stdif/configurable_stdimpl/get_uint32.c
	src/stdif/configurable_stdimpl/get_uint64.c
	src/stdif/configurable_stdimpl/get_utf8.c
	src/stdif/configurable_stdimpl/ops.c
	src/stdif/configurable_stdimpl/reset.c
	src/stdif/configurable_stdimpl/set_bool.c
	src/stdif/configurable_stdimpl/set_data.c
	src/stdif/configurable_stdimpl/set_double.c
	src/stdif/configurable_stdimpl/set_enum32.c
	src/stdif/configurable_stdimpl/set_float.c
	src/stdif/configurable_stdimpl/set_function.c
	src/stdif/configurable_stdimpl/set_int8.c
	src/stdif/configurable_stdimpl/set_int16.c
	src/stdif/configurable_stdimpl/set_int32.c
	src/stdif/configurable_stdimpl/set_int64.c
	src/stdif/configurable_stdimpl/set_uint8.c
	src/stdif/configurable_stdimpl/set_uint16.c
	src/stdif/configurable_stdimpl/set_uint32.c
	src/stdif/configurable_stdimpl/set_uint64.c
	src/stdif/configurable_stdimpl/set_utf8.c)

set(STDIF_MESSAGING_STDIMPL_HEADER_FILES
	src/include/stdif/messaging_stdimpl.h)

set(STDIF_MESSAGING_STDIMPL_SOURCE_FILES
	src/stdif/messaging_stdimpl/add_listener.c
	src/stdif/messaging_stdimpl/bind.c
	src/stdif/messaging_stdimpl/bound.c
	src/stdif/messaging_stdimpl/bound_add_listener.c
	src/stdif/messaging_stdimpl/bound_has_listener.c
	src/stdif/messaging_stdimpl/bound_remove_listener.c
	src/stdif/messaging_stdimpl/bound_send.c
	src/stdif/messaging_stdimpl/cleanup.c
	src/stdif/messaging_stdimpl/create.c
	src/stdif/messaging_stdimpl/destroy.c
	src/stdif/messaging_stdimpl/has_listener.c
	src/stdif/messaging_stdimpl/ops.c
	src/stdif/messaging_stdimpl/remove_listener.c
	src/stdif/messaging_stdimpl/remove_listener_by_id.c
	src/stdif/messaging_stdimpl/send.c
	src/stdif/messaging_stdimpl/unbind.c)


# IV core
set(IV_HEADER_FILES 
	src/include/iv/base.h
	src/include/iv/version.h)


# IV map
set(IV_MAP_HEADER_FILES 
	src/include/iv/map.h)

set(IV_MAP_SOURCE_FILES
	src/iv/map.c)


# IV repository
set(IV_REPOSITORY_HEADER_FILES 
	src/include/iv/repository.h)

set(IV_REPOSITORY_SOURCE_FILES
	src/iv/repository/cleanup.c
	src/iv/repository/create.c
	src/iv/repository/destroy.c
	src/iv/repository/get.c
	src/iv/repository/query.c
	src/iv/repository/remove.c
	src/iv/repository/set.c)


# IV utilities
set(IV_UTIL_HEADER_FILES 
	src/include/iv/util.h)

set(IV_UTIL_SOURCE_FILES
	src/iv/util/matches.c)

if(IV_COMPAT)
	set(IV_UTIL_SOURCE_FILES
		${IV_UTIL_SOURCE_FILES}
		src/iv/util/keymap.c)
endif()


#
# Library Loader
#
if(EXTIT_LIB_LOADER STREQUAL "dl")
	set(EXTIT_CONTAINER_STDIMPL_SOURCE_FILES
		${EXTIT_CONTAINER_STDIMPL_SOURCE_FILES}
		src/extit/container_stdimpl/dl/get_function.c
		src/extit/container_stdimpl/dl/get_symbol.c)

	set(EXTIT_PMODULE_SOURCE_FILES
		${EXTIT_PMODULE_SOURCE_FILES}
		src/extit/pmodule/dl/module_get_function.c
		src/extit/pmodule/dl/module_get_symbol.c
		src/extit/pmodule/dl/module_load.c
		src/extit/pmodule/dl/module_release.c
		src/extit/pmodule/dl/module_scan.c)

	if(APPLE)
		set(EXTIT_PMODULE_SOURCE_FILES
			${EXTIT_PMODULE_SOURCE_FILES}
			src/extit/pmodule/dylib/module_defaults.c)
	else()
		set(EXTIT_PMODULE_SOURCE_FILES
			${EXTIT_PMODULE_SOURCE_FILES}
			src/extit/pmodule/dl/module_defaults.c)
	endif()
elseif(EXTIT_LIB_LOADER STREQUAL "win32")
	set(EXTIT_CONTAINER_STDIMPL_SOURCE_FILES
		${EXTIT_CONTAINER_STDIMPL_SOURCE_FILES}
		src/extit/container_stdimpl/win32/get_function.c
		src/extit/container_stdimpl/win32/get_symbol.c)

	set(EXTIT_PMODULE_SOURCE_FILES
		${EXTIT_PMODULE_SOURCE_FILES}
		src/extit/pmodule/win32/module_defaults.c
		src/extit/pmodule/win32/module_get_function.c
		src/extit/pmodule/win32/module_get_symbol.c
		src/extit/pmodule/win32/module_load.c
		src/extit/pmodule/win32/module_release.c
		src/extit/pmodule/win32/module_scan.c)
else()
	message(FATAL_ERROR "Unsupported library loader: ${EXTIT_LIB_LOADER}")
endif()


#
# C++ Support
#
if(EXTIT_WITH_CXX)
	set(EXTIT_CONTAINER_HEADER_FILES 
		${EXTIT_CONTAINER_HEADER_FILES}
		src/include/extit/container_cxx.h)

	set(EXTIT_CONTAINER_SOURCE_FILES
		${EXTIT_CONTAINER_SOURCE_FILES}
		src/extit/container/Container.cc
		src/extit/container/Container_1_0.cc
		src/extit/container/ContainerImpl.cc
		src/extit/container/ContainerImpl_1_0.cc)

	set(EXTIT_PMODULE_HEADER_FILES 
		${EXTIT_PMODULE_HEADER_FILES}
		src/include/extit/pmodule_cxx.h)

	set(EXTIT_PMODULE_SOURCE_FILES
		${EXTIT_PMODULE_SOURCE_FILES}
		src/extit/pmodule/Module.cc
		src/extit/pmodule/Plugin.cc)
endif()


#
# Configuration Options
#
if(EXTIT_PARANOID)
	add_definitions("-DIV_PARANOID")
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

if(IV_COMPAT)
	add_definitions("-DIV_COMPAT")
endif()

if(EXTIT_MALLOC_0_SUCCEEDS)
	add_definitions("-DEXTIT_MALLOC_0_SUCCEEDS")
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

target_link_libraries(
	extit_pmodule
		extit_container
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


#
# [lib]extit_container_stdimpl
#
add_library(
	extit_container_stdimpl
		${EXTIT_CONTAINER_STDIMPL_SOURCE_FILES}
		${EXTIT_CONTAINER_STDIMPL_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_MAP_HEADER_FILES}
		${EXTIT_HEADER_FILES})

target_link_libraries(
	extit_container_stdimpl
		iv_map)


#
# [lib]extit_util
#
add_library(
	extit_util
		${EXTIT_UTIL_SOURCE_FILES}
		${IV_HEADER_FILES}
		${EXTIT_HEADER_FILES}
		${EXTIT_UTIL_HEADER_FILES})


#
# [lib]stdif_allocator
#
add_library(
	stdif_allocator
		${STDIF_ALLOCATOR_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${STDIF_ALLOCATOR_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

if(EXTIT_PARANOID)
	target_link_libraries(
		stdif_allocator
			iv_util)
endif()


#
# [lib]stdif_allocator_stdimpl
#
add_library(
	stdif_allocator_stdimpl
		${STDIF_ALLOCATOR_STDIMPL_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${STDIF_ALLOCATOR_HEADER_FILES}
		${STDIF_ALLOCATOR_STDIMPL_HEADER_FILES}
		${IV_HEADER_FILES})


#
# [lib]stdif_configurable
#
add_library(
	stdif_configurable
		${STDIF_CONFIGURABLE_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${STDIF_CONFIGURABLE_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

if(EXTIT_PARANOID)
	target_link_libraries(
		stdif_configurable
			iv_util)
endif()


#
# [lib]stdif_configurable_stdimpl
#
add_library(
	stdif_configurable_stdimpl
		${STDIF_CONFIGURABLE_STDIMPL_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${STDIF_CONFIGURABLE_HEADER_FILES}
		${STDIF_CONFIGURABLE_STDIMPL_HEADER_FILES}
		${IV_HEADER_FILES})

target_link_libraries(
	stdif_configurable_stdimpl
		stdif_configurable_util)

if(EXTIT_PARANOID)
	target_link_libraries(
		stdif_configurable_stdimpl
			iv_util)
endif()


#
# [lib]stdif_configurable_util
#
add_library(
	stdif_configurable_util
		${STDIF_CONFIGURABLE_UTIL_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${STDIF_CONFIGURABLE_HEADER_FILES}
		${STDIF_CONFIGURABLE_UTIL_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

if(MINGW AND ${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
	#
	# MinGW printf PRId64 / PRIu64 / PRIxPTR(64-bit) compile check broken
	#
	target_compile_options(
		stdif_configurable_util
			PRIVATE -Wno-error=format)
endif()


#
# [lib]stdif_disposable
#
add_library(
	stdif_disposable
		${STDIF_DISPOSABLE_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${STDIF_DISPOSABLE_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

if(EXTIT_PARANOID)
	target_link_libraries(
		stdif_disposable
			iv_util)
endif()


#
# [lib]stdif_messaging
#
add_library(
	stdif_messaging
		${STDIF_MESSAGING_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${STDIF_MESSAGING_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

if(EXTIT_PARANOID)
	target_link_libraries(
		stdif_messaging
			iv_util)
endif()


#
# [lib]stdif_messaging_stdimpl
#
add_library(
	stdif_messaging_stdimpl
		${STDIF_MESSAGING_STDIMPL_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${STDIF_MESSAGING_HEADER_FILES}
		${STDIF_MESSAGING_STDIMPL_HEADER_FILES}
		${IV_HEADER_FILES})

target_link_libraries(
	stdif_messaging_stdimpl
		iv_map
		extit_util)


#
# [lib]stdif_referenced
#
add_library(
	stdif_referenced
		${STDIF_REFERENCED_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${STDIF_REFERENCED_HEADER_FILES}
		${EXTIT_UTIL_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

target_link_libraries(
	stdif_referenced
		extit_util)

if(EXTIT_PARANOID)
	target_link_libraries(
		stdif_referenced
			iv_util)
endif()


#
# [lib]stdif_resolvable
#
add_library(
	stdif_resolvable
		${STDIF_RESOLVABLE_SOURCE_FILES}
		${EXTIT_HEADER_FILES}
		${STDIF_RESOLVABLE_HEADER_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})

if(EXTIT_PARANOID)
	target_link_libraries(
		stdif_resolvable
			iv_util)
endif()


#
# [lib]iv_map
#
add_library(
	iv_map
		${IV_MAP_SOURCE_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES}
		${IV_MAP_HEADER_FILES})


#
# [lib]iv_repository
#
add_library(
	iv_repository
		${IV_REPOSITORY_SOURCE_FILES}
		${IV_HEADER_FILES}
		${IV_MAP_FILES}
		${IV_REPOSITORY_HEADER_FILES})

target_link_libraries(
	iv_repository
		iv_map
		iv_util)


#
# [lib]iv_util
#
add_library(
	iv_util
		${IV_UTIL_SOURCE_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES})


#
# Platform Specific
#
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_definitions("-D_GNU_SOURCE")
	target_link_libraries(extit_pmodule dl)
endif()

if(MSVC)
	set(TEST_COMPILE_FLAGS "/wd4127")

	set(EXTRA_COMPILE_FLAGS "/W4 /wd4054 /wd4100")

	if(EXTIT_WARNFREE)
		set(EXTRA_COMPILE_FLAGS "${EXTRA_COMPILE_FLAGS} /WX")
	endif()

	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_COMPILE_FLAGS}")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4458")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILE_FLAGS}")

	# Get rid of annoying D9025 warning for /W3 /W4
	string(REPLACE "/W3 " "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
	string(REPLACE "/W3 " "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
else(MSVC)
	set(TEST_COMPILE_FLAGS "")

	set(EXTRA_COMPILE_FLAGS "-Wall -pedantic")

	if(EXTIT_WARNFREE)
		set(EXTRA_COMPILE_FLAGS "${EXTRA_COMPILE_FLAGS} -Werror")
	endif()

	if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-prototypes -Wstrict-prototypes")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_COMPILE_FLAGS}")
	endif()

	if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++98")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILE_FLAGS}")
	endif()
endif(MSVC)


#
# Shared Linking
#
if(BUILD_SHARED_LIBS)
	add_definitions("-DIV_LINK_SHARED")
	add_definitions("-DEXTIT_LINK_SHARED")
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
		stdif_allocator PROPERTIES
			OUTPUT_NAME "stdif_allocator${LIBNAME_POSTFIX}")

	set_target_properties(
		stdif_allocator_stdimpl PROPERTIES
			OUTPUT_NAME "stdif_allocator_stdimpl${LIBNAME_POSTFIX}")

	set_target_properties(
		stdif_disposable PROPERTIES
			OUTPUT_NAME "stdif_disposable${LIBNAME_POSTFIX}")

	set_target_properties(
		stdif_messaging PROPERTIES
			OUTPUT_NAME "stdif_messaging${LIBNAME_POSTFIX}")

	set_target_properties(
		stdif_messaging_stdimpl PROPERTIES
			OUTPUT_NAME "stdif_messaging_stdimpl${LIBNAME_POSTFIX}")

	set_target_properties(
		stdif_referenced PROPERTIES
			OUTPUT_NAME "stdif_referenced${LIBNAME_POSTFIX}")

	set_target_properties(
		stdif_resolvable PROPERTIES
			OUTPUT_NAME "stdif_resolvable${LIBNAME_POSTFIX}")

	set_target_properties(
		extif_util PROPERTIES
			OUTPUT_NAME "extif_util${LIBNAME_POSTFIX}")

	set_target_properties(
		iv_map PROPERTIES
			OUTPUT_NAME "iv_map${LIBNAME_POSTFIX}")

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
		stdif_allocator
		stdif_allocator_stdimpl
		stdif_configurable
		stdif_configurable_stdimpl
		stdif_configurable_util
		stdif_disposable
		stdif_messaging
		stdif_messaging_stdimpl
		stdif_referenced
		stdif_resolvable
		extit_container
		extit_container_stdimpl
		extit_pmodule
		extit_util
		iv_map
		iv_repository
		iv_util
	DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(
	FILES
		${EXTIT_HEADER_FILES}
		${EXTIT_CONTAINER_HEADER_FILES}
		${EXTIT_CONTAINER_STDIMPL_HEADER_FILES}
		${EXTIT_PMODULE_HEADER_FILES}
		${EXTIT_UTIL_HEADER_FILES}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/extit)

install(
	FILES
		${STDIF_HEADER_FILES}
		${STDIF_ALLOCATOR_HEADER_FILES}
		${STDIF_ALLOCATOR_STDIMPL_HEADER_FILES}
		${STDIF_CONFIGURABLE_HEADER_FILES}
		${STDIF_CONFIGURABLE_STDIMPL_HEADER_FILES}
		${STDIF_CONFIGURABLE_UTIL_HEADER_FILES}
		${STDIF_DISPOSABLE_HEADER_FILES}
		${STDIF_MESSAGING_HEADER_FILES}
		${STDIF_MESSAGING_STDIMPL_HEADER_FILES}
		${STDIF_REFERENCED_HEADER_FILES}
		${STDIF_RESOLVABLE_HEADER_FILES}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/if)

install(
	FILES
		${IV_HEADER_FILES}
		${IV_MAP_HEADER_FILES}
		${IV_REPOSITORY_HEADER_FILES}
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
		sample_stdif_allocator_plugin SHARED
			sample/stdif_allocator/plugin.c
			${EXTIT_HEADER_FILES}
			${EXTIT_ALLOCATOR_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	set_target_properties(
		sample_stdif_allocator_plugin PROPERTIES
			PREFIX "")

	target_link_libraries(
		sample_stdif_allocator_plugin
			stdif_allocator
			extit_container
			iv_util)


	#
	# Allocator Interface Server
	#
	add_executable(
		sample_stdif_allocator_server
			sample/stdif_allocator/server.c
			${EXTIT_HEADER_FILES}
			${EXTIT_ALLOCATOR_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_stdif_allocator_server
			stdif_allocator_stdimpl
			extit_container_stdimpl
			extit_pmodule)


	#
	# Configurable Interface
	#
	add_executable(
		sample_stdif_configurable
			sample/stdif_configurable/client.c
			sample/stdif_configurable/scan_service.c
			sample/stdif_configurable/scan_service.h
			${EXTIT_HEADER_FILES}
			${STDIF_CONFIGURABLE_HEADER_FILES}
			${STDIF_CONFIGURABLE_STDIMPL_HEADER_FILES}
			${STDIF_CONFIGURABLE_UTIL_HEADER_FILES}
			${IV_HEADER_FILES})

	target_link_libraries(
		sample_stdif_configurable
			stdif_configurable
			stdif_configurable_stdimpl
			stdif_configurable_util)


	#
	# Configurable Interface (List Properties)
	#
	add_executable(
		sample_stdif_configurable_proplist
			sample/stdif_configurable_proplist/dump_props.c
			${EXTIT_HEADER_FILES}
			${STDIF_CONFIGURABLE_HEADER_FILES}
			${STDIF_CONFIGURABLE_STDIMPL_HEADER_FILES}
			${STDIF_CONFIGURABLE_UTIL_HEADER_FILES}
			${IV_HEADER_FILES})

	target_link_libraries(
		sample_stdif_configurable_proplist
			stdif_configurable
			stdif_configurable_stdimpl
			stdif_configurable_util)


	#
	# Disposable Interface
	#
	add_executable(
		sample_stdif_disposable
			sample/stdif_disposable/client.c
			sample/stdif_disposable/item.c
			sample/stdif_disposable/item.h
			sample/stdif_disposable/itemsource.c
			sample/stdif_disposable/itemsource.h
			${EXTIT_HEADER_FILES}
			${STDIF_DISPOSABLE_HEADER_FILES}
			${STDIF_DISPOSABLE_IMPL_HEADER_FILES}
			${IV_HEADER_FILES})

	target_link_libraries(
		sample_stdif_disposable
			stdif_disposable)


	#
	# Messaging Interface (alarm)
	#
	add_executable(
		sample_stdif_messaging_alarm
			sample/stdif_messaging/alarm.h
			sample/stdif_messaging/demo.c
			${EXTIT_HEADER_FILES}
			${EXTIT_MESSAGING_HEADER_FILES}
			${EXTIT_MESSAGING_STDIMPL_HEADER_FILES}
			${IV_HEADER_FILES})

	target_link_libraries(
		sample_stdif_messaging_alarm
			stdif_messaging
			stdif_messaging_stdimpl)


	#
	# Refcount Interface
	#
	add_executable(
		sample_stdif_referenced
			sample/stdif_referenced/client.c
			sample/stdif_referenced/myobj.h
			sample/stdif_referenced/provider.c
			sample/stdif_referenced/provider.h
			sample/stdif_referenced/worklist.c
			sample/stdif_referenced/worklist.h
			${EXTIT_HEADER_FILES}
			${STDIF_REFERENCED_HEADER_FILES}
			${EXTIT_UTIL_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_stdif_referenced
			stdif_referenced)


	#
	# Resolvable Interface
	#
	add_executable(
		sample_stdif_resolvable
			sample/stdif_resolvable/client.c
			sample/stdif_resolvable/myobj.c
			sample/stdif_resolvable/myobj.h
			sample/stdif_resolvable/myobj_client.c
			sample/stdif_resolvable/myobj_priv.h
			${EXTIT_HEADER_FILES}
			${STDIF_REFERENCED_HEADER_FILES}
			${STDIF_REFERENCED_IMPL_HEADER_FILES}
			${STDIF_CONFIGURABLE_HEADER_FILES}
			${STDIF_CONFIGURABLE_IMPL_HEADER_FILES}
			${STDIF_CONFIGURABLE_STDIMPL_HEADER_FILES}
			${STDIF_RESOLVABLE_HEADER_FILES}
			${STDIF_RESOLVABLE_IMPL_HEADER_FILES}
			${EXTIT_UTIL_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		sample_stdif_resolvable
			extit_util
			stdif_referenced
			stdif_resolvable
			stdif_configurable
			stdif_configurable_stdimpl
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
			iv_map
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
				"PERSISTENCE_ABI_TARGET=PERSISTENCE_ABI_1_0")

	target_link_libraries(
		sample_multiver_server_1_0
			extit_container_stdimpl
			extit_pmodule
			iv_map
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
				"PERSISTENCE_ABI_TARGET=PERSISTENCE_ABI_1_1")

	target_link_libraries(
		sample_multiver_server_1_1
			extit_container_stdimpl
			extit_pmodule
			iv_map
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
				"PERSISTENCE_ABI_TARGET=PERSISTENCE_ABI_1_2")

	target_link_libraries(
		sample_multiver_server_1_2
			extit_container_stdimpl
			extit_pmodule
			iv_map
			iv_repository)


	add_library(
		sample_multiver_plugin_1_0 SHARED
			sample/multiver/multiver_plugin.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_compile_definitions(
		sample_multiver_plugin_1_0
			PRIVATE "-DPERSISTENCE_ABI_TARGET=PERSISTENCE_ABI_1_0")

	set_target_properties(
		sample_multiver_plugin_1_0 PROPERTIES
			PREFIX "")

	target_link_libraries(
		sample_multiver_plugin_1_0
			extit_container
			iv_util)


	add_library(
		sample_multiver_plugin_1_1 SHARED
			sample/multiver/multiver_plugin.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_compile_definitions(
		sample_multiver_plugin_1_1
			PRIVATE "-DPERSISTENCE_ABI_TARGET=PERSISTENCE_ABI_1_1")

	set_target_properties(
		sample_multiver_plugin_1_1 PROPERTIES
			PREFIX "")

	target_link_libraries(
		sample_multiver_plugin_1_1
			extit_container
			iv_util)


	add_library(
		sample_multiver_plugin_1_2 SHARED
			sample/multiver/multiver_plugin.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_compile_definitions(
		sample_multiver_plugin_1_2
			PRIVATE "-DPERSISTENCE_ABI_TARGET=PERSISTENCE_ABI_1_2")

	set_target_properties(
		sample_multiver_plugin_1_2 PROPERTIES
			PREFIX "")

	target_link_libraries(
		sample_multiver_plugin_1_2
			extit_container
			iv_util)


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
			extit_container_stdimpl
			extit_pmodule)


	add_library(
		sample_scan_plugin_pie SHARED
			sample/scan/recipe_pie.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	set_target_properties(
		sample_scan_plugin_pie PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-pie")

	target_link_libraries(
		sample_scan_plugin_pie
			iv_util)


	add_library(
		sample_scan_plugin_tea SHARED
			sample/scan/recipe_tea.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	set_target_properties(
		sample_scan_plugin_tea PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-tea")

	target_link_libraries(
		sample_scan_plugin_tea
			iv_util)


	add_library(
		sample_scan_plugin_tacos SHARED
			sample/scan/recipe_tacos.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	set_target_properties(
		sample_scan_plugin_tacos PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-tacos")

	target_link_libraries(
		sample_scan_plugin_tacos
			iv_util)


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
			extit_container_stdimpl
			extit_pmodule)


	add_library(
		sample_simple_plugin SHARED
			sample/simple/simple_plugin.c
			${EXTIT_HEADER_FILES}
			${EXTIT_PMODULE_HEADER_FILES}
			${EXTIT_CONTAINER_HEADER_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	set_target_properties(
		sample_simple_plugin PROPERTIES
			PREFIX "")

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

	target_compile_options(
		test_extit_bool_t
			PRIVATE ${TEST_COMPILE_FLAGS})

	add_executable(
		test_extit_refcount
			tests/extit_refcount/test_refcount.c
			${EXTIT_HEADER_FILES}
			${EXTIT_UTIL_HEADER_FILES})

	target_compile_options(
		test_extit_refcount
			PRIVATE ${TEST_COMPILE_FLAGS})

	target_link_libraries(
		test_extit_refcount
			extit_util)

	add_executable(
		test_iv_version
			tests/iv_version/test_iv_version.c
			${IV_HEADER_FILES})

	target_compile_options(
		test_iv_version
			PRIVATE ${TEST_COMPILE_FLAGS})

	add_executable(
		test_iv_bool_t
			tests/iv_bool_t/test_iv_bool.c
			${IV_HEADER_FILES})

	target_compile_options(
		test_iv_bool_t
			PRIVATE ${TEST_COMPILE_FLAGS})

	if(IV_COMPAT)
		add_executable(
			test_iv_keymap
				tests/iv_keymap/test_keymap.c
				${IV_HEADER_FILES}
				${IV_UTIL_HEADER_FILES})

		target_compile_options(
			test_iv_keymap
				PRIVATE ${TEST_COMPILE_FLAGS})

		target_link_libraries(
			test_iv_keymap
				iv_util)
	endif()

	add_executable(
		test_iv_map
			tests/iv_map/test_iv_map.c
			${IV_HEADER_FILES}
			${IV_MAP_HEADER_FILES})

	target_compile_options(
		test_iv_map
			PRIVATE ${TEST_COMPILE_FLAGS})

	target_link_libraries(
		test_iv_map
			iv_map)

	add_executable(
		test_iv_matches
			tests/iv_matches/test_iv_matches.c
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_compile_options(
		test_iv_matches
			PRIVATE ${TEST_COMPILE_FLAGS})

	target_link_libraries(
		test_iv_matches
			iv_util)
endif(EXTIT_COMPILE_TESTS)

