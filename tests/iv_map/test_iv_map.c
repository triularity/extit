/*
 * @(#) tests/iv_map/test_iv_map.c
 *
 * Unit test for iv_map.
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include <iv/base.h>
#include <iv/map.h>


static int value1 = 22901;

static int value1_alt = 7262013;

static int value2 = 1987331;

static int value3 = 49728;

static int value_blank = 112233;


int
main(int argc, char **argv)
{
	iv_map_t *	map;
	int		rc;
	void **		valuep;
	void *		value;
	const char *	nameid;
	const char *	iid;


	if((map = iv_map_create(0, NULL)) == NULL)
	{
		fprintf(stderr,
			"Test setup failed - iv_map_create() == NULL\n");

		return 1;
	}


	rc = 0;


	/*
	 * Add entries
	 */
	if((valuep = iv_map_acquire_valueptr(
	 map, "key1", "interface-a", NULL, NULL)) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr()\n");

		rc = 2;
	}
	else
	{
		*valuep = &value1;
	}


	if((valuep = iv_map_acquire_valueptr(
	 map, "key2", "interface-a", NULL, NULL)) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr()\n");

		rc = 2;
	}
	else
	{
		*valuep = &value2;
	}


	if((valuep = iv_map_acquire_valueptr(
	 map, "key_number_3", "interface-a", NULL, NULL)) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr()\n");

		rc = 2;
	}
	else
	{
		*valuep = &value3;
	}


	if((valuep = iv_map_acquire_valueptr(
	 map, "", "interface-a", NULL, NULL)) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr()\n");

		rc = 2;
	}
	else
	{
		*valuep = &value_blank;
	}


	/*
	 * Alternate interface
	 */
	if((valuep = iv_map_acquire_valueptr(
	 map, "key1", "interface-b", NULL, NULL)) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr()\n");

		rc = 2;
	}
	else
	{
		*valuep = &value1_alt;
	}


	/*
	 * Validate repeatable value pointers
	 */
	if((valuep = iv_map_acquire_valueptr(
	 map, "key1", "interface-a", NULL, NULL)) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr()\n");

		rc = 2;
	}
	else if(*valuep != &value1)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr() returned wrong value\n");

		rc = 2;
	}


	if((valuep = iv_map_acquire_valueptr(
	 map, "key2", "interface-a", NULL, NULL)) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr()\n");

		rc = 2;
	}
	else if(*valuep != &value2)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr() returned wrong value\n");

		rc = 2;
	}


	/*
	 * Validate assignments
	 */
	if((value = iv_map_get(map, "key1", "interface-a")) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_get() [key1, interface-a]\n");

		rc = 2;
	}
	else if(value != &value1)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_get() returned wrong value\n");

		rc = 2;
	}


	if((value = iv_map_get(map, "key1", "interface-b")) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_get() [key1, interface-b]\n");

		rc = 2;
	}
	else if(value != &value1_alt)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_get() returned wrong value\n");

		rc = 2;
	}


	if((value = iv_map_get(map, "key_number_3", "interface-a")) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_get() [key_number_3, interface-a]\n");

		rc = 2;
	}
	else if(value != &value3)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_get() returned wrong value\n");

		rc = 2;
	}


	/*
	 * Non-matches
	 */
	if(iv_map_get_valueptr(map, "key1", "interface-z") != NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_get_valueptr() returned unexpected value\n");

		rc = 2;
	}


	if(iv_map_get_valueptr(map, "keyX", "interface-a") != NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_get_valueptr() returned unexpected value\n");

		rc = 2;
	}


	/*
	 * Internal pointers
	 */
	if((valuep = iv_map_acquire_valueptr(
	 map, "somekey", "that-interface", &nameid, &iid)) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr()\n");

		rc = 2;
	}
	else if(nameid == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr() didn't set internal name id\n");

		rc = 2;
	}
	else if(iid == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr() didn't set internal interface id\n");

		rc = 2;
	}
	else if(strcmp(nameid, "somekey") != 0)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr() didn't return expected internal name id\n");

		rc = 2;
	}
	else if(strcmp(iid, "that-interface") != 0)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_acquire_valueptr() didn't return expected internal interface id\n");

		rc = 2;
	}


	if((nameid = iv_map_intern_nameid(map, "key2", "interface-a")) == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_intern_nameid()\n");

		rc = 2;
	}
	else if(strcmp(nameid, "key2") != 0)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_intern_nameid() didn't return expected value\n");

		rc = 2;
	}


	if((iid = iv_map_intern_interfaceid(map, "key2", "interface-a"))
	 == NULL)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_intern_interfaceid()\n");

		rc = 2;
	}
	else if(strcmp(iid, "interface-a") != 0)
	{
		fprintf(stderr,
			"Test FAILED - iv_map_intern_interfaceid() didn't return expected value\n");

		rc = 2;
	}


	iv_map_destroy(map);


	if(rc == 0)
		fprintf(stderr, "Tests PASSED - iv_map\n");

	return rc;
}
