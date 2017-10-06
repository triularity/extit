/*
 * @(#) extit/container_cxx.h
 *
 * ExtIt container C++ wrapper.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__container_cxx_h
#define	__extit__container_cxx_h

#ifndef	__cplusplus
#error	C++ only
#endif

#include <string>

#include <extit/container.h>

#ifdef	extit_container_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif

namespace ExtIt
{

/*
 * C++ Container (base)
 */
class LIBAPI Container
{
	protected:
		const extit_container_t *	container;

	public:
		const extit_container_t *
				get_struct() const;

		iv_version_t	getVersion() const;
};


/*
 * C++ Container (base concrete)
 */
class ContainerImpl : public Container
{
	public:
		ContainerImpl(const extit_container_t *container);
};


/*
 * C++ Container (v1.0)
 */
class Container_1_0 : public Container
{
	public:
		extit_func_t	getFunction(
					const char *name);

		extit_func_t	getFunction(
					const std::string & name);

		void *		getInterface(
					const char *iid,
					iv_version_t version);

		void *		getInterface(
					const std::string & iid,
					iv_version_t version);

		void *		getSymbol(
					const char *name);

		void *		getSymbol(
					const std::string & name);

		void		log(
					const char *message);

		void		log(
					const std::string & message);

		iv_version_t	queryInterface(
					const char *iid,
					iv_version_t base_version);

		iv_version_t	queryInterface(
					const std::string & iid,
					iv_version_t base_version);
};


/*
 * C++ Container (v1.0 concrete)
 */
class ContainerImpl_1_0 : public Container_1_0
{
	public:
		ContainerImpl_1_0(const extit_container_t *container);
		ContainerImpl_1_0(const extit_container_1_0_t *container);
};

// namespace "ExtIt"
}

#undef	LIBAPI

#endif	/* !__extit__container_cxx_h */
