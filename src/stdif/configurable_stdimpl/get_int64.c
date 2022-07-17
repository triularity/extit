/*
 * @(#) stdif/configurable_stdimpl/get_int64.c
 *
 * Configurable Interface - get_int64@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, 2022. Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>
#include <math.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>

#include "floatrange.h"


/**
 * Standard implementation to get a property value as a signed
 * 64-bit integer.
 *
 * @note	The contents of memory referenced by @{param valuep}
 *		will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation returns the value at
 *		@{param configurable} @{code +} @{param prop}@{code ->offset}
 *		of the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_DOUBLE},
 *		@{constant STDIF_CONFIGURABLE_TYPE_ENUM32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_FLOAT},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT8},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT16},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT64},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT8},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT16},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT64}.
 *
 * @param	configurable	The configurable instance.
 * @param	prop		The property reference.
 * @param	valuep		The address to store the value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible,
 *		or @{constant EXTIT_STATUS_INVALID} if the value is out
 *		of valid range for the return type.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_set_int64__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, int64_t)}
 * @see		@{func stdif_configurable_stdimpl_get_int64__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, int64_t *)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_int64__1_0
(
	stdif_configurable_1_0_t *configurable,
	stdif_configurable_propref_t *prop,
	int64_t *valuep
)
{
	return stdif_configurable_stdimpl_get_int64__1_0_base(
		configurable, configurable, prop, valuep);
}


/**
 * Standard implementation helper to get a property value as a signed
 * 64-bit integer.
 *
 * @note	The contents of memory referenced by @{param valuep}
 *		will be left unchanged if anything except
 *		@{constant EXTIT_STATUS_OK} is returned.
 *
 * @note	This implementation returns the value at
 *		@{param base} @{code +} @{param prop}@{code ->offset}
 *		of the binary type defined by the property.
 *
 * @note	This implementation supports the following property types:
 *		@{constant STDIF_CONFIGURABLE_TYPE_DOUBLE},
 *		@{constant STDIF_CONFIGURABLE_TYPE_ENUM32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_FLOAT},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT8},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT16},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_INT64},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT8},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT16},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT32},
 *		@{constant STDIF_CONFIGURABLE_TYPE_UINT64}.
 *
 * @param	configurable	The configurable instance.
 * @param	base		The base address.
 * @param	prop		The property reference.
 * @param	valuep		The address to store the value.
 *
 * @return	@{constant EXTIT_STATUS_OK} if successful,
 *		@{constant STDIF_CONFIGURABLE_STATUS_MISMATCH} if the
 *		property type is incompatible,
 *		or @{constant EXTIT_STATUS_INVALID} if the value is out
 *		of valid range for the return type.
 *
 * @since	1.0
 *
 * @see		@{func stdif_configurable_stdimpl_set_int64__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, int64_t)}
 * @see		@{func stdif_configurable_stdimpl_get_int64__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, int64_t *)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_int64__1_0_base
(
	stdif_configurable_1_0_t *configurable,
	void *base,
	stdif_configurable_propref_t *prop,
	int64_t *valuep
)
{
	double		value_d;
	float		value_f;
	uint64_t	value_u64;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
#ifdef	DBL_MANT_BITS
		case STDIF_CONFIGURABLE_TYPE_DOUBLE:
			value_d = trunc(*((double *) base));

#if	DBL_MANT_BITS < 63
			if((value_d > (double) DBL_MANT_MAXVAL)
			 || (value_d < (double) -DBL_MANT_MAXVAL))
			{
				return EXTIT_STATUS_INVALID;
			}
#else
			if((value_d > (double) INT64_MAX)
			 || (value_d < (double) INT64_MIN))
			{
				return EXTIT_STATUS_INVALID;
			}
#endif	/* DBL_MANT_BITS < 63 */

			*valuep = (int64_t) value_d;
			break;
#else	/* DBL_MANT_BITS */
#warn	STDIF_CONFIGURABLE_TYPE_DOUBLE property not supported
#endif	/* DBL_MANT_BITS */

#ifdef	FLT_MANT_BITS
		case STDIF_CONFIGURABLE_TYPE_FLOAT:
			value_f = truncf(*((float *) base));

#if	FLT_MANT_BITS < 63
			if((value_f > (float) FLT_MANT_MAXVAL)
			 || (value_f < (float) -FLT_MANT_MAXVAL))
			{
				return EXTIT_STATUS_INVALID;
			}
#else
			if((value_f > (float) INT64_MAX)
			 || (value_f < (float) INT64_MIN))
			{
				return EXTIT_STATUS_INVALID;
			}
#endif	/* FLT_MANT_BITS < 63 */

			*valuep = (int64_t) value_f;
			break;
#else	/* FLT_MANT_BITS */
#warn	STDIF_CONFIGURABLE_TYPE_FLOAT property not supported
#endif	/* FLT_MANT_BITS */

		case STDIF_CONFIGURABLE_TYPE_INT8:
			*valuep = *((int8_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT16:
			*valuep = *((int16_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT32:
			*valuep = *((int32_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT64:
			*valuep = *((int64_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT8:
			*valuep = *((uint8_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT16:
			*valuep = *((uint16_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT32:
		case STDIF_CONFIGURABLE_TYPE_ENUM32:
			*valuep = *((uint32_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT64:
			value_u64 = *((uint64_t *) base);

			if(value_u64 > (uint64_t) INT64_MAX)
				return EXTIT_STATUS_INVALID;

			*valuep = (int64_t) value_u64;
			break;

		default:
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
