/*
 * @(#) stdif_configurable/scan_service.h
 *
 * This file is in the Public Domain.
 */

#ifndef	__scan_service_h
#define	__scan_service_h

#include <stdif/configurable.h>

typedef enum scan_mode
{
	SCAN_MODE_BW	= 0,
	SCAN_MODE_GRAY	= 1,
	SCAN_MODE_COLOR	= 2
} scan_mode_t;


typedef struct _scan_service		scan_service_t;


scan_service_t *			scan_service_create(void);

stdif_configurable_t *			scan_service_get_configurable(
						scan_service_t *service);

#endif	/* !__scan_service_h */
