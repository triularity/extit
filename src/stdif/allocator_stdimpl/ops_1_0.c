/*
 * @(#) stdif/allocator_stdimpl/ops_1_0.c
 *
 * Allocator Interface - Standard implementation 1.0 instance.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <extit/base.h>
#include <stdif/allocator.h>
#include <stdif/allocator_impl.h>
#include <stdif/allocator_stdimpl.h>


static
stdif_allocator_ops_1_0_t	allocator_ops_1_0 =
{
	/* v0 */
	{
		stdif_allocator_stdimpl_alloc__1_0,	/* op_alloc */
		stdif_allocator_stdimpl_free__1_0,	/* op_free */
		stdif_allocator_stdimpl_realloc__1_0,	/* op_realloc */
		stdif_allocator_stdimpl_zalloc__1_0,	/* op_zalloc */
		stdif_allocator_stdimpl_dup__1_0	/* op_dup */
	}
};


/**
 * A static instance of an allocator 1.0 interface that uses standard
 * C memory management.
 */
stdif_allocator_1_0_t	stdif_allocator_stdimpl_1_0 =
{
	STDIF_ALLOCATOR_ABI_1_0,	/* version */
	&allocator_ops_1_0		/* ops_1_0 */
};

