/* BEEBS mergesort benchmark

   Originally from https://github.com/BonzaiThePenguin/WikiSort
   and placed into public domain.

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

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 10

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <limits.h>

/* various #defines for the C code */
#ifndef true
	#define true 1
	#define false 0
	typedef uint8_t bool;
#endif

/* These macros are no longer used in BEEBS. alloca does a better job

#define Var(name, value)				__typeof__(value) name = value
#define Allocate(type, count)				(type *)malloc((count) * sizeof(type))

*/

long Min(const long a, const long b) {
	if (a < b) return a;
	return b;
}

long Max(const long a, const long b) {
	if (a > b) return a;
	return b;
}

/* structure to represent ranges within the array */
typedef struct {
	long start;
	long end;
} Range;

long Range_length(Range range) { return range.end - range.start; }

Range MakeRange(const long start, const long end) {
	Range range;
	range.start = start;
	range.end = end;
	return range;
}


/* structure to test stable sorting (index will contain its original index in the array, to make sure it doesn't switch places with other items) */
typedef struct {
	int value;
	int index;
} Test;


bool TestCompare(Test item1, Test item2) { return (item1.value < item2.value); }

typedef bool (*Comparison)(Test, Test);

/* find the index of the last value within the range that is equal to array[index], plus 1 */
long BinaryLast(const Test array[], const long index, const Range range, const Comparison compare) {
	long start = range.start, end = range.end - 1;
	while (start < end) {
		long mid = start + (end - start)/2;
		if (!compare(array[index], array[mid]))
			start = mid + 1;
		else
			end = mid;
	}
	if (start == range.end - 1 && !compare(array[index], array[start])) start++;
	return start;
}


/* n^2 sorting algorithm used to sort tiny chunks of the full array */
void InsertionSort(Test array[], const Range range, const Comparison compare) {
	long i;
	for (i = range.start + 1; i < range.end; i++) {
		const Test temp = array[i]; long j;
		for (j = i; j > range.start && compare(temp, array[j - 1]); j--)
			array[j] = array[j - 1];
		array[j] = temp;
	}
}

/* standard merge sort, so we have a baseline for how well the in-place merge works */
void MergeSortR(Test array[], const Range range, const Comparison compare, Test buffer[]) {
	long mid, A_count = 0, B_count = 0, insert = 0;
	Range A, B;

	if (Range_length(range) < 32) {
		InsertionSort(array, range, compare);
		return;
	}

	mid = range.start + (range.end - range.start)/2;
	A = MakeRange(range.start, mid);
	B = MakeRange(mid, range.end);

	MergeSortR(array, A, compare, buffer);
	MergeSortR(array, B, compare, buffer);

	/* standard merge operation here (only A is copied to the buffer, and only the parts that weren't already where they should be) */
	A = MakeRange(BinaryLast(array, B.start, A, compare), A.end);
	memcpy(&buffer[0], &array[A.start], Range_length(A) * sizeof(array[0]));
	while (A_count < Range_length(A) && B_count < Range_length(B)) {
		if (!compare(array[A.end + B_count], buffer[A_count])) {
			array[A.start + insert] = buffer[A_count];
			A_count++;
		} else {
			array[A.start + insert] = array[A.end + B_count];
			B_count++;
		}
		insert++;
	}

	memcpy(&array[A.start + insert], &buffer[A_count], (Range_length(A) - A_count) * sizeof(array[0]));
}

void MergeSort(Test array[], const long array_count, const Comparison compare) {
	/* The original version used malloc. For BEEBS, alloca requires less
	   library support.
	Var(buffer, Allocate(Test, array_count));
	*/
	Test *buffer = (Test *)alloca((array_count * sizeof(Test)));
	MergeSortR(array, MakeRange(0, array_count), compare, buffer);
	/* For BEEBS, no need to free with alloca
	free(buffer);
	*/
}


long TestingPathological(long index, long total) {
	if (index == 0) return 10;
	else if (index < total/2) return 11;
	else if (index == total - 1) return 10;
	return 9;
}

long TestingRandom(long index, long total) {
	return rand_beebs();
}

long TestingMostlyDescending(long index, long total) {
	return total - index + rand_beebs() * 1.0/RAND_MAX * 5 - 2.5;
}

long TestingMostlyAscending(long index, long total) {
	return index + rand_beebs() * 1.0/RAND_MAX * 5 - 2.5;
}

long TestingAscending(long index, long total) {
	return index;
}

long TestingDescending(long index, long total) {
	return total - index;
}

long TestingEqual(long index, long total) {
	return 1000;
}

long TestingJittered(long index, long total) {
	return (rand_beebs() * 1.0/RAND_MAX <= 0.9) ? index : (index - 2);
}

long TestingMostlyEqual(long index, long total) {
  return 1000L + (long) (rand_beebs() % 4);
}


const long max_size = 100;
Test array1[100];

void
initialise_benchmark (void)
{
}



int benchmark()
{
  long total, index, test_case;
  Comparison compare = TestCompare;

  __typeof__(&TestingPathological) test_cases[9] =
    {
      &TestingPathological,
      &TestingRandom,
      &TestingMostlyDescending,
      &TestingMostlyAscending,
      &TestingAscending,
      &TestingDescending,
      &TestingEqual,
      &TestingJittered,
      &TestingMostlyEqual
    };

  int  i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    {
      /* initialize the random-number generator. */
      /* The original code used srand here, we use a value that will fit in
	 a 16-bit unsigned int. */
      srand_beebs (0);
      /*srand(10141985);*/ /* in case you want the same random numbers */

      total = max_size;
      for (test_case = 0; test_case < 9; test_case++) {

	for (index = 0; index < total; index++) {
	  Test item;

	  item.value = test_cases[test_case](index, total);
	  item.index = index;

	  array1[index] = item;
	}

	MergeSort(array1, total, compare);
      }
    }

  return 0;
}

int verify_benchmark(int unused)
{
  Test exp[] = {
    { 1000,  0 }, { 1000,  8 }, { 1000, 11 }, { 1000, 16 }, { 1000, 33 },
    { 1000, 34 }, { 1000, 37 }, { 1000, 39 }, { 1000, 41 }, { 1000, 44 },
    { 1000, 51 }, { 1000, 54 }, { 1000, 56 }, { 1000, 59 }, { 1000, 70 },
    { 1000, 73 }, { 1000, 74 }, { 1000, 75 }, { 1000, 76 }, { 1000, 77 },
    { 1000, 93 }, { 1000, 97 }, { 1000, 98 }, { 1001,  1 }, { 1001,  4 },
    { 1001,  9 }, { 1001, 19 }, { 1001, 24 }, { 1001, 25 }, { 1001, 29 },
    { 1001, 30 }, { 1001, 36 }, { 1001, 38 }, { 1001, 40 }, { 1001, 42 },
    { 1001, 47 }, { 1001, 50 }, { 1001, 55 }, { 1001, 57 }, { 1001, 61 },
    { 1001, 63 }, { 1001, 65 }, { 1001, 66 }, { 1001, 68 }, { 1001, 69 },
    { 1001, 71 }, { 1001, 72 }, { 1001, 78 }, { 1001, 80 }, { 1001, 83 },
    { 1001, 84 }, { 1001, 91 }, { 1001, 92 }, { 1001, 94 }, { 1002,  2 },
    { 1002, 10 }, { 1002, 12 }, { 1002, 13 }, { 1002, 14 }, { 1002, 17 },
    { 1002, 21 }, { 1002, 26 }, { 1002, 31 }, { 1002, 35 }, { 1002, 43 },
    { 1002, 46 }, { 1002, 48 }, { 1002, 52 }, { 1002, 53 }, { 1002, 79 },
    { 1002, 81 }, { 1002, 82 }, { 1002, 88 }, { 1002, 89 }, { 1002, 90 },
    { 1002, 99 }, { 1003,  3 }, { 1003,  5 }, { 1003,  6 }, { 1003,  7 },
    { 1003, 15 }, { 1003, 18 }, { 1003, 20 }, { 1003, 22 }, { 1003, 23 },
    { 1003, 27 }, { 1003, 28 }, { 1003, 32 }, { 1003, 45 }, { 1003, 49 },
    { 1003, 58 }, { 1003, 60 }, { 1003, 62 }, { 1003, 64 }, { 1003, 67 },
    { 1003, 85 }, { 1003, 86 }, { 1003, 87 }, { 1003, 95 }, { 1003, 96}
  };

  return 0 == memcmp (array1, exp, max_size * sizeof (array1[0]));
}
