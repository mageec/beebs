/* BEEBS select benchmark

   SOURCE : Numerical Recipes in C - The Second Edition

   Copyright (C) 2014 Embecosm Limited and University of Bristol

   Contributor Pierre Langlois <pierre.langlois@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

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

#include "math.h"
#include "string.h"
#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 1749

static const float arr_ref[20] = {
    5.00,   4.00,  10.30,   1.10,   5.70,
  100.00, 231.00, 111.00,  49.50,  99.00,
   10.00, 150.00, 222.22, 101.00,  77.00,
   44.00,  35.00,  20.54,  99.99, 888.88
};

float arr[20];

static void
swap (unsigned long a,
      unsigned long b)
{
  float t = arr[a];

  arr[a] = arr[b];
  arr[b] = t;
}

/* Fix for C. The original program assumed the values were in arr[1] to
   arr[n]. This version assumes arr[0] to arr[n-1]. */

float
      select(unsigned long k,		/* Element wanted */
	     unsigned long n)		/* Size of arr */
{
  unsigned long i,ir,j,l,mid;
  float a,temp;
  int flag, flag2;

  l=0;
  ir=n-1;

  while (1)
    {
      if (ir <= (l + 1))
	{
	  if (ir == (l + 1) && (arr[ir] < arr[l]))
	      swap (l, ir);

	  return arr[k - 1];
	}
      else
	{
	  mid = (l + ir) >> 1;
	  swap (mid, l + 1);

	  if (arr[l] > arr[ir])
	    swap (l, ir);

	  if (arr[l + 1] > arr[ir])
	    swap (l + 1, ir);

	  if (arr[l] > arr[l + 1])
	    swap (l, l + 1);

	  i = l + 1;
	  j = ir;
	  a = arr[l + 1];

	  while (1)
	    {
	      do
		i++;
	      while (arr[i] < a);

	      do
		j--;
	      while (arr[j] > a);

	      if (j < i)
		break;

	      swap (i, j);
	    }

	  arr[l + 1] = arr[j];
	  arr[j] = a;

	  if (j >= (k - 1))
	    ir = j - 1;

	  if (j <= (k - 1))
	    l = i;
	}
    }
}

static int x, y;
volatile float result;

int
benchmark (void)
{
  int  i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    {
      memcpy  (arr, arr_ref, 20 * sizeof (arr[0]));
      x = 10;
      y = 20;
      result = select(x, y);
    }

  return 0;
}

void initialise_benchmark() {
}


int
verify_benchmark (int res)
{
  return fabs (result - 49.50) < 1.0e-6;
}
