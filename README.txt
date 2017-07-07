
EXTend-IT is a lightweight, interface versioning based plugin library.


Supported OS's:
	Windows (tested on Windows 7, 64-bit)
		MSVC 18 (Visual Studio 12) 32-bit/64-bit
		MinGW 32-bit
	FreeBSD  (tested on 10.x, 64-bit)
		clang 3.4 64-bit
	NetBSD (tested on 6.1.5, 64-bit)
		gcc 4.5 64-bit
	OpenBSD (tested on 5.7, 64-bit)
		gcc 4.2 64-bit
	Linux  (tested on CentOS 7, 64-bit)
		gcc 4.8 64-bit


Planned OS's:
	macOS


This package contains 3 main components:
 * IV - The interface version library
 * ExtIt - The core plugin/extention library.
 * IF - The standard interfaces.


COMPILING
---------

This project uses Cmake (2.8+). Configuration options are:

	EXTIT_PARANOID		Enable runtime sanity checks.

	EXTIT_COMPAT		Enabled deprecated compatibility code.

	EXTIT_DEBUG		Enabled runtime debugging.

	EXTIT_WARNFREE		Cause the build to fail on compile warnings.

	EXTIT_COMPILE_SAMPLES	Compile the sample code.

	EXTIT_COMPILE_TESTS	Compile the unit tests.

	EXTIT_LIB_LOADER [*]	The dynamic library API ("dl", "win32").

	EXTIT_WCHAR [*]		Enable wchar_t support code.

	EXTIT_HAVE_DLFUNC [*]	Enable dlfunc() support (dl load only).

[*] - Auto detected.


FILES
-----

src/include/		Public header files.
src/iv/			IV source code.
src/if/			IF source code.
src/extit/		ExtIt source code.
samples/		Sample code.
tests/			Unit tests.

