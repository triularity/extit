/*
 * @(#) stdif/configurable_stdimpl/floatrange.h
 *
 * Copyright (c) 2022, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__stdif__configurable_stdimpl__floatrange_h
#define	__stdif__configurable_stdimpl__floatrange_h

#include <float.h>

/*
 * The number of precision bits in a float
 */
#ifndef	FLT_MANT_BITS
#if	FLT_RADIX == 2
#define	FLT_MANT_BITS	FLT_MANT_DIG
#elif	FLT_RADIX == 16
#define	FLT_MANT_BITS	(FLT_MANT_DIG * 4)
#endif
#endif	/* !FLT_MANT_BITS */

/*
 * The number of precision bits in a double
 */
#ifndef	DBL_MANT_BITS
#if	FLT_RADIX == 2
#define	DBL_MANT_BITS	DBL_MANT_DIG
#elif	FLT_RADIX == 16
#define	DBL_MANT_BITS	(DBL_MANT_DIG * 4)
#endif
#endif	/* !DBL_MANT_BITS */

/*
 * Maximum precise value that can portably be represented as a float
 */
#ifdef	FLT_MANT_BITS
#define	FLT_MANT_MAXVAL	((1UL << (FLT_MANT_BITS)) - 1U)
#endif

/*
 * Maximum value precise that can portably be represented as a ouble
 */
#ifdef	DBL_MANT_BITS
#define	DBL_MANT_MAXVAL	((1ULL << (DBL_MANT_BITS)) - 1U)
#endif

#endif	/* !__stdif__configurable_stdimpl__floatrange_h */
