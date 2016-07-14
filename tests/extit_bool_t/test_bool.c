/*
 * @(#) test_extit_bool_t.c
 *
 * Unit test for extit_bool_t.
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <extit/base.h>


int
main(int argc, char **argv)
{
	int	rc;


	rc = 0;


	if(!EXTIT_TRUE)
	{
		fprintf(stderr,
			"Test FAILED - !EXTIT_TRUE\n");

		rc = 1;
	}

	if(EXTIT_FALSE)
	{
		fprintf(stderr,
			"Test FAILED - EXTIT_FALSE\n");

		rc = 1;
	}

	if(rc == 0)
		fprintf(stderr, "Tests PASSED - extit_bool_t\n");

	return rc;
}
