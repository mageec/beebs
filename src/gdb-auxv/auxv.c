/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS GDB auxv test

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
   gdb/testsuite/gdb.base/auxv.c in the GDB sources). */

#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)


#ifndef HAVE_ABORT
#define HAVE_ABORT 1
#endif

#if HAVE_ABORT
#include <stdlib.h>
#define ABORT abort()
#else
#define ABORT {char *invalid = 0; *invalid = 0xFF;}
#endif

/* Don't make these automatic vars or we will have to walk back up the
   stack to access them. */
char *buf1;
char *buf2;

int coremaker_data = 1;	/* In Data section */
int coremaker_bss;	/* In BSS section */

const int coremaker_ro = 201;	/* In Read-Only Data section */

volatile int y;

void
func2 (int x)
{
  int coremaker_local[5];
  int i;

  /* Make sure that coremaker_local doesn't get optimized away. */
  for (i = 0; i < 5; i++)
    coremaker_local[i] = i;
  coremaker_bss = 0;
  for (i = 0; i < 5; i++)
    coremaker_bss += coremaker_local[i];
  coremaker_data = coremaker_ro + 1;
  y = 10 * x;
}


void
func1 (int x)
{
  func2 (x * 2);
}


void
benchmark ()
{
  func1 (10);
}


int
main (void)
{
  int i;

  start_trigger ();

  for (i = 0; i < SCALE_FACTOR; i++)
    benchmark ();

  stop_trigger ();
  return 0;
}
