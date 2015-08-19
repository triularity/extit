/*
 * @(#) extit/src/ir/ir.c
 *
 * Interface Repository implementation.
 *
 * Copyright (c) 2014, 2015, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <extit/base.h>
#include <extit/ir.h>
#include <iv/repository.h>


/**
 * Convert ExtIt flags to Interface Versioning flags
 */
static
unsigned int
extit_to_ivr_flags(unsigned int flags)
{
	switch(flags & EXTIT_FLAG_LOG)
	{
		case EXTIT_FLAG_LOG_MINIMAL:
			return IV_REPOSITORY_FLAG_LOG_MINIMAL;

		case EXTIT_FLAG_LOG_NORMAL:
			return IV_REPOSITORY_FLAG_LOG_NORMAL;

		case EXTIT_FLAG_LOG_DEBUG:
			return IV_REPOSITORY_FLAG_LOG_DEBUG;

		case EXTIT_FLAG_LOG_TRACE:
			return IV_REPOSITORY_FLAG_LOG_TRACE;

		default:
			return IV_REPOSITORY_FLAG_LOG_MINIMAL;
	}
}


/**
 * Convert Interface Versioning flags to ExtIt flags
 */
static
unsigned int
ivr_to_extit_flags(unsigned int flags)
{
	switch(flags & IV_REPOSITORY_FLAG_LOG)
	{
		case IV_REPOSITORY_FLAG_LOG_MINIMAL:
			return EXTIT_FLAG_LOG_MINIMAL;

		case IV_REPOSITORY_FLAG_LOG_NORMAL:
			return EXTIT_FLAG_LOG_NORMAL;

		case IV_REPOSITORY_FLAG_LOG_DEBUG:
			return EXTIT_FLAG_LOG_DEBUG;

		case IV_REPOSITORY_FLAG_LOG_TRACE:
			return EXTIT_FLAG_LOG_TRACE;

		default:
			return EXTIT_FLAG_LOG_MINIMAL;
	}
}


/**
 * Convert an Interface Versioning status to an ExtIt status
 */
static
extit_status_t
ivr_to_extit_status(iv_repository_status_t status)
{
	switch(status)
	{
		case IV_REPOSITORY_STATUS_FAIL:
			return EXTIT_STATUS_FAIL;

		case IV_REPOSITORY_STATUS_INVALID:
			return EXTIT_STATUS_INVALID;

		case IV_REPOSITORY_STATUS_NOMEM:
			return EXTIT_STATUS_NOMEM;

		case IV_REPOSITORY_STATUS_OK:
			return EXTIT_STATUS_OK;

		default:
			return EXTIT_STATUS_FAIL;
	}
}


/**
 ** Public API (v1.0)
 **/

EXTIT_EXPORT
void
EXTIT_DECL
extit_ir_cleanup(iv_repository_t *ir)
{
	iv_repository_cleanup(ir);
}


EXTIT_EXPORT
iv_repository_t *
EXTIT_DECL
extit_ir_create(unsigned int flags)
{
	iv_repository_t *	ivr;


	if((ivr = iv_repository_create()) != NULL)
		iv_repository_setFlags(ivr, extit_to_ivr_flags(flags));

	return ivr;
}


EXTIT_EXPORT
void
EXTIT_DECL
extit_ir_destroy(iv_repository_t *ir)
{
	iv_repository_destroy(ir);
}


EXTIT_EXPORT
unsigned int
EXTIT_DECL
extit_ir_getFlags(const iv_repository_t *ir)
{
	return ivr_to_extit_flags(iv_repository_getFlags(ir));
}


EXTIT_EXPORT
void *
EXTIT_DECL
extit_ir_getInterface(const iv_repository_t *ir, const char *id, iv_version_t version)
{
	return iv_repository_get(ir, id, version);
}


EXTIT_EXPORT
iv_version_t
EXTIT_DECL
extit_ir_queryInterface(const iv_repository_t *ir, const char *id, iv_version_t base_version)
{
	return iv_repository_query(ir, id, base_version);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_ir_removeInterface(iv_repository_t *ir, const char *id, iv_version_t version, void *old_valuep)
{
	return ivr_to_extit_status(
		iv_repository_remove(ir, id, version, old_valuep));
}


EXTIT_EXPORT
void
EXTIT_DECL
extit_ir_setFlags(iv_repository_t *ir, unsigned int flags)
{
	iv_repository_setFlags(ir, extit_to_ivr_flags(flags));
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_ir_setInterface(iv_repository_t *ir, const char *id, iv_version_t version, void *value, void *old_valuep)
{
	return ivr_to_extit_status(
		iv_repository_set(ir, id, version, value, old_valuep));
}
