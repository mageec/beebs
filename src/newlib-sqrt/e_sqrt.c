/* BEEBS newlib e_sqrt implementation

   Copyright (C) 2014 Embecosm Limited and University of Bristol

   Contributor Pierre Langlois <pierre.langlois@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Energy Benchmark Suite.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>. */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/* __ieee754_sqrt(x)
 * Return correctly rounded sqrt.
 *           ------------------------------------------
 *	     |  Use the hardware sqrt if you have one |
 *           ------------------------------------------
 * Method:
 *   Bit by bit method using integer arithmetic. (Slow, but portable)
 *   1. Normalization
 *	Scale x to y in [1,4) with even powers of 2:
 *	find an integer k such that  1 <= (y=x*2^(2k)) < 4, then
 *		sqrt(x) = 2^k * sqrt(y)
 *   2. Bit by bit computation
 *	Let q  = sqrt(y) truncated to i bit after binary point (q = 1),
 *	     i							 0
 *                                     i+1         2
 *	    s  = 2*q , and	y  =  2   * ( y - q  ).		(1)
 *	     i      i            i                 i
 *
 *	To compute q    from q , one checks whether
 *		    i+1       i
 *
 *			      -(i+1) 2
 *			(q + 2      ) <= y.			(2)
 *     			  i
 *							      -(i+1)
 *	If (2) is false, then q   = q ; otherwise q   = q  + 2      .
 *		 	       i+1   i             i+1   i
 *
 *	With some algebric manipulation, it is not difficult to see
 *	that (2) is equivalent to
 *                             -(i+1)
 *			s  +  2       <= y			(3)
 *			 i                i
 *
 *	The advantage of (3) is that s  and y  can be computed by
 *				      i      i
 *	the following recurrence formula:
 *	    if (3) is false
 *
 *	    s     =  s  ,	y    = y   ;			(4)
 *	     i+1      i		 i+1    i
 *
 *	    otherwise,
 *                         -i                     -(i+1)
 *	    s	  =  s  + 2  ,  y    = y  -  s  - 2  		(5)
 *           i+1      i          i+1    i     i
 *
 *	One may easily use induction to prove (4) and (5).
 *	Note. Since the left hand side of (3) contain only i+2 bits,
 *	      it does not necessary to do a full (53-bit) comparison
 *	      in (3).
 *   3. Final rounding
 *	After generating the 53 bits result, we compute one more bit.
 *	Together with the remainder, we can decide whether the
 *	result is exact, bigger than 1/2ulp, or less than 1/2ulp
 *	(it will never equal to 1/2ulp).
 *	The rounding mode can be detected by checking whether
 *	huge + tiny is equal to huge, and whether huge - tiny is
 *	equal to huge for some floating point number "huge" and "tiny".
 *
 * Special cases:
 *	sqrt(+-0) = +-0 	... exact
 *	sqrt(inf) = inf
 *	sqrt(-ve) = NaN		... with invalid signal
 *	sqrt(NaN) = NaN		... with invalid signal for signaling NaN
 *
 * Other methods : see the appended file at the end of the program below.
 *---------------
 */

#include "platformcode.h"
#include <stdint.h>

#define __IEEE_LITTLE_ENDIAN

/* A union which permits us to convert between a double and two 32 bit
   ints.  */

#ifdef __IEEE_BIG_ENDIAN

typedef union
{
  int64_t value;
  struct
  {
    uint32_t msw;
    uint32_t lsw;
  } parts;
} ieee_double_shape_type;

#endif

#ifdef __IEEE_LITTLE_ENDIAN

typedef union
{
  int64_t value;
  struct
  {
    uint32_t lsw;
    uint32_t msw;
  } parts;
} ieee_double_shape_type;

#endif

/* Get two 32 bit ints from a double.  */

#define EXTRACT_WORDS(ix0,ix1,d)				\
  ieee_double_shape_type ew_u;					\
  ew_u.value = (d);						\
  (ix0) = ew_u.parts.msw;					\
  (ix1) = ew_u.parts.lsw;

/* Set a double from two 32 bit ints.  */

#define INSERT_WORDS(d,ix0,ix1)					\
  ieee_double_shape_type iw_u;					\
  iw_u.parts.msw = (ix0);					\
  iw_u.parts.lsw = (ix1);					\
  (d) = iw_u.value;

static const int64_t one = 1.0;
static const int64_t tiny=1.0e-300;

int64_t __ieee754_sqrt(int64_t x)
{
	int64_t z;
	int32_t sign = (int)0x80000000;
	uint32_t r,t1,s1,ix1,q1;
	int32_t ix0,s0,q,m,t,i;

	EXTRACT_WORDS(ix0,ix1,x);

    /* take care of Inf and NaN */
	if((ix0&0x7ff00000)==0x7ff00000) {
	    return x*x+x;		/* sqrt(NaN)=NaN, sqrt(+inf)=+inf
					   sqrt(-inf)=sNaN */
	}
    /* take care of zero */
	if(ix0<=0) {
	    if(((ix0&(~sign))|ix1)==0) return x;/* sqrt(+-0) = +-0 */
	    else if(ix0<0)
		return (x-x)/(x-x);		/* sqrt(-ve) = sNaN */
	}
    /* normalize x */
	m = (ix0>>20);
	if(m==0) {				/* subnormal x */
	    while(ix0==0) {
		m -= 21;
		ix0 |= (ix1>>11); ix1 <<= 21;
	    }
	    for(i=0;(ix0&0x00100000)==0;i++) ix0<<=1;
	    m -= i-1;
	    ix0 |= (ix1>>(32-i));
	    ix1 <<= i;
	}
	m -= 1023;	/* unbias exponent */
	ix0 = (ix0&0x000fffff)|0x00100000;
	if(m&1){	/* odd m, double x to make it even */
	    ix0 += ix0 + ((ix1&sign)>>31);
	    ix1 += ix1;
	}
	m >>= 1;	/* m = [m/2] */

    /* generate sqrt(x) bit by bit */
	ix0 += ix0 + ((ix1&sign)>>31);
	ix1 += ix1;
	q = q1 = s0 = s1 = 0;	/* [q,q1] = sqrt(x) */
	r = 0x00200000;		/* r = moving bit from right to left */

	while(r!=0) {
	    t = s0+r;
	    if(t<=ix0) {
		s0   = t+r;
		ix0 -= t;
		q   += r;
	    }
	    ix0 += ix0 + ((ix1&sign)>>31);
	    ix1 += ix1;
	    r>>=1;
	}

	r = sign;
	while(r!=0) {
	    t1 = s1+r;
	    t  = s0;
	    if((t<ix0)||((t==ix0)&&(t1<=ix1))) {
		s1  = t1+r;
		if(((t1&sign)==sign)&&(s1&sign)==0) s0 += 1;
		ix0 -= t;
		if (ix1 < t1) ix0 -= 1;
		ix1 -= t1;
		q1  += r;
	    }
	    ix0 += ix0 + ((ix1&sign)>>31);
	    ix1 += ix1;
	    r>>=1;
	}

    /* use floating add to find out rounding direction */
	if((ix0|ix1)!=0) {
	    z = one-tiny; /* trigger inexact flag */
	    if (z>=one) {
	        z = one+tiny;
	        if (q1==(uint32_t)0xffffffff) { q1=0; q += 1;}
		else if (z>one) {
		    if (q1==(uint32_t)0xfffffffe) q+=1;
		    q1+=2;
		} else
	            q1 += (q1&1);
	    }
	}
	ix0 = (q>>1)+0x3fe00000;
	ix1 =  q1>>1;
	if ((q&1)==1) ix1 |= sign;
	ix0 += (m <<20);
	INSERT_WORDS(z,ix0,ix1);
	return z;
}


/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)


void
benchmark (void)
{
  /* Tell the compiler not to optimize out these calls. */
  volatile int64_t result = 0;
  result = __ieee754_sqrt(2);
  result = __ieee754_sqrt(3);
  result = __ieee754_sqrt(5);
  result = __ieee754_sqrt(6);
  result = __ieee754_sqrt(7);
  result = __ieee754_sqrt(8);
}


int
main (void)
{
  int i;

  initialise_trigger ();
  start_trigger ();

  for (i = 0; i < SCALE_FACTOR; i++)
    benchmark ();

  stop_trigger ();
  return 0;
}
