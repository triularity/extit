project(iv)

cmake_minimum_required(VERSION 2.8.12)

#
# Defaults
#
set(IV_PARANOID TRUE CACHE BOOL "Enable Paranoid Code Checks")
set(IV_DEBUG TRUE CACHE BOOL "Enable Runtime Debugging")
set(IV_WARNFREE FALSE CACHE BOOL "Enable Error on Compile Warnings")
set(IV_COMPILE_EXAMPLES FALSE CACHE BOOL "Compile Example Code")
set(IV_COMPILE_TESTS FALSE CACHE BOOL "Compile Unit Tests")
set(IV_COMPAT FALSE CACHE BOOL "Enable Backward Compatibility")


include_directories(BEFORE src/include)


# IV core
set(IV_HEADER_FILES 
	src/include/iv/base.h
	src/include/iv/version.h)


# IV idmap
set(IV_IDMAP_HEADER_FILES 
	src/include/iv/idmap.h)


set(IV_IDMAP_SOURCE_FILES
	src/idmap.c)

# IV map
if(IV_COMPAT)
	set(IV_MAP_HEADER_FILES
		${IV_MAP_HEADER_FILES}
		src/include/iv/map.h)

	set(IV_MAP_SOURCE_FILES
		${IV_MAP_SOURCE_FILES}
		src/map.c)
endif()


# IV repository
set(IV_REPOSITORY_HEADER_FILES 
	src/include/iv/repository.h)

set(IV_REPOSITORY_SOURCE_FILES
	src/repository/cleanup.c
	src/repository/create.c
	src/repository/destroy.c
	src/repository/get.c
	src/repository/query.c
	src/repository/remove.c
	src/repository/set.c)


# IV utilities
set(IV_UTIL_HEADER_FILES 
	src/include/iv/util.h)

set(IV_UTIL_SOURCE_FILES
	src/util/matches.c)

if(IV_COMPAT)
	set(IV_UTIL_SOURCE_FILES
		${IV_UTIL_SOURCE_FILES}
		src/util/keymap.c)
endif()


#
# Configuration Options
#
if(IV_PARANOID)
	add_definitions("-DIV_PARANOID")
endif()

if(IV_DEBUG)
	add_definitions("-DIV_REPOSITORY_DEBUG")
endif()

if(IV_COMPAT)
	add_definitions("-DIV_COMPAT")
endif()


#
# [lib]iv_idmap
#
add_library(
	iv_idmap
		${IV_IDMAP_SOURCE_FILES}
		${IV_HEADER_FILES}
		${IV_UTIL_HEADER_FILES}
		${IV_IDMAP_HEADER_FILES})


#
# [lib]iv_map
#
if(IV_COMPAT)
	add_library(
		iv_map
			${IV_MAP_SOURCE_FILES}
			${IV_HEADER_FILES}
			${IV_UTIL_HEADER_FILES}
			${IV_MAP_HEADER_FILES})
endif()


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
		iv_idmap
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
endif()

if(MSVC)
	set(TEST_COMPILE_FLAGS "/wd4127")

	set(EXTRA_COMPILE_FLAGS "/W4 /wd4054 /wd4100")

	if(IV_WARNFREE)
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

	if(IV_WARNFREE)
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
		iv_idmap PROPERTIES
			OUTPUT_NAME "iv_idmap${LIBNAME_POSTFIX}")

	if(IV_COMPAT)
		set_target_properties(
			iv_map PROPERTIES
				OUTPUT_NAME "iv_map${LIBNAME_POSTFIX}")
	endif()

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
		iv_idmap
		iv_repository
		iv_util
	DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if(IV_COMPAT)
	install(
		TARGETS
			iv_map
		DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()


install(
	FILES
		${IV_HEADER_FILES}
		${IV_IDMAP_HEADER_FILES}
		${IV_REPOSITORY_HEADER_FILES}
		${IV_UTIL_HEADER_FILES}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/iv)

if(IV_COMPAT)
	install(
		FILES
			${IV_HEADER_FILES}
			${IV_MAP_HEADER_FILES}
			${IV_REPOSITORY_HEADER_FILES}
			${IV_UTIL_HEADER_FILES}
		DESTINATION ${CMAKE_INSTALL_PREFIX}/include/iv)
endif()


#
# Sample Code
#
if(IV_COMPILE_EXAMPLES)
	#
	# Interface Repository
	#
	add_executable(
		example_iv_repository
			examples/iv_repository/repository.c
			${IV_HEADER_FILES}
			${IV_REPOSITORY_HEADER_FILES}
			${IV_UTIL_HEADER_FILES})

	target_link_libraries(
		example_iv_repository
			iv_idmap
			iv_repository)
endif(IV_COMPILE_EXAMPLES)


if(IV_COMPILE_TESTS)
	add_executable(
		test_iv_version
			tests/iv_version/test_iv_version.c
			${IV_HEADER_FILES})

	target_compile_options(
		test_iv_version
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
		test_iv_idmap
			tests/iv_idmap/test_iv_idmap.c
			${IV_HEADER_FILES}
			${IV_MAP_HEADER_FILES})

	target_compile_options(
		test_iv_idmap
			PRIVATE ${TEST_COMPILE_FLAGS})

	target_link_libraries(
		test_iv_idmap
			iv_idmap)

	if(IV_COMPAT)
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
	endif()

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
endif(IV_COMPILE_TESTS)

