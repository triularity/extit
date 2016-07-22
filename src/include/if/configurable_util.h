/*
 * @(#) if/configurable_util.h
 *
 * Configurable Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__if__configurable_util_h
#define	__if__configurable_util_h

#include <extit/base.h>
#include <if/configurable.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	if_configurable_util_EXPORTS
#define	LIBAPI		EXTIT_EXPORT
#else
#define	LIBAPI		EXTIT_IMPORT
#endif


/*
 * Public API (v1.0)
 */
LIBAPI
const if_configurable_enum32_t *
			EXTIT_DECL
			if_configurable_enum32_find_by_id(
				const if_configurable_enum32_t *choices,
				uint32_t count,
				const char *id);

LIBAPI
const if_configurable_enum32_t *
			EXTIT_DECL
			if_configurable_enum32_find_by_value(
				const if_configurable_enum32_t *choices,
				uint32_t count,
				uint32_t value);

#undef	LIBAPI

#ifdef	__cplusplus
}
#endif

#endif	/* !__if__configurable_util_h */
