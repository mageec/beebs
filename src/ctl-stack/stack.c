/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS stack benchmark

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

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)

#include "stack.h"

typedef struct {
  int a, b;
} pair;

MAKE_STACK(int)
MAKE_STACK(pair)


int
benchmark (void)
{
  ctl_intStack *v;
  ctl_pairStack *v2;
  int cnt=0, i;

  v = ctl_intStackInit();

  for (i = 1; i <= 100; ++i)
    ctl_intStackPush(v, i*11);

  while(v->size > 0)
  {
    int k;

    ctl_intStackPop(v, &k);

    cnt += k;
  }

  ctl_intStackFree(v);

  v2 = ctl_pairStackInit();

  for (i = 1; i <= 100; ++i)
  {
    pair p = {i, i*i};
    ctl_pairStackPush(v2, p);
  }

  while(v2->size > 0)
  {
    pair k;

    ctl_pairStackPop(v2, &k);

    cnt += k.a*k.b;
  }

  ctl_pairStackFree(v2);

  return cnt;
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
