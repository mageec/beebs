/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS stringsearch1 benchmark

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

void prep1(unsigned char *base, int m);
void exec1(unsigned char *base, int n);
void prep2(unsigned char *base, int m);
void exec2(unsigned char *base, int n);

unsigned char *buf="abacacbabbabbadcabdcabccacacbadbadbcabdcabcbadcbacabadbadcabcbacdcacabacabcabcbadcbacabadbadcabcbac";
unsigned char *search="abc";

void
benchmark (void)
{
  prep1(search, 3);
  exec1(buf, strlen(buf));
  prep2(search, 3);
  exec2(buf, strlen(buf));
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
