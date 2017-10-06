/*
 * @(#) extit/container/ContainerImpl.cc
 *
 * C++ wrappers for container library.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdexcept>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container_cxx.h>
#include <extit/container_impl.h>


namespace ExtIt
{

//
// Container (concrete)
//

ContainerImpl::ContainerImpl
(
	const extit_container_t *container
)
{
	if(container == NULL)
		throw new std::invalid_argument("Container is NULL");

	this->container = container;
}

// namespace ExtIt
}
