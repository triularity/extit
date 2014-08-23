/*
 * @(#) repository.c
 *
 * Example on using the interface repository.
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <extit/base.h>
#include <extit/ir.h>


#define	FOO_INTERFACE_NAME		"foo"
#define	BAR_INTERFACE_NAME		"bar"

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
	extit_ir_t *		ir;
	extit_iv_t		version;
	general_iface_t *	gi;


	ir = extit_ir_create(EXTIT_FLAG_LOG_DEBUG);

	if(ir == NULL)
	{
		fprintf(stderr, "Failed to create interface repository\n");
		return 1;
	}


	/*
	 * Register all interfaces
	 */
	if(extit_ir_setInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(0,1),
	 &foo_prototype_0_1, NULL) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@0.1\n", FOO_INTERFACE_NAME);

		return 2;
	}

	if(extit_ir_setInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(0,2),
	 &foo_prototype_0_2, NULL) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@0.2\n", FOO_INTERFACE_NAME);

		return 2;
	}

	if(extit_ir_setInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(0,4),
	 &foo_prototype_0_5, NULL) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@0.4\n", FOO_INTERFACE_NAME);

		return 2;
	}

	if(extit_ir_setInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(0,5),
	 &foo_prototype_0_5, NULL) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@0.5\n", FOO_INTERFACE_NAME);

		return 2;
	}

	if(extit_ir_setInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(1,4),
	 &foo_release_1_4, NULL) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@1.4\n", FOO_INTERFACE_NAME);

		return 2;
	}

	if(extit_ir_setInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(2,1),
	 &foo_release_2_1, NULL) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@2.1\n", FOO_INTERFACE_NAME);

		return 2;
	}

	if(extit_ir_setInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(2,2),
	 &foo_release_2_2, NULL) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@2.2\n", FOO_INTERFACE_NAME);

		return 2;
	}

	if(extit_ir_setInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(1,3),
	 &bar_release_1_3, NULL) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@1.3\n", BAR_INTERFACE_NAME);

		return 2;
	}

	if(extit_ir_setInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(2,2),
	 &bar_release_2_2, NULL) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@2.2\n", BAR_INTERFACE_NAME);

		return 2;
	}

	if(extit_ir_setInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(3,0),
	 &bar_release_3_0, NULL) != EXTIT_STATUS_OK)
	{
		fprintf(stderr,
			"Failed to register %s@3.0\n", BAR_INTERFACE_NAME);

		return 2;
	}


	/**
	 ** Query interfaces
	 **/

	if((version = extit_ir_queryInterface(
	 ir, FOO_INTERFACE_NAME, EXTIT_IV(0,1))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v0.1)\n",
			FOO_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@0.1\n",
			FOO_INTERFACE_NAME);
	}

	if((version = extit_ir_queryInterface(
	 ir, FOO_INTERFACE_NAME, EXTIT_IV(0,4))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v0.4)\n",
			FOO_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@0.4\n",
			FOO_INTERFACE_NAME);
	}

	if((version = extit_ir_queryInterface(
	 ir, FOO_INTERFACE_NAME, EXTIT_IV(1,0))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v1.0)\n",
			FOO_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@1.0\n",
			FOO_INTERFACE_NAME);
	}

	if((version = extit_ir_queryInterface(
	 ir, FOO_INTERFACE_NAME, EXTIT_IV(1,4))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v1.4)\n",
			FOO_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@1.4\n",
			FOO_INTERFACE_NAME);
	}

	if((version = extit_ir_queryInterface(
	 ir, FOO_INTERFACE_NAME, EXTIT_IV(1,5))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found unexpected interface %s@%u.%u (from v1.5)\n",
			FOO_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}

	if((version = extit_ir_queryInterface(
	 ir, FOO_INTERFACE_NAME, EXTIT_IV(2,0))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v2.0)\n",
			FOO_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@2.0\n",
			FOO_INTERFACE_NAME);
	}

	if((version = extit_ir_queryInterface(
	 ir, FOO_INTERFACE_NAME, EXTIT_IV(2,2))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v2.2)\n",
			FOO_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@2.2\n",
			FOO_INTERFACE_NAME);
	}

	if((version = extit_ir_queryInterface(
	 ir, FOO_INTERFACE_NAME, EXTIT_IV(3,0))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found unexpected interface %s@%u.%u (from v3.0)\n",
			FOO_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}

	if((version = extit_ir_queryInterface(
	 ir, BAR_INTERFACE_NAME, EXTIT_IV(1,0))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v1.0)\n",
			BAR_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@1.0\n",
			BAR_INTERFACE_NAME);
	}

	if((version = extit_ir_queryInterface(
	 ir, BAR_INTERFACE_NAME, EXTIT_IV(2,0))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v2.0)\n",
			BAR_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@2.0\n",
			BAR_INTERFACE_NAME);
	}

	if((version = extit_ir_queryInterface(
	 ir, BAR_INTERFACE_NAME, EXTIT_IV(3,0))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found interface %s@%u.%u (from v3.0)\n",
			BAR_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
	else
	{
		fprintf(stderr,
			"Couldn't query interface >= %s@3.0\n",
			BAR_INTERFACE_NAME);
	}

	if((version = extit_ir_queryInterface(
	 ir, BAR_INTERFACE_NAME, EXTIT_IV(4,0))) != EXTIT_IV_NONE)
	{
		fprintf(stderr,
			"Found unexpected interface %s@%u.%u (from v4.0)\n",
			BAR_INTERFACE_NAME,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}


	/**
	 ** Get various interfaces
	 **/

	/*
	 * foo@0.x
	 */
	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(0,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@0.1  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@0.1\n",
			FOO_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(0,2)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@0.2  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@0.2\n",
			FOO_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(0,3)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@0.3  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(0,4)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@0.4  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@0.4\n",
			FOO_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(0,5)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@0.5  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@0.5\n",
			FOO_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(0,8)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@0.8  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}


	/*
	 * foo@1.x
	 */
	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(1,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.0  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.0\n",
			FOO_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(1,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.1  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.1\n",
			FOO_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(1,4)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.4  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.4\n",
			FOO_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(1,5)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@1.5  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}


	/*
	 * foo@2.x
	 */
	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(2,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.0  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.0\n",
			FOO_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(2,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.1  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.1\n",
			FOO_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(2,2)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.2  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.2\n",
			FOO_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(2,3)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@2.3  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}


	/*
	 * foo@3.x
	 */
	if((gi = extit_ir_getInterface(ir, FOO_INTERFACE_NAME, EXTIT_IV(3,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@3.0  [%s]\n",
			FOO_INTERFACE_NAME,
			gi->name);
	}


	/*
	 * bar@1.x
	 */
	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(1,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.0  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.0\n",
			BAR_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(1,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.1  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.1\n",
			BAR_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(1,2)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.2  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.2\n",
			BAR_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(1,3)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@1.3  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@1.3\n",
			BAR_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(1,4)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@1.4  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}


	/*
	 * bar@2.x
	 */
	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(2,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.0  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.0\n",
			BAR_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(2,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.1  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.1\n",
			BAR_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(2,2)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@2.2  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@2.2\n",
			BAR_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(2,3)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@2.3  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}


	/*
	 * bar@3.x
	 */
	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(3,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found interface %s@3.0  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}
	else
	{
		fprintf(stderr,
			"Couldn't find interface %s@3.0\n",
			BAR_INTERFACE_NAME);
	}

	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(3,1)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@3.1  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}


	/*
	 * bar@4.x
	 */
	if((gi = extit_ir_getInterface(ir, BAR_INTERFACE_NAME, EXTIT_IV(4,0)))
	 != NULL)
	{
		fprintf(stderr,
			"Found unexpected interface %s@4.0  [%s]\n",
			BAR_INTERFACE_NAME,
			gi->name);
	}


	extit_ir_destroy(ir);
	exit(0);
}

