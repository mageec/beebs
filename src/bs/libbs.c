/* This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

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
/*  FILE: bs.c                                                           */
/*  SOURCE : Public Domain Code                                          */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Binary search for the array of 15 integer elements.               */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

#include <string.h>
#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 9568


struct DATA {
  int  key;
  int  value;
}  ;

#define NUMVALS 100

struct DATA data[NUMVALS] = {
  {   2, 1440 }, {   6,  130 }, {   9, 1960 }, {  12, 1750 }, {  13,  270 },
  {  15,  600 }, {  18,  790 }, {  19,  990 }, {  20,  400 }, {  23, 1300 },
  {  27,  880 }, {  29,  350 }, {  30, 1070 }, {  33,   70 }, {  39,  580 },
  {  40,  360 }, {  42,  320 }, {  43, 1430 }, {  45,  800 }, {  47,  510 },
  {  48,  850 }, {  50,   70 }, {  53, 1500 }, {  55, 1680 }, {  57,  980 },
  {  58,  570 }, {  59, 1230 }, {  61, 1930 }, {  63, 1710 }, {  64, 1640 },
  {  71, 1140 }, {  72,  680 }, {  73,  710 }, {  74,  460 }, {  77,  130 },
  {  79,  110 }, {  83, 1700 }, {  84,  610 }, {  85, 1540 }, {  86,  210 },
  {  89, 1290 }, {  92, 1480 }, {  94,   50 }, {  95,  930 }, {  99,  760 },
  { 101,  990 }, { 102,  190 }, { 104, 1160 }, { 105, 1860 }, { 106, 1960 },
  { 108, 1910 }, { 109, 1610 }, { 111, 1390 }, { 114, 1800 }, { 116, 1860 },
  { 117,  400 }, { 118, 1200 }, { 119,  930 }, { 120,  930 }, { 123,  430 },
  { 124,  130 }, { 125,  740 }, { 126,  870 }, { 129, 1840 }, { 132, 1220 },
  { 133,  350 }, { 136, 1690 }, { 137,  150 }, { 139, 1440 }, { 140, 1160 },
  { 141, 1740 }, { 142,  560 }, { 144,  760 }, { 145,  240 }, { 146,  480 },
  { 147, 1730 }, { 148, 1500 }, { 149, 1660 }, { 152,  310 }, { 153, 1970 },
  { 155,  840 }, { 158,  680 }, { 160,  500 }, { 161,  320 }, { 168,  760 },
  { 171, 1240 }, { 173,  310 }, { 174,  960 }, { 175, 1460 }, { 179, 1750 },
  { 181, 1710 }, { 183,  240 }, { 184, 1650 }, { 185, 1450 }, { 189,  170 },
  { 190,  330 }, { 194,  880 }, { 198,  400 }, { 199,  590 }, { 200, 1540 }
};

int
binary_search(int x)
{
  int fvalue, mid, up, low ;

  low = 0;
  up = NUMVALS - 1;
  fvalue = -1 /* all data are positive */ ;
  while (low <= up) {
    mid = (low + up) >> 1;
    if ( data[mid].key == x ) {  /*  found  */
      up = low - 1;
      fvalue = data[mid].value;
    }
    else  /* not found */
      if ( data[mid].key > x ) 	{
	up = mid - 1;
      }
      else   {
	low = mid + 1;
      }
  }
  return fvalue;
}

int res [5];		/* Result for verification */

int
verify_benchmark (int r __attribute ((unused)) )
{
  static int exp[5] = { 1440, 850, 990, 1730, 1540 };

  return 0 == memcmp (res, exp, 5 * sizeof (res[0]));
}


void
initialise_benchmark (void)
{
}



int benchmark()
{
  int  i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    {
      volatile int  v;

      v = 2;
      v = binary_search (2);
      res[0] = v;
      v = 48;
      v = binary_search (48);
      res[1] = v;
      v = 101;
      v = binary_search (101);
      res[2] = v;
      v = 147;
      v = binary_search (147);
      res[3] = v;
      v = 200;
      v = binary_search (200);
      res[4] = v;
    }

  return 0;
}
