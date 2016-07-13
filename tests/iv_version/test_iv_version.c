/*
 * @(#) test_iv_version.c
 *
 * Unit test for IV_VERSION(), IV_VERSION_MAJOR(), and IV_VERSION_MINOR().
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <iv/base.h>


int
main(int argc, char **argv)
{
	int	rc;


	rc = 0;


	/*
	 * IV_VERSION_NONE
	 */
	if(IV_VERSION_NONE != 0)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION_NONE != 0\n");

		rc = 1;
	}

	if(IV_VERSION(0, 0) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(0, 0) != IV_VERSION_NONE\n");

		rc = 1;
	}


	/*
	 * Major/Minor
	 */
	if(IV_VERSION_MAJOR(IV_VERSION(0, 0)) != 0)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION_MAJOR(IV_VERSION(0, 0)) != 0\n");

		rc = 1;
	}

	if(IV_VERSION_MAJOR(IV_VERSION(1, 0)) != 1)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION_MAJOR(IV_VERSION(1, 0)) != 1\n");

		rc = 1;
	}

	if(IV_VERSION_MAJOR(IV_VERSION(2, 0)) != 2)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION_MAJOR(IV_VERSION(2, 0)) != 2\n");

		rc = 1;
	}

	if(IV_VERSION_MINOR(IV_VERSION(0, 0)) != 0)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION_MINOR(IV_VERSION(0, 0)) != 0\n");

		rc = 1;
	}

	if(IV_VERSION_MINOR(IV_VERSION(0, 1)) != 1)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION_MINOR(IV_VERSION(0, 1)) != 1\n");

		rc = 1;
	}

	if(IV_VERSION_MINOR(IV_VERSION(0, 2)) != 2)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION_MINOR(IV_VERSION(0, 2)) != 2\n");

		rc = 1;
	}


	/*
	 * Values
	 */
	if(IV_VERSION(1, 0) != 0x00010000)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(1, 0) != 0x00010000\n");

		rc = 1;
	}

	if(IV_VERSION(2, 0) != 0x00020000)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(2, 0) != 0x00020000\n");

		rc = 1;
	}

	if(IV_VERSION(3, 0) != 0x00030000)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(3, 0) != 0x00030000\n");

		rc = 1;
	}


	if(IV_VERSION(0, 1) != 0x00000001)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(0, 1) != 0x00000001\n");

		rc = 1;
	}

	if(IV_VERSION(0, 2) != 0x00000002)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(0, 2) != 0x00000002\n");

		rc = 1;
	}

	if(IV_VERSION(0, 3) != 0x00000003)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(0, 3) != 0x00000003\n");

		rc = 1;
	}

	if(IV_VERSION(1, 3) != 0x00010003)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(1, 3) != 0x00010003\n");

		rc = 1;
	}

	if(IV_VERSION(4, 1) != 0x00040001)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(4, 1) != 0x00040001\n");

		rc = 1;
	}


	/*
	 * Range clipping
	 */
	if(IV_VERSION(0x10000, 0) != 0x00000000)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(0x10000, 0) != 0x00000000\n");

		rc = 1;
	}

	if(IV_VERSION(0, 0x10000) != 0x00000000)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(0, 0x10000) != 0x00000000\n");

		rc = 1;
	}

	if(IV_VERSION(0x10005, 0) != 0x00050000)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(0x10005, 0) != 0x00050000\n");

		rc = 1;
	}

	if(IV_VERSION(0, 0x10005) != 0x00000005)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(0, 0x10005) != 0x00000005\n");

		rc = 1;
	}

	if(IV_VERSION(-1, 0) != 0xFFFF0000)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(-1, 0) != 0xFFFF0000\n");

		rc = 1;
	}

	if(IV_VERSION(0, -1) != 0x0000FFFF)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(0, -1) != 0x0000FFFF\n");

		rc = 1;
	}

	if(IV_VERSION(-2, 0) != 0xFFFE0000)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(-2, 0) != 0xFFFE0000\n");

		rc = 1;
	}

	if(IV_VERSION(0, -2) != 0x0000FFFE)
	{
		fprintf(stderr,
			"Test FAILED - IV_VERSION(0, -2) != 0x0000FFFE\n");

		rc = 1;
	}


	if(rc == 0)
		fprintf(stderr, "Tests PASSED - iv_version\n");

	return rc;
}
