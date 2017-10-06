/*
 * @(#) extit/container/Container.cc
 *
 * C++ wrappers for container library.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <extit/container_cxx.h>
#include <extit/container_impl.h>


namespace ExtIt
{

//
// Container (interface)
//

const extit_container_t *
Container::get_struct() const
{
	return container;
}


iv_version_t
Container::getVersion() const
{
	return container->version;
}

// namespace ExtIt
}
