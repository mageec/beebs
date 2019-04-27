/* BEEBS lcdnum benchmark

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
#define LOCAL_SCALE_FACTOR 13650

/* MDH WCET BENCHMARK SUITE. */

/* 2012/09/28, Jan Gustafsson <jan.gustafsson@mdh.se>
 * Changes:
 *  - The volatile variable n controls a loop, which is not correct. The loop will not terminate. Fixed.
 */

/***********************************************************************
 *  FILE: synthetic.c
 *
 *  PURPOSE: demonstrate effect of flow facts for straight loops
 *
 *  IDEA: reading from an in port mapped to a ten-item buffer,
 *        send first five characters to an LCD as numbers
 *
 ***********************************************************************/


unsigned char num_to_lcd(unsigned char a)
{
  /*   -0-            1            01
   *  1   2         2   4        02  04
   *   -3-    i.e.    8     i.e.   08
   *  4   5        16   32       10  20
   *   -6-           64            40
   *
   */
  switch(a)
    {
    case 0x00: return 0;
    case 0x01: return 0x24;
    case 0x02: return 1+4+8+16+64;
    case 0x03: return 1+4+8+32+64;
    case 0x04: return 2+4+8+32;
    case 0x05: return 1+4+8+16+64;
    case 0x06: return 1+2+8+16+32+64;
    case 0x07: return 1+4+32;
    case 0x08: return 0x7F;     /* light all */
    case 0x09: return 0x0F + 32 + 64;
    case 0x0A: return 0x0F + 16 + 32;
    case 0x0B: return 2+8+16+32+64;
    case 0x0C: return 1+2+16+64;
    case 0x0D: return 4+8+16+32+64;
    case 0x0E: return 1+2+8+16+64;
    case 0x0F: return 1+2+8+16;
    }
  return 0;
}

unsigned char out_vals[16];

int
verify_benchmark (int res __attribute ((unused)) )
{
  static const unsigned char out_ref[16] =
    { 0x00, 0x24, 0x5d, 0x6d, 0x2e, 0x5d, 0x7b, 0x25,
      0x7f, 0x6f, 0x3f, 0x7a, 0x53, 0x7c, 0x5b, 0x1b };

  return 0 == memcmp (out_vals, out_ref, 16);
}


void
initialise_benchmark (void)
{
}



int benchmark(void)
{
  int  j;

  for (j = 0; j < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); j++)
    {
      int i;

      for (i = 0; i < 16; i++)
	{
	  volatile unsigned char  in = (unsigned char) i;
	  volatile unsigned char  out;

	  out = num_to_lcd (in);
	  out_vals[i] = out;
	}
    }

  return 0;
}
