/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS vector benchmark

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
#define LOCAL_SCALE_FACTOR 446

typedef struct {
  int a, b;
} pair;

/* BEEBS heap is just an array */

#define HEAP_SIZE 8192
static char heap[HEAP_SIZE];

#include "stack.h"

/* Create stack functions for different types.  */
MAKE_STACK(int)
MAKE_STACK(pair)

/* Container types.  */
typedef ctl_intStack int_container;
typedef ctl_pairStack pair_container;

#define CTL_INIT(type) ctl_ ## type ## StackInit ()
#define CTL_PUSH(type, stk, val) ctl_ ## type ## StackPush (stk, val)
#define CTL_POP(type, stk, res) ctl_ ## type ## StackPop (stk, res)
#define CTL_FREE(type, stk) ctl_ ## type ## StackFree (stk)

/* There's no DELETE for stacks.  */
#define CTL_DELETE(type, vec, a, b) do { } while (0)


static int init;
static int lim;
static int fact;
static int begin;
static int end;
static int end2;

int
benchmark (void)
{
  int  j;
  long int  cnt;

  for (j = 0; j < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); j++)
    {
	int_container *v;
	pair_container *v2;
	int i;

	cnt=0;
	init = 1;
	lim = 100;
	fact = 11;
	begin = 4;
	end = 50;
	end2 = 8;
	init_heap_beebs ((void *) heap, HEAP_SIZE);

	v = CTL_INIT (int);

	for (i = init; i <= lim; ++i)
	    CTL_PUSH (int, v, i * fact);

	CTL_DELETE (int, v, begin, end);

	while(v->size > 0)
	    {
		int k;

		CTL_POP (int, v, &k);

		cnt += k;
	    }

	CTL_FREE (int, v);

	v2 = CTL_INIT (pair);

	for (i = init; i <= lim; ++i)
	    {
		pair p = {i, i*i};
		CTL_PUSH (pair, v2, p);
	    }

	CTL_DELETE (pair, v2, begin, end2);

	while(v2->size > 0)
	    {
		pair k;

		CTL_POP (pair, v2, &k);

		cnt += k.a*k.b;
	    }

	CTL_FREE (pair, v2);
    }

  return (int) (cnt % 32768L);
}

void initialise_benchmark() {
}

int verify_benchmark(int r)
{
  return (31778 == r) && check_heap_beebs ((void *) heap);
}
