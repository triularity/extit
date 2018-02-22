/*
 * @(#) stdif/configurable_stdimpl/get_float.c
 *
 * Configurable Interface - get_float@1.0 standard implementation.
 *
 * Copyright (c) 2016-2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>
#include <float.h>

#include <extit/base.h>
#include <stdif/configurable.h>
#include <stdif/configurable_impl.h>
#include <stdif/configurable_stdimpl.h>

/*
 * The number of precision bits in a float
 */
#if	FLT_RADIX == 2
#define	FLT_MANT_BITS	FLT_MANT_DIG
#elif	FLT_RADIX == 16
#define	FLT_MANT_BITS	(FLT_MANT_DIG * 4)
#endif


/**
 * Standard implementation to get a property value as a 32-bit
 * floating point.
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
 * @see		@{func stdif_configurable_stdimpl_set_float__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, float)}
 * @see		@{func stdif_configurable_stdimpl_get_float__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, float *)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_float__1_0
(
	stdif_configurable_1_0_t *configurable,
	stdif_configurable_propref_t *prop,
	float *valuep
)
{
	return stdif_configurable_stdimpl_get_float__1_0_base(
		configurable, configurable, prop, valuep);
}


/**
 * Standard implementation helper to get a property value as a 32-bit
 * floating point.
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
 * @see		@{func stdif_configurable_stdimpl_set_float__1_0_base(stdif_configurable_1_0_t *, void *, stdif_configurable_propref_t *, float)}
 * @see		@{func stdif_configurable_stdimpl_get_float__1_0(stdif_configurable_1_0_t *, stdif_configurable_propref_t *, float *)}
 */
extit_status_t
EXTIT_DECL
stdif_configurable_stdimpl_get_float__1_0_base
(
	stdif_configurable_1_0_t *configurable,
	void *base,
	stdif_configurable_propref_t *prop,
	float *valuep
)
{
	double		value_d;
	int32_t		value_i32;
	int64_t		value_i64;
	uint32_t	value_u32;
	uint64_t	value_u64;


	base = ((char *) base) + prop->offset;

	switch(prop->definition.type)
	{
		case STDIF_CONFIGURABLE_TYPE_DOUBLE:
			value_d = *((double *) base);

			if((value_d > ((double) FLT_MAX))
			 || (value_d < -((double) FLT_MAX)))
			{
				return EXTIT_STATUS_INVALID;
			}

			*valuep = (float) value_d;
			break;

		case STDIF_CONFIGURABLE_TYPE_FLOAT:
			*valuep = *((float *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT8:
			*valuep = *((int8_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_INT16:
			*valuep = *((int16_t *) base);
			break;

#ifdef	FLT_MANT_BITS
		case STDIF_CONFIGURABLE_TYPE_INT32:
			value_i32 = *((int32_t *) base);

#if	FLT_MANT_BITS < 31
			if((value_i32 > ((int32_t) 1 << FLT_MANT_BITS))
			 || (value_i32 < -((int32_t) 1 << FLT_MANT_BITS)))
			{
				return EXTIT_STATUS_INVALID;
			}
#endif	/* FLT_MANT_BITS < 31 */

			*valuep = (float) value_i32;
			break;

		case STDIF_CONFIGURABLE_TYPE_INT64:
			value_i64 = *((int64_t *) base);

#if	FLT_MANT_BITS < 63
			if((value_i64 > ((int64_t) 1 << FLT_MANT_BITS))
			 || (value_i64 < -((int64_t) 1 << FLT_MANT_BITS)))
			{
				return EXTIT_STATUS_INVALID;
			}
#endif	/* FLT_MANT_BITS < 63 */

			*valuep = (float) value_i64;
			break;
#else	/* FLT_MANT_BITS */
#warn	STDIF_CONFIGURABLE_TYPE_INT32 property not supported
#warn	STDIF_CONFIGURABLE_TYPE_INT64 property not supported
#endif	/* FLT_MANT_BITS */

		case STDIF_CONFIGURABLE_TYPE_UINT8:
			*valuep = *((uint8_t *) base);
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT16:
			*valuep = *((uint16_t *) base);
			break;

#ifdef	FLT_MANT_BITS
		case STDIF_CONFIGURABLE_TYPE_UINT32:
			value_u32 = *((uint32_t *) base);

#if	FLT_MANT_BITS < 32
			if(value_u32 > ((uint32_t) 1 << FLT_MANT_BITS))
				return EXTIT_STATUS_INVALID;
#endif	/* FLT_MANT_BITS < 32 */

			*valuep = (float) value_u32;
			break;

		case STDIF_CONFIGURABLE_TYPE_UINT64:
			value_u64 = *((uint64_t *) base);

#if	FLT_MANT_BITS < 64
			if(value_u64 > ((uint64_t) 1 << FLT_MANT_BITS))
				return EXTIT_STATUS_INVALID;
#endif	/* FLT_MANT_BITS < 64 */

			*valuep = (float) value_u64;
			break;
#else	/* FLT_MANT_BITS */
#warn	STDIF_CONFIGURABLE_TYPE_UINT32 property not supported
#warn	STDIF_CONFIGURABLE_TYPE_UINT64 property not supported
#endif	/* FLT_MANT_BITS */

		default:
			return STDIF_CONFIGURABLE_STATUS_MISMATCH;
	}

	return EXTIT_STATUS_OK;
}
