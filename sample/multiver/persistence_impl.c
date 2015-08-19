/*
 * @(#) persistence_impl.c
 *
 * A simple persistence manager interface implementation using the filesystem.
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifdef	_WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#include "persistence.h"

#define	MAX_NAME_LEN	64


struct _persistence_ctx
{
	char *		dir;
};


static
int
isValidName(const char *name)
{
	if(name[0] == '\0')
		return 0;

	if(name[0] == '.')
		return 0;

	if(strchr(name, '/') != NULL)
		return 0;

	if(strchr(name, '\\') != NULL)
		return 0;

	if(strlen(name) > MAX_NAME_LEN)
		return 0;

	return 1;
}


static
persistence_ctx_t
EXTIT_DECL
open_ctx(const char *id)
{
	persistence_ctx_t	ctx;


	if(!isValidName(id))
		return NULL;

	if((ctx = calloc(1, sizeof(struct _persistence_ctx))) == NULL)
		return NULL;

	if((ctx->dir = malloc(strlen(id) + 7 + 1)) == NULL)
	{
		free(ctx);
		return NULL;
	}

	strcpy(ctx->dir, "pstore-");
	strcat(ctx->dir, id);

	/*
	 * XXX - Just assume the mkdir() works, or that it fails because
	 * the directory already exists. It will fail later if the directory
	 * wasn't created here.
	 *
	 * Real code would do all the proper checking and return an error if
	 * needed.
	 */
#ifdef	_WIN32
	_mkdir(ctx->dir);
#else
	mkdir(ctx->dir, S_IRUSR|S_IWUSR);
#endif

	return ctx;
}


static
void
EXTIT_DECL
close_ctx(persistence_ctx_t ctx)
{
	free(ctx->dir);
	free(ctx);
}


static
persistence_status_t
EXTIT_DECL
set_string(persistence_ctx_t ctx, const char *name, const char *value)
{
	char	path[MAX_NAME_LEN+MAX_NAME_LEN+2];
	FILE *	fp;
	size_t	len;


	if(!isValidName(name))
		return PERSISTENCE_STATUS_INVALID;

	sprintf(path, "%s/%s", ctx->dir, name);

	if((fp = fopen(path, "w")) == NULL)
		return PERSISTENCE_STATUS_NOTFOUND;

	len = strlen(value) + 1;

	if(fwrite(value, 1, len, fp) != len)
	{
		fclose(fp);
		return PERSISTENCE_STATUS_IOERROR;
	}

	fclose(fp);
	return PERSISTENCE_STATUS_SUCCESS;
}


static
persistence_status_t
EXTIT_DECL
get_string(persistence_ctx_t ctx, const char *name, char *buf, unsigned int maxlen)
{
	char	path[MAX_NAME_LEN+MAX_NAME_LEN+2];
	FILE *	fp;
	size_t	len;


	if(!isValidName(name))
		return PERSISTENCE_STATUS_INVALID;

	sprintf(path, "%s/%s", ctx->dir, name);

	if((fp = fopen(path, "r")) == NULL)
		return PERSISTENCE_STATUS_NOTFOUND;

	len = fread(buf, 1, maxlen, fp);

	if(len == maxlen)
	{
		fclose(fp);
		return PERSISTENCE_STATUS_TOOLONG;
	}

	if(ferror(fp) != 0)
	{
		fclose(fp);
		return PERSISTENCE_STATUS_IOERROR;
	}

	buf[len] = '\0';

	fclose(fp);
	return PERSISTENCE_STATUS_SUCCESS;
}


#if	PERSISTENCE_INTERFACE_TARGET >= PERSISTENCE_INTERFACE_VERSION_1_1
static
persistence_status_t
EXTIT_DECL
set_int(persistence_ctx_t ctx, const char *name, int value)
{
	char	str[20];


	sprintf(str, "%d", value);

	return set_string(ctx, name, str);
}


static
persistence_status_t
EXTIT_DECL
set_double(persistence_ctx_t ctx, const char *name, double value)
{
	char	str[20];


	sprintf(str, "%f", value);

	return set_string(ctx, name, str);
}


static
int
EXTIT_DECL
get_int(persistence_ctx_t ctx, const char *name, int defValue)
{
	char	str[20];
	long	value;


	if(get_string(ctx, name, str, sizeof(str))
	 != PERSISTENCE_STATUS_SUCCESS)
	{
		return defValue;
	}

	if(str[0] == '\0')
		return defValue;

	value = strtol(str, (char **) NULL, 10);

	if((value < INT_MIN) || (value > INT_MAX))
		return defValue;

	return (int) value;
}


static
double
EXTIT_DECL
get_double(persistence_ctx_t ctx, const char *name, double defValue)
{
	char	str[20];


	if(get_string(ctx, name, str, sizeof(str))
	 != PERSISTENCE_STATUS_SUCCESS)
	{
		return defValue;
	}

	if(str[0] == '\0')
		return defValue;

	return strtod(str, (char **) NULL);
}


#if	PERSISTENCE_INTERFACE_TARGET >= PERSISTENCE_INTERFACE_VERSION_1_2
static
persistence_status_t
EXTIT_DECL
set_binary(persistence_ctx_t ctx, const char *name, const char *value, unsigned int length)
{
	char	path[MAX_NAME_LEN+MAX_NAME_LEN+2];
	FILE *	fp;


	if(!isValidName(name))
		return PERSISTENCE_STATUS_INVALID;

	sprintf(path, "%s/%s", ctx->dir, name);

	if((fp = fopen(path, "wb")) == NULL)
		return PERSISTENCE_STATUS_NOTFOUND;

	if(fwrite(value, 1, length, fp) != length)
	{
		fclose(fp);
		return PERSISTENCE_STATUS_IOERROR;
	}

	fclose(fp);
	return PERSISTENCE_STATUS_SUCCESS;
}


static
int
EXTIT_DECL
get_binary(persistence_ctx_t ctx, const char *name, char *buf, unsigned int maxlen)
{
	char	path[MAX_NAME_LEN+MAX_NAME_LEN+2];
	FILE *	fp;
	size_t	len;


	if(!isValidName(name))
		return -1;

	sprintf(path, "%s/%s", ctx->dir, name);

	if((fp = fopen(path, "r")) == NULL)
		return -1;

	len = fread(buf, 1, maxlen, fp);

	if(ferror(fp) != 0)
	{
		fclose(fp);
		return -1;
	}

	fclose(fp);
	return (int) len;
}

#endif	/* PERSISTENCE_INTERFACE_TARGET >= PERSISTENCE_INTERFACE_VERSION_1_2 */
#endif	/* PERSISTENCE_INTERFACE_TARGET >= PERSISTENCE_INTERFACE_VERSION_1_1 */


/*
 * Simulate various implementations.
 * Normally this would just be all that is supported at the time.
 */
struct _persistence persistence_interface =
{
	/* v1.0 */
	open_ctx,
	close_ctx,
	set_string,
	get_string,
#if	PERSISTENCE_INTERFACE_TARGET >= PERSISTENCE_INTERFACE_VERSION_1_1
	/* v1.1 */
	set_int,
	set_double,
	get_int,
	get_double,
#if	PERSISTENCE_INTERFACE_TARGET >= PERSISTENCE_INTERFACE_VERSION_1_2
	/* v1.2 */
	set_binary,
	get_binary
#endif	/* PERSISTENCE_INTERFACE_TARGET >= PERSISTENCE_INTERFACE_VERSION_1_2 */
#endif	/* PERSISTENCE_INTERFACE_TARGET >= PERSISTENCE_INTERFACE_VERSION_1_1 */
};

