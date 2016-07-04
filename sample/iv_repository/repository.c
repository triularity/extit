/*
 * @(#) repository.c
 *
 * Example on using the interface repository.
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <iv/base.h>
#include <iv/repository.h>


#define	FOO_INTERFACE_ID		"foo"
#define	BAR_INTERFACE_ID		"bar"

typedef struct _general_iface
{
	const char *	name;

	/* Some useful stuff goes here.. */
} general_iface_t;


static general_iface_t foo_prototype_0_1 =
{
	"Foo Prototype v0.1"
};

static general_iface_t foo_prototype_0_2 =
{
	"Foo Prototype v0.2"
};

static general_iface_t foo_prototype_0_5 =
{
	"Foo Prototype v0.4/v0.5"
};

static general_iface_t foo_release_1_4 =
{
	"Foo Release v1.4"
};

static general_iface_t foo_release_2_1 =
{
	"Foo Release v2.1"
};

static general_iface_t foo_release_2_2 =
{
	"Foo Release v2.2"
};

static general_iface_t bar_release_1_3 =
{
	"Bar Release v1.3"
};

static general_iface_t bar_release_2_2 =
{
	"Bar Release v2.2"
};

static general_iface_t bar_release_3_0 =
{
	"Bar Release v3.0"
};


int
main(int argc, char **argv)
{
	iv_repository_t *	ir;
	iv_version_t		version;
	general_iface_t *	gi;


	iv_repository_set_default_flags(IV_REPOSITORY_FLAG_LOG_DEBUG);

	ir = iv_repository_create();

	if(ir == NULL)
	{
		fprintf(stderr, "Failed to create interface repository\n");
		return 1;
	}


	/*
	 * Register all interfaces
	 */
	if(iv_repository_set(ir, FOO_INTERFACE_ID, IV_VERSION(0,1),
	 &foo_prototype_0_1, NULL) != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@0.1\n", FOO_INTERFACE_ID);

		return 2;
	}

	if(iv_repository_set(ir, FOO_INTERFACE_ID, IV_VERSION(0,2),
	 &foo_prototype_0_2, NULL) != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@0.2\n", FOO_INTERFACE_ID);

		return 2;
	}

	if(iv_repository_set(ir, FOO_INTERFACE_ID, IV_VERSION(0,4),
	 &foo_prototype_0_5, NULL) != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@0.4\n", FOO_INTERFACE_ID);

		return 2;
	}

	if(iv_repository_set(ir, FOO_INTERFACE_ID, IV_VERSION(0,5),
	 &foo_prototype_0_5, NULL) != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@0.5\n", FOO_INTERFACE_ID);

		return 2;
	}

	if(iv_repository_set(ir, FOO_INTERFACE_ID, IV_VERSION(1,4),
	 &foo_release_1_4, NULL) != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@1.4\n", FOO_INTERFACE_ID);

		return 2;
	}

	if(iv_repository_set(ir, FOO_INTERFACE_ID, IV_VERSION(2,1),
	 &foo_release_2_1, NULL) != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@2.1\n", FOO_INTERFACE_ID);

		return 2;
	}

	if(iv_repository_set(ir, FOO_INTERFACE_ID, IV_VERSION(2,2),
	 &foo_release_2_2, NULL) != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@2.2\n", FOO_INTERFACE_ID);

		return 2;
	}

	if(iv_repository_set(ir, BAR_INTERFACE_ID, IV_VERSION(1,3),
	 &bar_release_1_3, NULL) != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@1.3\n", BAR_INTERFACE_ID);

		return 2;
	}

	if(iv_repository_set(ir, BAR_INTERFACE_ID, IV_VERSION(2,2),
	 &bar_release_2_2, NULL) != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@2.2\n", BAR_INTERFACE_ID);

		return 2;
	}

	if(iv_repository_set(ir, BAR_INTERFACE_ID, IV_VERSION(3,0),
	 &bar_release_3_0, NULL) != IV_REPOSITORY_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@3.0\n", BAR_INTERFACE_ID);

		return 2;
	}


	/**
	 ** Query interfaces
	 **/

	if((version = iv_repository_query(
	 ir, FOO_INTERFACE_ID, IV_VERSION(0,1))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v0.1)\n",
			FOO_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@0.1\n",
			FOO_INTERFACE_ID);
	}

	if((version = iv_repository_query(
	 ir, FOO_INTERFACE_ID, IV_VERSION(0,4))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v0.4)\n",
			FOO_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@0.4\n",
			FOO_INTERFACE_ID);
	}

	if((version = iv_repository_query(
	 ir, FOO_INTERFACE_ID, IV_VERSION(1,0))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v1.0)\n",
			FOO_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@1.0\n",
			FOO_INTERFACE_ID);
	}

	if((version = iv_repository_query(
	 ir, FOO_INTERFACE_ID, IV_VERSION(1,4))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v1.4)\n",
			FOO_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@1.4\n",
			FOO_INTERFACE_ID);
	}

	if((version = iv_repository_query(
	 ir, FOO_INTERFACE_ID, IV_VERSION(1,5))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found unexpected interface %s@%u.%u (from v1.5)\n",
			FOO_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}

	if((version = iv_repository_query(
	 ir, FOO_INTERFACE_ID, IV_VERSION(2,0))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v2.0)\n",
			FOO_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@2.0\n",
			FOO_INTERFACE_ID);
	}

	if((version = iv_repository_query(
	 ir, FOO_INTERFACE_ID, IV_VERSION(2,2))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v2.2)\n",
			FOO_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@2.2\n",
			FOO_INTERFACE_ID);
	}

	if((version = iv_repository_query(
	 ir, FOO_INTERFACE_ID, IV_VERSION(3,0))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found unexpected interface %s@%u.%u (from v3.0)\n",
			FOO_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}

	if((version = iv_repository_query(
	 ir, BAR_INTERFACE_ID, IV_VERSION(1,0))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v1.0)\n",
			BAR_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@1.0\n",
			BAR_INTERFACE_ID);
	}

	if((version = iv_repository_query(
	 ir, BAR_INTERFACE_ID, IV_VERSION(2,0))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v2.0)\n",
			BAR_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@2.0\n",
			BAR_INTERFACE_ID);
	}

	if((version = iv_repository_query(
	 ir, BAR_INTERFACE_ID, IV_VERSION(3,0))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v3.0)\n",
			BAR_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@3.0\n",
			BAR_INTERFACE_ID);
	}

	if((version = iv_repository_query(
	 ir, BAR_INTERFACE_ID, IV_VERSION(4,0))) != IV_VERSION_NONE)
	{
		fprintf(stderr,
			"Found unexpected interface %s@%u.%u (from v4.0)\n",
			BAR_INTERFACE_ID,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}


	/**
	 ** Get various interfaces
	 **/

	/*
	 * foo@0.x
	 */
	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(0,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@0.1  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@0.1\n",
			FOO_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(0,2)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@0.2  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@0.2\n",
			FOO_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(0,3)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@0.3  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(0,4)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@0.4  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@0.4\n",
			FOO_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(0,5)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@0.5  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@0.5\n",
			FOO_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(0,8)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@0.8  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}


	/*
	 * foo@1.x
	 */
	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(1,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.0  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.0\n",
			FOO_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(1,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.1  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.1\n",
			FOO_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(1,4)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.4  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.4\n",
			FOO_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(1,5)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@1.5  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}


	/*
	 * foo@2.x
	 */
	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(2,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.0  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.0\n",
			FOO_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(2,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.1  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.1\n",
			FOO_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(2,2)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.2  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.2\n",
			FOO_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(2,3)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@2.3  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}


	/*
	 * foo@3.x
	 */
	if((gi = iv_repository_get(ir, FOO_INTERFACE_ID, IV_VERSION(3,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@3.0  [%s]\n",
			FOO_INTERFACE_ID,
			gi->name);
	}


	/*
	 * bar@1.x
	 */
	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(1,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.0  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.0\n",
			BAR_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(1,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.1  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.1\n",
			BAR_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(1,2)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.2  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.2\n",
			BAR_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(1,3)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.3  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.3\n",
			BAR_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(1,4)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@1.4  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}


	/*
	 * bar@2.x
	 */
	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(2,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.0  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.0\n",
			BAR_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(2,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.1  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.1\n",
			BAR_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(2,2)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.2  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.2\n",
			BAR_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(2,3)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@2.3  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}


	/*
	 * bar@3.x
	 */
	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(3,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@3.0  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@3.0\n",
			BAR_INTERFACE_ID);
	}

	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(3,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@3.1  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}


	/*
	 * bar@4.x
	 */
	if((gi = iv_repository_get(ir, BAR_INTERFACE_ID, IV_VERSION(4,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@4.0  [%s]\n",
			BAR_INTERFACE_ID,
			gi->name);
	}


	iv_repository_destroy(ir);
	return 0;
}

