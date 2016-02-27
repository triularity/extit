/*
 * @(#) extit/src/iv/util.c
 *
 * Interface Versioning utilities.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/util.h>


IV_EXPORT
iv_bool_t
IV_DECL
iv_matches
(
	iv_version_t version,
	iv_version_t req_version
)
{
	unsigned int	version_major;


	version_major = IV_VERSION_MAJOR(version);

	if(version_major == 0)
	{
		return (version == req_version) ? IV_TRUE : IV_FALSE;
	}
	else if(version_major == IV_VERSION_MAJOR(req_version))
	{
		return (version >= req_version) ? IV_TRUE : IV_FALSE;
	}
	else
	{
		return IV_FALSE;
	}
}

