/* BEEBS listinsertsort1 benchmark

   Copyright (C) 2014 Embecosm Limited and University of Bristol

   Contributor James Pallister <james.pallister@bristol.ac.uk>

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
#include <stdio.h>
#include <string.h>
#include "sglib.h"
#include <stdlib.h>

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)


int array[100] = {14, 66, 12, 41, 86, 69, 19, 77, 68, 38, 26, 42, 37, 23, 17, 29, 55, 13,
  90, 92, 76, 99, 10, 54, 57, 83, 40, 44, 75, 33, 24, 28, 80, 18, 78, 32, 93, 89, 52, 11,
  21, 96, 50, 15, 48, 63, 87, 20, 8, 85, 43, 16, 94, 88, 53, 84, 74, 91, 67, 36, 95, 61,
  64, 5, 30, 82, 72, 46, 59, 9, 7, 3, 39, 31, 4, 73, 70, 60, 58, 81, 56, 51, 45, 1, 6, 49,
  27, 47, 34, 35, 62, 97, 2, 79, 98, 25, 22, 65, 71, 0};

typedef struct ilist {
    int i;
    struct ilist *next_ptr;
} iListType;

#define ILIST_COMPARATOR(e1, e2) (e1->i - e2->i)

SGLIB_DEFINE_SORTED_LIST_PROTOTYPES(iListType, ILIST_COMPARATOR, next_ptr)
SGLIB_DEFINE_SORTED_LIST_FUNCTIONS(iListType, ILIST_COMPARATOR, next_ptr)

int benchmark()
{
  int i;
  struct ilist *l, *the_list;
  struct sglib_iListType_iterator   it;
  int cnt = 0;

  the_list = NULL;
  for (i = 1; i < 100; i++) {
    l = malloc (sizeof (struct ilist));
    l->i = array [i];

    /* Insert the new element into the list while keeping it sorted.  */
    sglib_iListType_add (&the_list, l);
  }

  for (l = sglib_iListType_it_init (&it, the_list); l != NULL; l = sglib_iListType_it_next (&it)) {
    cnt += l->i;
  }

  for(l = sglib_iListType_it_init (&it, the_list); l != NULL; l = sglib_iListType_it_next (&it)) {
    free (l);
  }

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
