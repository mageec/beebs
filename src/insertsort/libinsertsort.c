/* BEEBS insertsort benchmark

   *************************************************************************
   *                                                                       *
   *   SNU-RT Benchmark Suite for Worst Case Timing Analysis               *
   *   =====================================================               *
   *                              Collected and Modified by S.-S. Lim      *
   *                                           sslim@archi.snu.ac.kr       *
   *                                         Real-Time Research Group      *
   *                                        Seoul National University      *
   *                                                                       *
   *                                                                       *
   *        < Features > - restrictions for our experimental environment   *
   *                                                                       *
   *          1. Completely structured.                                    *
   *               - There are no unconditional jumps.                     *
   *               - There are no exit from loop bodies.                   *
   *                 (There are no 'break' or 'return' in loop bodies)     *
   *          2. No 'switch' statements.                                   *
   *          3. No 'do..while' statements.                                *
   *          4. Expressions are restricted.                               *
   *               - There are no multiple expressions joined by 'or',     *
   *                'and' operations.                                      *
   *          5. No library calls.                                         *
   *               - All the functions needed are implemented in the       *
   *                 source file.                                          *
   *                                                                       *
   *                                                                       *
   *************************************************************************
   *                                                                       *
   *  FILE: insertsort.c                                                   *
   *  SOURCE : Public Domain Code                                          *
   *                                                                       *
   *  DESCRIPTION :                                                        *
   *                                                                       *
   *     Insertion sort for 10 integer numbers.                            *
   *     The integer array a[] is initialized in main function.            *
   *                                                                       *
   *  REMARK :                                                             *
   *                                                                       *
   *  EXECUTION TIME :                                                     *
   *                                                                       *
   *                                                                       *
   *************************************************************************

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

#include <string.h>
#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 10443

unsigned int a[11];    /* assume all data is positive */

int
benchmark (void)
{
  static const unsigned int a_ref[11] = {
    0, 11, 10, 9, 8 ,7, 6, 5, 4, 3, 2
  };

  int  k;

  for (k = 0; k < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); k++)
    {
      int i,j, temp;

      memcpy (a, a_ref, 11 * sizeof (a[0]));
      i = 2;

      while(i <= 10){
	j = i;
	while (a[j] < a[j-1])
	  {
	    temp = a[j];
	    a[j] = a[j-1];
	    a[j-1] = temp;
	    j--;
	  }
	i++;
      }
    }

  return 0;
}

void initialise_benchmark() {
}

int verify_benchmark(int unused) {
  int expected[] = {0,2,3,4,5,6,7,8,9,10,11};
  return 0 == memcmp (a, expected, 11 * sizeof (a[0]));
}
