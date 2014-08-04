/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS GDB async test

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
   gdb/testsuite/gdb.base/async.c in the GDB sources). */

#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)

int baz (void);

int
foo (void)
{
 int x, y;

 x = 5;
 y = 3;

 return x + y;
}

int
benchmark (void)
{
 int y, z;
 
 y = 2;
 z = 9;
 y = foo ();
 z = y;
 y = y + 2;
 y = baz ();

 (void) z;
 return 0;
}

int
baz (void)
{ 
  return 5;
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
