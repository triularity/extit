/*
 * @(#) extit/container/ContainerImpl_1_0.cc
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

ContainerImpl_1_0::ContainerImpl_1_0
(
	const extit_container_t *container
)
{
	if(container == NULL)
		throw new std::invalid_argument("Container is NULL");

	if(IV_VERSION_MAJOR(container->version) != 1)
		throw new std::logic_error("Container does not support 1.0");

	this->container = container;
}


ContainerImpl_1_0::ContainerImpl_1_0
(
	const extit_container_1_0_t *container
)
{
	if(container == NULL)
		throw new std::invalid_argument("Container is NULL");

#ifdef  EXTIT_PARANOID
	if(IV_VERSION_MAJOR(container->version) != 1)
		throw new std::logic_error("Container does not support 1.0");
#endif

	this->container = (const extit_container_t *) container;
}

// namespace ExtIt
}
