/* BEEBS bsort100 benchmark

   Copyright (C) 2014 Embecosm Limited and University of Bristol

   Contributor James Pallister <james.pallister@bristol.ac.uk>

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

#include "platformcode.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 7)

/* bsort100.c */

/* All output disabled for wcsim */
#define WCSIM 1


#include <stdio.h>

#define WORSTCASE 1
#define FALSE 0
#define TRUE 1
#define NUMELEMS 100
#define MAXDIM   (NUMELEMS+1)

/* BUBBLESORT BENCHMARK PROGRAM:
 * This program tests the basic loop constructs, integer comparisons,
 * and simple array handling of compilers by sorting 10 arrays of
 * randomly generated integers.
 */

int Array[MAXDIM], Seed;
int factor;

benchmark()
{
   long  StartTime, StopTime;
   float TotalTime;

#ifndef WCSIM
   printf("\n *** BUBBLE SORT BENCHMARK TEST ***\n\n");
   printf("RESULTS OF TEST:\n\n");
#endif
   Initialize(Array);
   /*   StartTime = ttime (); */
   BubbleSort(Array);
   /*   StopTime = ttime(); */
   /*   TotalTime = (StopTime - StartTime) / 1000.0; */
#ifndef WCSIM
   printf("     - Number of elements sorted is %d\n", NUMELEMS);
   printf("     - Total time sorting is %3.3f seconds\n\n", TotalTime);
#endif
}


Initialize(Array)
int Array[];
/*
 * Initializes given array with randomly generated integers.
 */
{
   int  Index, fact;

#ifdef WORSTCASE
   factor = -1;
#else
   factor = 1;
#endif

fact = factor;
for (Index = 1; Index <= NUMELEMS; Index ++)
    Array[Index] = Index*fact;
}



BubbleSort(Array)
int Array[];
/*
 * Sorts an array of integers of size NUMELEMS in ascending order.
 */
{
   int Sorted = FALSE;
   int Temp, LastIndex, Index, i;

   for (i = 1;
	i <= NUMELEMS-1;           /* apsim_loop 1 0 */
	i++)
   {
      Sorted = TRUE;
      for (Index = 1;
	   Index <= NUMELEMS-1;      /* apsim_loop 10 1 */
	   Index ++) {
         if (Index > NUMELEMS-i)
            break;
         if (Array[Index] > Array[Index + 1])
         {
            Temp = Array[Index];
            Array[Index] = Array[Index+1];
            Array[Index+1] = Temp;
            Sorted = FALSE;
         }
      }

      if (Sorted)
         break;
   }

#ifndef WCSIM
   if (Sorted || i == 1)
      fprintf(stderr, "array was successfully sorted in %d passes\n", i-1);
   else
      fprintf(stderr, "array was unsuccessfully sorted in %d passes\n", i-1);
#endif
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
