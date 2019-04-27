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
#define LOCAL_SCALE_FACTOR 466

/* Global variables, so calls in BENCHMARK are not optimised away.  */
int int_dest[7];
char char_dest [20];


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
      volatile int i1, i2;
      trio_sscanf("123", "%d", &i1);
      int_dest[0] = i1;
      trio_sscanf("123 456", "%d %d", &i1, &i2);
      int_dest[1] = i1;
      int_dest[2] = i2;
      trio_sscanf("000000123", "%d", &i1);
      int_dest[3] = i1;
      trio_sscanf("cdefg", "%x", &i1);
      int_dest[4] = i1;
      trio_sscanf("FF", "%x",&i1);
      int_dest[5] = i1;
      trio_sscanf("abcdefg", "%[^f]%xg", &char_dest, &i1);
      int_dest[6] = i1;
    }

  return 0;
}

int verify_benchmark(int unused) {
  static const int int_exp[7] = {
    123, 123, 456, 123, 0xcdef, 0xff, 0xf
  };
  static const char char_exp [20] = "abcde";

  return (0 == memcmp (int_exp, int_dest, 7 * sizeof (int_exp[0])))
    && (0 == strcmp (char_exp, char_dest));
}
