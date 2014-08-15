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
	set(DEFAULT_LIB_LOADER "dlopen")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "BSD$")
	set(DEFAULT_HAVE_DLFUNC TRUE)
endif()

set(EXTIT_PARANOID TRUE CACHE BOOL "Enable Paranoid Code Checks")
set(EXTIT_DEBUG TRUE CACHE BOOL "Enable Runtime Debugging")
set(EXTIT_WITH_CXX FALSE CACHE BOOL "Enable C++ Wrappers")
set(EXTIT_COMPILE_SAMPLES FALSE CACHE BOOL "Compile Sample Programs")
set(EXTIT_LIB_LOADER ${DEFAULT_LIB_LOADER} CACHE STRING "Library Loader (dlopen|win32|dylib)")
set(EXTIT_WCHAR ${DEFAULT_WCHAR} CACHE BOOL "Enable wchar_t support")
set(EXTIT_HAVE_DLFUNC ${DEFAULT_HAVE_DLFUNC} CACHE BOOL "Platform supports dlfunc()")


include_directories(BEFORE src/include)

set(EXTIT_SOURCE_FILES src/container/container_common.c)

set(EXTIT_IR_SOURCE_FILES src/ir/ir.c)


#
# Library Loader
#
if(EXTIT_LIB_LOADER STREQUAL "dlopen")
	set(EXTIT_SOURCE_FILES
		${EXTIT_SOURCE_FILES} src/container/container_dlopen.c)
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

	set(EXTIT_IR_SOURCE_FILES
		${EXTIT_IR_SOURCE_FILES} src/ir/ir_cxx.cc)
endif()


#
# Configuration Options
#
if(EXTIT_PARANOID)
	add_definitions("-DEXTIT_PARANOID")
endif()

if(EXTIT_DEBUG)
	add_definitions("-DEXTIT_DEBUG")
endif()

if(EXTIT_WCHAR)
	add_definitions("-DEXTIT_WCHAR")
endif()

if(EXTIT_HAVE_DLFUNC)
	add_definitions("-DEXTIT_HAVE_DLFUNC")
endif()


add_library(extit ${EXTIT_SOURCE_FILES})

add_library(extit_ir ${EXTIT_IR_SOURCE_FILES})


#
# Platform Specific
#
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_definitions("-D_GNU_SOURCE")
	target_link_libraries(extit dl)
endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	add_compile_options("-Wall" "-pedantic")
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
		extit PROPERTIES
			OUTPUT_NAME "extit${LIBNAME_POSTFIX}")

	set_target_properties(
		extit_ir PROPERTIES
			OUTPUT_NAME "extit_ir${LIBNAME_POSTFIX}")
endif(DEFINED LIBNAME_POSTFIX)


#
# Install
#
install(
	TARGETS
		extit
		extit_ir
	DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(
	FILES
		src/include/extit/base.h
		src/include/extit/container.h
		src/include/extit/ir.h
		src/include/extit/platform.h
		src/include/extit/plugin_spi.h
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/extit)


#
# Sample Code
#
if(EXTIT_COMPILE_SAMPLES)
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

	target_link_libraries(sample_scan_plugin_pie extit)


	add_library(
		sample_scan_plugin_tea SHARED
			sample/scan/recipe_tea.c)

	set_target_properties(
		sample_scan_plugin_tea PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-tea")

	target_link_libraries(sample_scan_plugin_tea extit)


	add_library(
		sample_scan_plugin_tacos SHARED
			sample/scan/recipe_tacos.c)

	set_target_properties(
		sample_scan_plugin_tacos PROPERTIES
			PREFIX ""
			OUTPUT_NAME "recipe-tacos")

	target_link_libraries(sample_scan_plugin_tacos extit)


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

	target_link_libraries(sample_simple_plugin extit)
endif(EXTIT_COMPILE_SAMPLES)

