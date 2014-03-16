/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS string benchmark

   Copyright (C) 2013 Embecosm Limited and University of Bristol

   Contributor: James Pallister <james.pallister@bristol.ac.uk>

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

#include "platformcode.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)

#include "string.h"

int cnt;
benchmark (void)
{
  ctl_string *s;
  ctl_string *s2;
  int cnt;

  s = ctl_StringInit();
  s2 = ctl_StringInit();

  ctl_StringSet(s, "This is a string");
  ctl_StringAppend(s, "This is a string2");
  ctl_StringSet(s2, "aaa");
  ctl_StringSetString(s, s2);

  while(ctl_StringCmpNoCase(s, "AaaAaAaaaaaAAaaaAAaaAaA"))
  {
    ctl_StringAppend(s, "a");
    cnt++;
  }

  ctl_StringFree(s);
  ctl_StringFree(s2);
  return cnt;
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
