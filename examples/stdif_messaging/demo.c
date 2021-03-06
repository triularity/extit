/*
 * @(#) stdif_messaging/demo.c
 *
 * This file is in the Public Domain.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef	_WIN32
#include <windows.h>

#define	sleep(x)	Sleep((x) * 1000)
#else
#include <unistd.h>
#endif

#include <iv/base.h>
#include <stdif/messaging.h>
#include <stdif/messaging_stdimpl.h>

#include "alarm.h"


static
void
alarm_changed(const char *mid, void *data, void *client_data)
{
	alarm_1_0_t *	alarm_data;


	alarm_data = (alarm_1_0_t *) data;

	printf("New Alarm Time (%s): %02u:%02u\n",
		(char *) client_data,
		alarm_data->hour, alarm_data->minute);
}


static
void
alarm_triggered(const char *mid, void *data, void *client_data)
{
	alarm_1_0_t *	alarm_data;


	alarm_data = (alarm_1_0_t *) data;

	printf("Alarm! %02u:%02u\n", alarm_data->hour, alarm_data->minute);
}


static
void
new_alarm_triggered(const char *mid, void *data, void *client_data)
{
	alarm_2_0_t *	alarm_data;
	struct tm *	timeinfo;


	alarm_data = (alarm_2_0_t *) data;

	timeinfo = localtime(&alarm_data->timestamp);

	printf("Alarm! %04d-%02d:%02d %02d:%02d:%02d\n",
		timeinfo->tm_year + 1900,
		timeinfo->tm_mon + 1,
		timeinfo->tm_mday,
		timeinfo->tm_hour,
		timeinfo->tm_min,
		timeinfo->tm_sec);

	if(alarm_data->message != NULL)
		printf("       %s\n", alarm_data->message);
}


static
char alarm_name[] = "Alarm #1";


int
main(int argc, char **argv)
{
	stdif_messaging_t *	messaging;
	stdif_messaging_bound_t *	alarm_2_0_bound;
	alarm_1_0_t		alarm_1_0;
	alarm_1_1_t		alarm_1_1;
	alarm_2_0_t		alarm_2_0;
	int			i;


	/* XXX - Check for NULL in real thing */
	messaging = stdif_messaging_stdimpl_create(STDIF_MESSAGING_ABI_1_0);

	/* XXX - Check status in real thing */
	stdif_messaging_add_listener(
		messaging,
		"clock_alarm_set",
		ALARM_TYPE_IID,
		ALARM_TYPE_VERSION_1_0,
		alarm_changed,
		alarm_name);

	/* XXX - Check status in real thing */
	stdif_messaging_add_listener(
		messaging,
		"alarm:activate",
		ALARM_TYPE_IID,
		ALARM_TYPE_VERSION_1_0,
		alarm_triggered,
		NULL);

	/* XXX - Check status in real thing */
	stdif_messaging_add_listener(
		messaging,
		"alarm:activate",
		ALARM_TYPE_IID,
		ALARM_TYPE_VERSION_2_0,
		new_alarm_triggered,
		NULL);

	alarm_2_0_bound = stdif_messaging_bind(
		messaging,
		"alarm:activate",
		ALARM_TYPE_IID,
		ALARM_TYPE_VERSION_2_0);

	if(alarm_2_0_bound == STDIF_MESSAGING_BOUND_NONE)
	{
		fprintf(stderr, "Message bind failed\n");
		return 1;
	}


	alarm_1_0.hour = 6;
	alarm_1_0.minute = 35;

	/* XXX - Check status in real thing */
	stdif_messaging_send(
		messaging,
		"clock_alarm_set",
		ALARM_TYPE_IID,
		ALARM_TYPE_VERSION_1_0,
		&alarm_1_0);

	/* ... */

	/* XXX - Check status in real thing */
	stdif_messaging_send(
		messaging,
		"alarm:activate",
		ALARM_TYPE_IID,
		ALARM_TYPE_VERSION_1_0,
		&alarm_1_0);


	/* Notify about impending y2k doom! ;) */
	alarm_1_1.year = 1999;
	alarm_1_1.month = 12;
	alarm_1_1.day = 31;
	alarm_1_1.hour = 23;
	alarm_1_1.minute = 59;

	/* XXX - Check status in real thing */
	stdif_messaging_send(
		messaging,
		"alarm:activate",
		ALARM_TYPE_IID,
		ALARM_TYPE_VERSION_1_1,
		&alarm_1_1);


	alarm_2_0.timestamp = time(NULL);
	alarm_2_0.message = "Pre-flood alert";

	/* XXX - Check status in real thing */
	stdif_messaging_bound_send(
		messaging,
		alarm_2_0_bound,
		&alarm_2_0);

	alarm_2_0.message = NULL;

	for(i = 0; i < 10; i++)
	{
		sleep(1);

		alarm_2_0.timestamp = time(NULL);

		/* XXX - Check status in real thing */
		stdif_messaging_bound_send(
			messaging,
			alarm_2_0_bound,
			&alarm_2_0);
	}

	stdif_messaging_stdimpl_destroy(messaging);

	return 0;
}
