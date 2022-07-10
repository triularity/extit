
Interface Versioning

When compiling code that will link against shared ExtIt/stdif  libraries, include the compiler flag: -DIV_LINK_SHARED


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


COMPILING
---------

A C99 build environment is required (or one with augmented stdint.h / stdbool.h files).

This project uses Cmake (2.8.12+). Configuration options are:

	IV_PARANOID		Enable runtime sanity checks.

	IV_COMPAT		Enabled deprecated compatibility code.

	IV_DEBUG		Enabled runtime debugging.

	IV_WARNFREE		Cause the build to fail on compile warnings.

	IV_COMPILE_EXAMPLES	Compile the example code.

	IV_COMPILE_TESTS	Compile the unit tests.


FILES
-----

src/			Source code.
src/include/		Public header files.
examples/		Example code.
tests/			Unit tests.
docs/			Documentation.

