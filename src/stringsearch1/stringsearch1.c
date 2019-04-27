/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS stringsearch1 benchmark

   Copyright (C) 2013 Embecosm Limited and University of Bristol

   Contributor: James Pallister <james.pallister@bristol.ac.uk>

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

#include <string.h>

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 568

#ifndef	CHARTYPE
#define	CHARTYPE	unsigned char
#endif

void prep1(CHARTYPE *base, int m);
int exec1(CHARTYPE *base, int n);
void prep2(CHARTYPE *base, int m);
int exec2(CHARTYPE *base, int n);

char buf[] = "abacacbabbabbadcabdcabccacacbadbadbcabdcabcbadcbacabadbadcabcbacdcacabacabcabcbadcbacabadbadcabcbac";
char search[] ="abc";
static int size;

int
benchmark (void)
{
  volatile int r;
  int  i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    {
	prep1((CHARTYPE *) search, size);
	r = exec1((CHARTYPE *) buf, strlen(buf));
	prep2((CHARTYPE *) search, size);
	r *= exec2((CHARTYPE *) buf, strlen(buf));
    }

  return r;
}

void initialise_benchmark() {
  size = 3;
}

int verify_benchmark(int r) {
  return 36 == r;
}
