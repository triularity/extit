/*
 * @(#) if/messaging_stdimpl/keybuf.c
 *
 * Copyright (c) 2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <extit/base.h>

#include "internal.h"


void
if_messaging_stdimpl_keybuf_init
(
	keybuf_t *keybuf
)
{
	keybuf->buf = keybuf->def_buffer;
	keybuf->len = sizeof(keybuf->def_buffer);
}


void
if_messaging_stdimpl_keybuf_release
(
	keybuf_t *keybuf
)
{
	if(keybuf->buf != keybuf->def_buffer)
		free(keybuf->buf);
}


extit_status_t
if_messaging_stdimpl_keybuf_setids(
	keybuf_t *keybuf,
	const char *mid,
	const char *iid
)
{
	size_t		mid_len;
	size_t		iid_len;
	size_t		keylen;


	mid_len = strlen(mid);
	iid_len = strlen(iid);

	keylen = mid_len + iid_len + 2;

	if(keybuf->len <= keylen)
	{
		if(keybuf->buf != keybuf->def_buffer)
			free(keybuf->buf);

		if((keybuf->buf = malloc(keylen)) == NULL)
		{
			/* Fallback to static buffer if possible */
			if(sizeof(keybuf->def_buffer) < keylen)
				return EXTIT_STATUS_NOMEM;

			keybuf->buf = keybuf->def_buffer;
			keybuf->len = sizeof(keybuf->def_buffer);
		}
	}

	memcpy(keybuf->buf, mid, mid_len);
	keybuf->buf[mid_len] = '\0';
	memcpy(&keybuf->buf[mid_len+1], iid, iid_len);
	keybuf->buf[keylen-1] = '\0';

	return EXTIT_STATUS_OK;
}
