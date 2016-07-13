/*
 * @(#) test_refcount.c
 *
 * Unit test for extit_refcount_*.
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <extit/base.h>
#include <extit/util.h>


int
main(int argc, char **argv)
{
	int     		rc;
	extit_refcount_t	refcount;


	rc = 0;


	/*
	 * EXTIT_REFCOUNT_NONE == 0
	 */
	if(EXTIT_REFCOUNT_NONE != 0)
	{
		fprintf(stderr,
			"Test FAILED - EXTIT_REFCOUNT_NONE != 0\n");

		rc = 1;
	}


	/*
	 * add succeeds
	 * count == 1
	 * release succeeds (!busy)
	 */
	refcount = EXTIT_REFCOUNT_NONE;

	if(extit_refcount_add(&refcount) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Test FAILED - extit_refcount_add()\n");

		rc = 1;
	}

	if(refcount != 1)
	{
		fprintf(stderr,
			"Test FAILED - extit_refcount_add() - [0 -> 1]\n");

		rc = 1;
	}

	if(extit_refcount_release(&refcount) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Test FAILED - extit_refcount_release() [1 -> 0]\n");

		rc = 1;
	}


	/*
	 * release fails when count == 0 (invalid)
	 */
	refcount = EXTIT_REFCOUNT_NONE;

	if(extit_refcount_release(&refcount) != EXTIT_STATUS_INVALID)
	{
		fprintf(stderr,
			"Test FAILED - extit_refcount_release() [0 -> -1]\n");

		rc = 1;
	}


	/*
	 * double add succeeds
	 * single release succeeds (busy)
	 */
	refcount = EXTIT_REFCOUNT_NONE;

	if(extit_refcount_add(&refcount) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Test FAILED - extit_refcount_add()\n");

		rc = 1;
	}
	else if(extit_refcount_add(&refcount) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Test FAILED - extit_refcount_add()\n");

		rc = 1;
	}
	else if(extit_refcount_release(&refcount) != EXTIT_STATUS_BUSY)
	{
		fprintf(stderr,
			"Test FAILED - extit_refcount_release() [2 -> 1]\n");

		rc = 1;
	}


	/*
	 * add fails when count == EXTIT_REFCOUNT_MAX
	 */
	refcount = EXTIT_REFCOUNT_MAX;

	if(extit_refcount_add(&refcount) != EXTIT_STATUS_INVALID)
	{
		fprintf(stderr,
			"Test FAILED - extit_refcount_add() [max -> max+1]\n");

		rc = 1;
	}


	if(rc == 0)
		fprintf(stderr, "Tests PASSED - extit_refcount\n");

	return rc;
}

