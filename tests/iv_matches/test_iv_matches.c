/*
 * @(#) test_iv_matches.c
 *
 * Unit test for iv_matches().
 */

#include <stdio.h>

#include <iv/base.h>
#include <iv/util.h>


int
main(int argc, char **argv)
{
	int	rc;


	rc = 0;

	/*
	 * 0.x matching
	 */
	if(iv_matches(IV_VERSION(0, 1), IV_VERSION(0, 1)) != IV_TRUE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<0.1>, <0.1>) != IV_TRUE\n");

		rc = 1;
	}

	if(iv_matches(IV_VERSION(0, 1), IV_VERSION(0, 2)) != IV_FALSE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<0.1>, <0.2>) != IV_FALSE\n");

		rc = 1;
	}

	if(iv_matches(IV_VERSION(0, 2), IV_VERSION(0, 1)) != IV_FALSE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<0.2>, <0.1>) != IV_FALSE\n");

		rc = 1;
	}


	/*
	 * 0.x ~ 1.x matching
	 */
	if(iv_matches(IV_VERSION(0, 1), IV_VERSION(1, 1)) != IV_FALSE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<0.1>, <1.1>) != IV_FALSE\n");

		rc = 1;
	}


	/*
	 * Major version matching
	 */
	if(iv_matches(IV_VERSION(1, 0), IV_VERSION(1, 0)) != IV_TRUE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<1.0>, <1.0>) != IV_TRUE\n");

		rc = 1;
	}

	if(iv_matches(IV_VERSION(1, 0), IV_VERSION(2, 0)) != IV_FALSE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<1.0>, <2.0>) != IV_FALSE\n");

		rc = 1;
	}

	if(iv_matches(IV_VERSION(3, 0), IV_VERSION(2, 0)) != IV_FALSE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<3.0>, <2.0>) != IV_FALSE\n");

		rc = 1;
	}


	/*
	 * Minor version matching
	 */
	if(iv_matches(IV_VERSION(1, 1), IV_VERSION(1, 0)) != IV_TRUE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<1.1>, <1.0>) != IV_TRUE\n");

		rc = 1;
	}

	if(iv_matches(IV_VERSION(1, 2), IV_VERSION(1, 0)) != IV_TRUE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<1.2>, <1.0>) != IV_TRUE\n");

		rc = 1;
	}

	if(iv_matches(IV_VERSION(1, 2), IV_VERSION(1, 1)) != IV_TRUE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<1.2>, <1.1>) != IV_TRUE\n");

		rc = 1;
	}

	if(iv_matches(IV_VERSION(1, 0), IV_VERSION(1, 1)) != IV_FALSE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<1.0>, <1.1>) != IV_FALSE\n");

		rc = 1;
	}

	if(iv_matches(IV_VERSION(1, 0), IV_VERSION(1, 2)) != IV_FALSE)
	{
		fprintf(stderr,
			"Test FAILED - iv_matches(<1.0>, <1.2>) != IV_FALSE\n");

		rc = 1;
	}

	if(rc == 0)
		fprintf(stderr, "Tests PASSED - iv_matches()\n");

	return rc;
}
