/*
 * @(#) if/configurable_util/fprint_utf8.c
 *
 * Print a configurable interface property value.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <inttypes.h>

#include <iv/base.h>

#include <if/configurable.h>
#include <if/configurable_util.h>


void
EXTIT_DECL
_if_configurable_fprint_utf8
(
	FILE *fp,
	const char *utf,
	extit_bool_t esc_ctrl
)
{
	char		ch;
	uint32_t	code;


	while((ch = *utf) != '\0')
	{
		utf++;

		if((ch & 0x80) == 0)
		{
			if(esc_ctrl && (iscntrl(ch) || (ch == '\\')))
			{
				switch(ch)
				{
					case 0x08:
						fputs("\\b", fp);
						break;

					case 0x09:
						fputs("\\t", fp);
						break;

					case 0x0A:
						fputs("\\n", fp);
						break;

					case 0x0B:
						fputs("\\v", fp);
						break;

					case 0x0C:
						fputs("\\f", fp);
						break;

					case 0x0D:
						fputs("\\r", fp);
						break;

					case 0x1B:
						fputs("\\e", fp);
						break;

					case '\\':
						fputs("\\\\", fp);
						break;

					default:
						fprintf(fp, "\\x%02x", ch);
				}
			}
			else
			{
				fputc(ch, fp);
			}
		}
		else
		{
			/*
			 * !!! NOT RFC 3629 Compliant !!!
			 * Could skip if required continuation bytes not found,
			 * but just assume correct UTF-8 data for our needs
			 */
			if((ch & 0xE0) == 0xC0)
			{
				code = ch & 0x1F;
			}
			else if((ch & 0xF0) == 0xE0)
			{
				code = ch & 0x0F;
			}
			else if((ch & 0xF8) == 0xF0)
			{
				code = ch & 0x07;
			}
			else
			{
				fprintf(fp, "\\x%02x", ch);
				continue;
			}

			while((ch = *utf) != '\0')
			{
				if((ch & 0xC0) != 0x80)
					break;

				utf++;

				code = (code << 6) | (ch & 0x3F);
			}

			if(code > 0xFFFF)
			{
				fprintf(fp, "\\U%08" PRIx32, code);
			}
			else
			{
				fprintf(fp, "\\u%04x", code);
			}
		}
	}
}
