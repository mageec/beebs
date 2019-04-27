/* BEEBS qsort-exam benchmark

   Copyright (C) 2014 Embecosm Limited and University of Bristol

   Contributor James Pallister <james.pallister@bristol.ac.uk>

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

#include <string.h>
#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 965

/*************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                           sslim@archi.snu.ac.kr       */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: qsort-exam.c                                                   */
/*  SOURCE : Numerical Recipes in C - The Second Edition                 */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Non-recursive version of quick sort algorithm.                    */
/*     This example sorts 20 floating point numbers, arr[].              */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/


#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;
#define M 7
#define NSTACK 50

static const float arr_ref[20] = {
   5.0,   4.0,  10.3,    1.1,  5.7, 100.0, 231.0, 111.0,   49.5,  99.0,
  10.0, 150.0, 222.22, 101.0, 77.0,  44.0,  35.0,  20.54,  99.99, 88.88
};

static float arr[20];

int istack[100];

/* Fix for C. The original program assumed the values were in arr[1] to
   arr[n]. This version assumes arr[0] to arr[n-1]. */

void sort(unsigned long n)
{
	unsigned long i,ir=n-1,j,k,l=0;
	int jstack=0;
	float a,temp;

	for (;;) {
		if (ir-l < M) {
			for (j=l+1;j<=ir;j++) {
				a=arr[j];
				for (i=j-1;i>=l;i--) {
					if (arr[i] <= a) break;
					arr[i+1]=arr[i];
				}
				arr[i+1]=a;
			}
			if (jstack == 0) break;
			ir=istack[jstack--];
			l=istack[jstack--];
		} else {
			k=(l+ir) >> 1;
			SWAP(arr[k],arr[l+1])
			if (arr[l] > arr[ir]) {
				SWAP(arr[l],arr[ir])
			}
			if (arr[l+1] > arr[ir]) {
				SWAP(arr[l+1],arr[ir])
			}
			if (arr[l] > arr[l+1]) {
				SWAP(arr[l],arr[l+1])
			}
			i=l+1;
			j=ir;
			a=arr[l+1];
			for (;;) {
				i++; while (arr[i] < a) i++;
				j--; while (arr[j] > a) j--;
				if (j < i) break;
				SWAP(arr[i],arr[j]);
			}
			arr[l+1]=arr[j];
			arr[j]=a;
			jstack += 2;

			if (ir-i+1 >= j-l) {
				istack[jstack]=ir;
				istack[jstack-1]=i;
				ir=j-1;
			} else {
				istack[jstack]=j-1;
				istack[jstack-1]=l;
				l=i;
			}
		}
	}
}


int
verify_benchmark (int res __attribute ((unused)) )
{
  static const float arr_exp[20] = {
      1.10,   4.0,    5.0,    5.70,  10.0,
    10.30,  20.54,  35.0,   44.0,   49.50,
    77.0,   88.88,  99.0,   99.99, 100.0,
   101.0,  111.0,  150.0,  222.22, 231.00
  };

  return 0 == memcmp (arr, arr_exp, 20 * sizeof (arr[0]));
}


void
initialise_benchmark (void)
{
}


int
benchmark()
{
  int  i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    {
      memcpy (arr, arr_ref, 20 * sizeof (arr[0]));
      sort(20);
    }

  return 0;
}


