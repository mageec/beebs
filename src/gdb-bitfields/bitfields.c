/* BEEBS GDB bitfields test

   Copyright (C) 1986-2014 Free Software Foundation, Inc.
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
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)

struct fields
{
  unsigned char	uc    ;
  signed int	s1 : 1;
  unsigned int	u1 : 1;
  signed int	s2 : 2;
  unsigned int	u2 : 2;
  signed int	s3 : 3;
  unsigned int	u3 : 3;
  signed int	s9 : 9;
  unsigned int  u9 : 9;
  signed char	sc    ;
} flags;

struct internalvartest
{
  unsigned int a : 1;
  struct
    {
      unsigned int b : 1;
      struct
	{
	  unsigned int c : 1;
	  signed int   d : 1;
	} deep;
      signed int   e : 1;
    } inner;
  signed int   f : 1;
} dummy_internalvartest;

void break1 ()
{
}

void break2 ()
{
}

void break3 ()
{
}

void break4 ()
{
}

void break5 ()
{
}

void break6 ()
{
}

void break7 ()
{
}

void break8 ()
{
}

void break9 ()
{
}

void break10 ()
{
}

struct container
{
  struct fields one;
  struct fields two;
} container;

/* this is used by bitfields.exp to determine if the target understands
   signed bitfields.  */
int i;

void
benchmark (void)
{
  /* for each member, set that member to 1, allow gdb to verify that the
     member (and only that member) is 1, and then reset it back to 0. */

  flags.uc = 1;
  break1 ();
  flags.uc = 0;

  flags.s1 = -1;
  break1 ();
  flags.s1 = 0;

  flags.u1 = 1;
  break1 ();
  flags.u1 = 0;

  flags.s2  = 1;
  break1 ();
  flags.s2 = 0;

  flags.u2 = 1;
  break1 ();
  flags.u2 = 0;

  flags.s3  = 1;
  break1 ();
  flags.s3 = 0;

  flags.u3 = 1;
  break1 ();
  flags.u3 = 0;

  flags.s9 = 1;
  break1 ();
  flags.s9 = 0;

  flags.u9 = 1;
  break1 ();
  flags.u9 = 0;

  flags.sc = 1;
  break1 ();
  flags.sc = 0;

  /* fill alternating fields with all 1's and verify that none of the bits
     "bleed over" to the other fields. */

  flags.uc = 0xff;
  flags.u1 = 0x1;
  flags.u2 = 0x3;
  flags.u3 = 0x7;
  flags.u9 = 0x1ff;
  break2 ();
  flags.uc = 0;
  flags.u1 = 0;
  flags.u2 = 0;
  flags.u3 = 0;
  flags.u9 = 0;

  flags.s1 = -1;
  flags.s2 = -1;
  flags.s3 = -1;
  flags.s9 = -1;
  flags.sc = 0xff;
  break2 ();
  flags.s1 = 0;
  flags.s2 = 0;
  flags.s3 = 0;
  flags.s9 = 0;
  flags.sc = 0;

  /* fill the unsigned fields with the maximum positive value and verify
     that the values are printed correctly. */

  /* maximum positive values */
  flags.u1 = 0x1;
  flags.u2 = 0x3;
  flags.u3 = 0x7;
  flags.u9 = 0x1ff;
  break3 ();
  flags.u1 = 0;
  flags.u2 = 0;
  flags.u3 = 0;
  flags.u9 = 0;

  /* fill the signed fields with the maximum positive value, then the maximally
     negative value, then -1, and verify in each case that the values are
     printed correctly. */

  /* maximum positive values */
  flags.s1 = 0x0;
  flags.s2 = 0x1;
  flags.s3 = 0x3;
  flags.s9 = 0xff;
  break4 ();

  /* maximally negative values */
  flags.s1 = -0x1;
  flags.s2 = -0x2;
  flags.s3 = -0x4;
  flags.s9 = -0x100;
  /* extract bitfield value so that bitfield.exp can check if the target
     understands signed bitfields.  */
  i = flags.s9;
  break4 ();

  /* -1 */
  flags.s1 = -1;
  flags.s2 = -1;
  flags.s3 = -1;
  flags.s9 = -1;
  break4 ();

  flags.s1 = 0;
  flags.s2 = 0;
  flags.s3 = 0;
  flags.s9 = 0;

  /* bitfields at a non-zero offset in a containing structure.  */
  container.one.u3 = 5;
  container.two.u3 = 3;
  break5 ();
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
