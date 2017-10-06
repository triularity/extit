/*
 * @(#) extit/container/Container_1_0.cc
 *
 * C++ wrappers for container library.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string>

#include <iv/base.h>
#include <extit/base.h>
#include <extit/container_cxx.h>
#include <extit/container_impl.h>


namespace ExtIt
{

//
// Container (v1.0 interface)
//

extit_func_t
Container_1_0::getFunction
(
	const char *name
)
{
	const extit_container_1_0_t *	container_1_0;


	container_1_0 = (const extit_container_1_0_t *) container;

	return container_1_0->ops->v0.op_get_function(container_1_0, name);
}


extit_func_t
Container_1_0::getFunction
(
	const std::string & name
)
{
	return getFunction(name.c_str());
}

void *
Container_1_0::getInterface
(
	const char *iid,
	iv_version_t version
)
{
	const extit_container_1_0_t *	container_1_0;


	container_1_0 = (const extit_container_1_0_t *) container;

	return container_1_0->ops->v0.op_get_interface(
		container_1_0, iid, version);
}


void *
Container_1_0::getInterface
(
	const std::string & iid,
	iv_version_t version
)
{
	return getInterface(iid.c_str(), version);
}


void *
Container_1_0::getSymbol
(
	const char *name
)
{
	const extit_container_1_0_t *	container_1_0;


	container_1_0 = (const extit_container_1_0_t *) container;

	return container_1_0->ops->v0.op_get_symbol(container_1_0, name);
}


void *
Container_1_0::getSymbol
(
	const std::string & name
)
{
	return getSymbol(name.c_str());
}


void
Container_1_0::log
(
	const char *message
)
{
	const extit_container_1_0_t *	container_1_0;


	container_1_0 = (const extit_container_1_0_t *) container;

	return container_1_0->ops->v0.op_log(container_1_0, message);
}


void
Container_1_0::log
(
	const std::string & message
)
{
	log(message.c_str());
}


iv_version_t
Container_1_0::queryInterface
(
	const char *iid,
	iv_version_t base_version
)
{
	const extit_container_1_0_t *	container_1_0;


	container_1_0 = (const extit_container_1_0_t *) container;

	return container_1_0->ops->v0.op_query_interface(
		container_1_0, iid, base_version);
}


iv_version_t
Container_1_0::queryInterface
(
	const std::string & iid,
	iv_version_t base_version
)
{
	return queryInterface(iid.c_str(), base_version);
}

// namespace ExtIt
}
