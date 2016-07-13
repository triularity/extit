/*
 * @(#) test_iv_bool.c
 *
 * Unit test for iv_bool_t.
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <iv/base.h>


int
main(int argc, char **argv)
{
	int	rc;


	rc = 0;


	if(!IV_TRUE)
	{
		fprintf(stderr,
			"Test FAILED - !IV_TRUE\n");

		rc = 1;
	}

	if(IV_FALSE)
	{
		fprintf(stderr,
			"Test FAILED - IV_FALSE\n");

		rc = 1;
	}


	if(rc == 0)
		fprintf(stderr, "Tests PASSED - iv_bool_t\n");

	return rc;
}
