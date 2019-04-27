
/* BEEBS fac benchmark

   MDH WCET BENCHMARK SUITE

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

#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 9195

long int fac (int n)
{
  if (n == 0)
     return 1;
  else
     return (n * fac (n-1));
}


void
initialise_benchmark (void)
{
}


int
benchmark (void)
{
  int  j;
  volatile long int s;

  for (j = 0; j < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); j++)
    {
      int i;
      volatile int n;

      s = 0;
      n = 10;
      for (i = 0;  i <= n; i++)
	s += fac (i);
    }

  return s % 65536L;
}

int verify_benchmark(int r)
{
  return (4037914L  % 65536L) == r;
}
