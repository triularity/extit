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
set(EXTIT_WITH_CXX FALSE CACHE BOOL "Enable C++ Wrappers")
set(EXTIT_COMPILE_SAMPLES FALSE CACHE BOOL "Compile Sample Programs")
set(EXTIT_LIB_LOADER ${DEFAULT_LIB_LOADER} CACHE STRING "Library Loader (dl|win32|dylib)")
set(EXTIT_WCHAR ${DEFAULT_WCHAR} CACHE BOOL "Enable wchar_t support")
set(EXTIT_HAVE_DLFUNC ${DEFAULT_HAVE_DLFUNC} CACHE BOOL "Platform supports dlfunc()")
set(EXTIT_COMPAT TRUE CACHE BOOL "Enable Backward Compatibility")


include_directories(BEFORE src/include)


set(IV_HEADER_FILES 
	src/include/iv/base.h
	src/include/iv/repository.h)

set(EXTIT_HEADER_FILES 
	src/include/extit/base.h
	src/include/extit/container.h
	src/include/extit/platform.h
	src/include/extit/plugin_spi.h)

set(IV_REPOSITORY_SOURCE_FILES src/iv/repository.c)

set(EXTIT_SOURCE_FILES src/container/container_common.c)

if(EXTIT_COMPAT)
	set(EXTIT_HEADER_FILES
		${EXTIT_HEADER_FILES} src/include/extit/ir.h)

	set(EXTIT_IR_SOURCE_FILES src/ir/ir.c)
endif()


#
# Library Loader
#
if(EXTIT_LIB_LOADER STREQUAL "dl")
	set(EXTIT_SOURCE_FILES
		${EXTIT_SOURCE_FILES} src/container/container_dl.c)
elseif(EXTIT_LIB_LOADER STREQUAL "win32")
	set(EXTIT_SOURCE_FILES
		${EXTIT_SOURCE_FILES} src/container/container_win32.c)
elseif(EXTIT_LIB_LOADER STREQUAL "dylib")
	set(EXTIT_SOURCE_FILES
		${EXTIT_SOURCE_FILES} src/container/container_dylib.c)
else()
	message(FATAL_ERROR "Unsupported library loader: ${EXTIT_LIB_LOADER}")
endif()


#
# C++ Support
#
if(EXTIT_WITH_CXX)
	set(EXTIT_SOURCE_FILES
		${EXTIT_SOURCE_FILES} src/container/container_cxx.cc)

	if(EXTIT_COMPAT)
		set(EXTIT_IR_SOURCE_FILES
			${EXTIT_IR_SOURCE_FILES} src/ir/ir_cxx.cc)
	endif()
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


add_library(iv_repository ${IV_REPOSITORY_SOURCE_FILES})

add_library(extit ${EXTIT_SOURCE_FILES})

if(EXTIT_COMPAT)
	add_library(extit_ir ${EXTIT_IR_SOURCE_FILES})
	target_link_libraries(extit_ir iv_repository)
endif()


#
# Platform Specific
#
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_definitions("-D_GNU_SOURCE")
	target_link_libraries(extit dl)
endif()

if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")
elseif(MSVC)
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
		iv_repository PROPERTIES
			OUTPUT_NAME "iv_repository${LIBNAME_POSTFIX}")

	set_target_properties(
		extit PROPERTIES
			OUTPUT_NAME "extit${LIBNAME_POSTFIX}")

	if(EXTIT_COMPAT)
		set_target_properties(
			extit_ir PROPERTIES
				OUTPUT_NAME "extit_ir${LIBNAME_POSTFIX}")
	endif()
endif(DEFINED LIBNAME_POSTFIX)


#
# Install
#
install(
	TARGETS
		iv_repository
		extit
	DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if(EXTIT_COMPAT)
	install(
		TARGETS
			extit_ir
		DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()

install(
	FILES ${IV_HEADER_FILES}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/iv)

install(
	FILES ${EXTIT_HEADER_FILES}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/extit)


#
# Sample Code
#
if(EXTIT_COMPILE_SAMPLES)

	#
	# Interface Repository
	#
	add_executable(
		sample_iv_repository
			sample/iv_repository/repository.c)

	target_link_libraries(sample_iv_repository iv_repository)


	#
	# Multi-Version
	#
	add_executable(
		sample_multiver_server_1_0
			sample/multiver/persistence_impl.c
			sample/multiver/multiver_server.c)

	set_target_properties(
		sample_multiver_server_1_0 PROPERTIES
			COMPILE_DEFINITIONS
				"PERSISTENCE_INTERFACE_TARGET=IV_VERSION(1,0)")

	target_link_libraries(sample_multiver_server_1_0 extit iv_repository)


	add_executable(
		sample_multiver_server_1_1
			sample/multiver/persistence_impl.c
			sample/multiver/multiver_server.c)

	set_target_properties(
		sample_multiver_server_1_1 PROPERTIES
			COMPILE_DEFINITIONS
				"PERSISTENCE_INTERFACE_TARGET=IV_VERSION(1,1)")

	target_link_libraries(sample_multiver_server_1_1 extit iv_repository)


	add_executable(
		sample_multiver_server_1_2
			sample/multiver/persistence_impl.c
			sample/multiver/multiver_server.c)

	set_target_properties(
		sample_multiver_server_1_2 PROPERTIES
			COMPILE_DEFINITIONS
				"PERSISTENCE_INTERFACE_TARGET=IV_VERSION(1,2)")

	target_link_libraries(sample_multiver_server_1_2 extit iv_repository)


	add_library(
		sample_multiver_plugin_1_0 SHARED
			sample/multiver/multiver_plugin.c)

	set_target_properties(
		sample_multiver_plugin_1_0 PROPERTIES
			COMPILE_DEFINITIONS
				"PERSISTENCE_INTERFACE_TARGET=IV_VERSION(1,0)")



	add_library(
		sample_multiver_plugin_1_1 SHARED
			sample/multiver/multiver_plugin.c)

	set_target_properties(
		sample_multiver_plugin_1_1 PROPERTIES
			COMPILE_DEFINITIONS
				"PERSISTENCE_INTERFACE_TARGET=IV_VERSION(1,1)")



	add_library(
		sample_multiver_plugin_1_2 SHARED
			sample/multiver/multiver_plugin.c)

	set_target_properties(
		sample_multiver_plugin_1_2 PROPERTIES
			COMPILE_DEFINITIONS
			"PERSISTENCE_INTERFACE_TARGET=IV_VERSION(1,2)")


	#
	# Plugin Scanning
	#
	add_executable(
		sample_scan_server
			sample/scan/recipe_server.c)

	target_link_libraries(sample_scan_server extit)


	add_library(
		sample_scan_plugin_pie SHARED
			sample/scan/recipe_pie.c)

	set_target_properties(
		sample_scan_plugin_pie PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-pie")


	add_library(
		sample_scan_plugin_tea SHARED
			sample/scan/recipe_tea.c)

	set_target_properties(
		sample_scan_plugin_tea PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-tea")


	add_library(
		sample_scan_plugin_tacos SHARED
			sample/scan/recipe_tacos.c)

	set_target_properties(
		sample_scan_plugin_tacos PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-tacos")


	#
	# Simple Plugin
	#
	add_executable(
		sample_simple_server
			sample/simple/simple_server.c)

	target_link_libraries(sample_simple_server extit)

	add_library(
		sample_simple_plugin SHARED
			sample/simple/simple_plugin.c)
endif(EXTIT_COMPILE_SAMPLES)

