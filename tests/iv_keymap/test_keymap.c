/*
 * @(#) tests/iv_keymap/test_keymap.c
 *
 * Unit test for iv_keymap.
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stddef.h>

#include <iv/base.h>
#include <iv/util.h>


static unsigned char bigkey[300] = "someBIGkey...........";

static int value1;

static int value2;

static int value3;

static int value4;


int
main(int argc, char **argv)
{
	iv_keymap_t *	keymap;
	uint32_t	ukey;
	int		rc;
	void **		valuep;
	void *		value;


	if((keymap = iv_keymap_create(0, NULL)) == NULL)
	{
		fprintf(stderr,
			"Test setup failed - iv_keymap_create() == NULL\n");

		return 2;
	}


	rc = 0;


	/*
	 * Set some values
	 */
	ukey = 123;

	if((valuep = iv_keymap_acquire_valueptr(
	 keymap, (unsigned char *) &ukey, sizeof(ukey), NULL)) == NULL)
	{
		fprintf(stderr,
			"Test allocation failed - iv_keymap_acquire_valueptr()\n");

		return 2;
	}

	*valuep = &value1;


	ukey = 998877;

	if((valuep = iv_keymap_acquire_valueptr(
	 keymap, (unsigned char *) &ukey, sizeof(ukey), NULL)) == NULL)
	{
		fprintf(stderr,
			"Test allocation failed - iv_keymap_acquire_valueptr()\n");

		return 2;
	}

	*valuep = &value2;


	ukey = 192837;

	if((valuep = iv_keymap_acquire_valueptr(
	 keymap, (unsigned char *) &ukey, sizeof(ukey), NULL)) == NULL)
	{
		fprintf(stderr,
			"Test allocation failed - iv_keymap_acquire_valueptr()\n");

		return 2;
	}

	*valuep = &value3;


	/*
	 * Large key
	 */
	if((valuep = iv_keymap_acquire_valueptr(
	 keymap, bigkey, sizeof(bigkey), NULL)) == NULL)
	{
		fprintf(stderr,
			"Test allocation failed - iv_keymap_acquire_valueptr()\n");

		return 2;
	}

	*valuep = &value4;


	/*
	 * Validate repeatable value pointers
	 */
	ukey = 123;

	if((valuep = iv_keymap_acquire_valueptr(
	 keymap, (unsigned char *) &ukey, sizeof(ukey), NULL)) == NULL)
	{
		fprintf(stderr,
			"Test allocation failed - iv_keymap_acquire_valueptr()\n");

		return 2;
	}

	if(*valuep != &value1)
	{
		fprintf(stderr,
			"Test FAILED - iv_keymap_acquire_valueptr() returned wrong value\n");

		rc = 1;
	}


	ukey = 998877;

	if((valuep = iv_keymap_get_valueptr(
	 keymap, (unsigned char *) &ukey, sizeof(ukey))) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_keymap_get_valueptr() returned wrong value\n");

		rc = 1;
	}
	else if(*valuep != &value2)
	{
		fprintf(stderr,
			"Test FAILED - iv_keymap_get_valueptr() returned wrong value\n");

		rc = 1;
	}


	ukey = 192837;

	if((value = iv_keymap_get(
	 keymap, (unsigned char *) &ukey, sizeof(ukey))) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_keymap_get() returned wrong value\n");

		rc = 1;
	}
	else if(value != &value3)
	{
		fprintf(stderr,
			"Test FAILED - iv_keymap_get() returned wrong value\n");

		rc = 1;
	}


	if((valuep = iv_keymap_acquire_valueptr(
	 keymap, bigkey, sizeof(bigkey), NULL)) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_keymap_acquire_valueptr() returned wrong value\n");

		rc = 1;
	}
	else if(*valuep != &value4)
	{
		fprintf(stderr,
			"Test FAILED - iv_keymap_acquire_valueptr() returned wrong value\n");

		rc = 1;
	}


	/*
	 * Non-matches
	 */
	ukey = 0;

	if(iv_keymap_get_valueptr(
	 keymap, (unsigned char *) &ukey, sizeof(ukey)) != NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_keymap_get_valueptr() returned unexpected value\n");

		rc = 1;
	}


	ukey = 333333;

	if(iv_keymap_get(
	 keymap, (unsigned char *) &ukey, sizeof(ukey)) != NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_keymap_get() returned unexpected value\n");

		rc = 1;
	}


	iv_keymap_destroy(keymap);


	if(rc == 0)
		fprintf(stderr, "Tests PASSED - iv_keymap\n");

	return rc;
}
