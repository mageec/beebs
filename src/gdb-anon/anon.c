/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS GDB anon test

   Copyright (C) 1986-2013 Free Software Foundation, Inc.
   Copyright (C) 2013 Embecosm Limited and University of Bristol

   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

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

/* This program is originally part of the GDB regression testsuite (see
   gdb/testsuite/gdb.base/anon.c in the GDB sources). */

/* This test will build in one of two versions, either with the official C
   library, or with the BEEBS subsitute library, depending on the
   configuration settings. */

#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)


/* Test of anonymous union in a struct.  */

#include <string.h>

struct outer
{
  int one;
  int two;

  struct
  {
    union {
      int three : 3;
      int four : 4;
    };

    union {
      int five : 3;
      int six : 4;
    };
  } data;
};


int
benchmark (void)
{
  struct outer val;

  memset (&val, 0, sizeof (val));
  val.data.six = 6;

  return 0;			/* break here */
}


int
main (void)
{
  int i;

  initialise_board ();
  start_trigger ();

  for (i = 0; i < SCALE_FACTOR; i++)
    benchmark ();

  stop_trigger ();
  return 0;
}
