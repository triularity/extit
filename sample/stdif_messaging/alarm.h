/*
 * @(#) sample/stdif_messaging/alarm.h
 *
 * This file is in the Public Domain.
 */

#ifndef	__alarm_h
#define	__alarm_h

#include <time.h>

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	ALARM_TYPE_IID			"alarm"

#define	ALARM_TYPE_VERSION_1_0		IV_VERSION(1,0)

typedef struct _alarm_1_0
{
	unsigned int	hour;
	unsigned int	minute;
} alarm_1_0_t;

#define	ALARM_TYPE_VERSION_1_1		IV_VERSION(1,1)

typedef struct _alarm_1_1
{
	/* 1.0 */
	unsigned int	hour;
	unsigned int	minute;

	/* 1.1 */
	unsigned int	year;
	unsigned int	month;
	unsigned int	day;
} alarm_1_1_t;

#define	ALARM_TYPE_VERSION_2_0		IV_VERSION(2,0)

typedef struct _alarm_2_0
{
	time_t		timestamp;
	const char *	message;
} alarm_2_0_t;


#ifdef	__cplusplus
}
#endif

#endif	/* !__alarm_h */
