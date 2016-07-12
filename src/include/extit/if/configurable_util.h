/*
 * @(#) extit/if/configurable_util.h
 *
 * Configurable Interface.
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__if__configurable_util_h
#define	__extit__if__configurable_util_h

#include <extit/base.h>
#include <extit/if/configurable.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	extit_if_configurable_util_EXPORTS
#define	EXTIT_IF_CONFIGURABLE_UTIL_LIBAPI	EXTIT_EXPORT
#else
#define	EXTIT_IF_CONFIGURABLE_UTIL_LIBAPI	EXTIT_IMPORT
#endif


/*
 * Public API (v1.0)
 */
EXTIT_IF_CONFIGURABLE_UTIL_LIBAPI
const extit_if_configurable_enum32_t *
			EXTIT_DECL
			extit_if_configurable_enum32_find_by_id(
				const extit_if_configurable_enum32_t *choices,
				uint32_t count,
				const char *id);

EXTIT_IF_CONFIGURABLE_UTIL_LIBAPI
const extit_if_configurable_enum32_t *
			EXTIT_DECL
			extit_if_configurable_enum32_find_by_value(
				const extit_if_configurable_enum32_t *choices,
				uint32_t count,
				uint32_t value);

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__if__configurable_util_h */
