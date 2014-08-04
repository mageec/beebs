/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS GDB advance test

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
   gdb/testsuite/gdb.base/all-types.c in the GDB sources). */

#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)


/*
 *	the basic C types.
 */

#if !defined (__STDC__) && !defined (_AIX)
#define signed  /**/
#endif

char		v_char;
signed char	v_signed_char;
unsigned char	v_unsigned_char;

short		v_short;
signed short	v_signed_short;
unsigned short	v_unsigned_short;

int		v_int;
signed int	v_signed_int;
unsigned int	v_unsigned_int;

long		v_long;
signed long	v_signed_long;
unsigned long	v_unsigned_long;

float		v_float;
double		v_double;


int
benchmark (void)
{
    extern void dummy();
    dummy();
    return 0;
}

void
dummy (void)
{
  /* Some linkers (e.g. on AIX) remove unreferenced variables,
     so make sure to reference them. */
  v_char = 'A';
  v_signed_char = 'B';
  v_unsigned_char = 'C';

  v_short = 3;
  v_signed_short = 4;
  v_unsigned_short = 5;    

  v_int = 6;
  v_signed_int = 7;
  v_unsigned_int = 8;    

  v_long = 9;
  v_signed_long = 10;
  v_unsigned_long = 11;    
  
  v_float = 100.343434;
  v_double = 200.565656;
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
