/* BEEBS dllist benchmark

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
#include <stdlib.h>

#include "sglib.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 225

typedef struct dllist {
    int i;
    struct dllist *ptr_to_next;
    struct dllist *ptr_to_previous;
} dllist;

#define DLLIST_COMPARATOR(e1, e2) (e1->i - e2->i)

SGLIB_DEFINE_DL_LIST_PROTOTYPES(dllist, DLLIST_COMPARATOR, ptr_to_previous, ptr_to_next);
SGLIB_DEFINE_DL_LIST_FUNCTIONS(dllist, DLLIST_COMPARATOR, ptr_to_previous, ptr_to_next);

int array[100] = {14, 66, 12, 41, 86, 69, 19, 77, 68, 38, 26, 42, 37, 23, 17, 29, 55, 13,
  90, 92, 76, 99, 10, 54, 57, 83, 40, 44, 75, 33, 24, 28, 80, 18, 78, 32, 93, 89, 52, 11,
  21, 96, 50, 15, 48, 63, 87, 20, 8, 85, 43, 16, 94, 88, 53, 84, 74, 91, 67, 36, 95, 61,
  64, 5, 30, 82, 72, 46, 59, 9, 7, 3, 39, 31, 4, 73, 70, 60, 58, 81, 56, 51, 45, 1, 6, 49,
  27, 47, 34, 35, 62, 97, 2, 79, 98, 25, 22, 65, 71, 0};


/* BEEBS heap is just an array */

#define HEAP_SIZE 8192
static char heap[HEAP_SIZE];

dllist *the_list;

int
verify_benchmark (int res)
{
  dllist *l;
  int i = 0;

  for(l=sglib_dllist_get_first(the_list); l!=NULL; l=l->ptr_to_next)
  {
    if (l->i != i)
      return 0;
    i++;
  }

  return (100 == res) && check_heap_beebs ((void *) heap);
}


void
initialise_benchmark (void)
{
}



int benchmark()
{
  volatile int cnt;
  int  i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    {
      dllist *l;
      int i;

      init_heap_beebs ((void *) heap, HEAP_SIZE);
      the_list = NULL;

      for(i = 0 ;i<100; ++i)
	{
	  l = malloc_beebs(sizeof(dllist));
	  l->i = array[i];
	  sglib_dllist_add(&the_list, l);
	}

      sglib_dllist_sort(&the_list);

      cnt = 0;

      for(l=sglib_dllist_get_first(the_list); l!=NULL; l=l->ptr_to_next)
	cnt++;
    }

  return cnt;
}
