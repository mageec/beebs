/* BEEBS template benchmark

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
#include "trio.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 433


/* BEEBS heap is just an array */

#define HEAP_SIZE 8192
static char heap[HEAP_SIZE];

char output[5][20];


int
verify_benchmark (int res __attribute ((unused)) )
{
  int i;
  char exp[5][20] = { "123", "123", "  123", "0007b", "   10" };

  for (i = 0; i < 5; i++)
    if (0 != strcmp (exp[i], output[i]))
      return 0;

  return 1;
}


void
initialise_benchmark (void)
{
}

int
benchmark (void)
{
  int  i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    {
      init_heap_beebs ((void *) heap, HEAP_SIZE);

      trio_snprintf(output[0], 20, "%d", 123);
      trio_snprintf(output[1], 20, "%ld", 123);
      trio_snprintf(output[2], 20, "%5d", 123);
      trio_snprintf(output[3], 20, "%05x", 123);
      trio_snprintf(output[4], 20, "%*d", 5, 10);
    }

  return 0;
}
