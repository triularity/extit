
EXTend-IT is a lightweight, interface versioning based plugin library.

When compiling code that will link against shared ExtIt/stdif  libraries, include the compiler flag: -DEXTIT_LINK_SHARED


Supported OS's:
	Windows (tested on Windows 7, 64-bit)
		Visual Studio 2015 (MSVC 14) 32-bit/64-bit
		MinGW/gcc 4.8 32-bit
		MinGW/gcc 4.9 64-bit
	FreeBSD (tested on 10.x, 64-bit)
		clang 3.4 64-bit
		gcc 6.4 64-bit
	FreeBSD (tested on 11.x, 64-bit)
		clang 4.0 64-bit
		clang 5.0 64-bit
	NetBSD (tested on 6.1.5, 64-bit)
		gcc 4.5 64-bit
	OpenBSD (tested on 5.7, 64-bit)
		gcc 4.2 64-bit
	Linux  (tested on CentOS 7, 64-bit)
		gcc 4.8 64-bit


Planned OS's:
	macOS


This package contains 3 main components:
 * iv - The interface version library
 * extit - The core plugin/extention library.
 * stdif - Standard interfaces.


COMPILING
---------

A C99 build environment is required (or one with augmented stdint.h / stdbool.h files).

This project uses Cmake (2.8.12+). Configuration options are:

	EXTIT_PARANOID		Enable runtime sanity checks.

	EXTIT_COMPAT		Enabled deprecated compatibility code.

	EXTIT_DEBUG		Enabled runtime debugging.

	EXTIT_WARNFREE		Cause the build to fail on compile warnings.

	EXTIT_COMPILE_EXAMPLES	Compile the example code.

	EXTIT_COMPILE_TESTS	Compile the unit tests.

	EXTIT_LIB_LOADER [*]	The dynamic library API ("dl", "win32").

	EXTIT_WCHAR [*]		Enable wchar_t support code.

	EXTIT_WITH_CXX		Compile C++ client wrappers.

	EXTIT_HAVE_DLFUNC [*]	Enable dlfunc() support (dl load only).

	EXTIT_MALLOC_0_SUCCEEDS	Calling malloc(0) doesn't return NULL.

[*] - Auto detected.


FILES
-----

src/include/		Public header files.
src/iv/			IV source code.
src/extit/		ExtIt source code.
src/stdif/		Standard interfaces source code.
examples/		Example code.
tests/			Unit tests.
docs/			Documentation.

