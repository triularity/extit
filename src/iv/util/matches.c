/*
 * @(#) extit/src/iv/util/matches.c
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <iv/base.h>
#include <iv/util.h>


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
		return (version == req_version);
	else if(version_major == IV_VERSION_MAJOR(req_version))
		return (version >= req_version);
	else
		return IV_FALSE;
}
