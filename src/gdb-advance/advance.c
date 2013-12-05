/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS GDB advance test

   Copyright (C) 1986-2013 Free Software Foundation, Inc.
   Copyright (C) 2013 Embecosm Limited and University of Bristol

   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

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

/* This program is originally part of the GDB regression testsuite (see
   gdb/testsuite/gdb.base/advance.c in the GDB sources). */

#include "platformcode.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)


static int x;


int foo (int a)
{
  int b = a + 10;
  return b;
}


int bar (int y)
{
  int z = y + 20;
  return z;
}


void func()
{
  x = x + 5;
  func2 ();
}
int func2 ()
{
  x = 6;
}


int func3 ()
{
  x = 4;
}


void marker1 ()
{
}


void
benchmark ()
{
  int result;
  int b, c;
  c = 5;
  b = 3;    /* advance this location */
    
  func (c); /* stop here after leaving current frame */
  marker1 (); /* stop here after leaving current frame */
  func3 (); /* break here */
  result = bar (b + foo (c));
  return 0; /* advance malformed */
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
