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
#define SCALE_FACTOR    (REPEAT_FACTOR >> 10)

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

#define Var(name, value)				__typeof__(value) name = value
#define Allocate(type, count)				(type *)malloc((count) * sizeof(type))

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
	Var(buffer, Allocate(Test, array_count));
	MergeSortR(array, MakeRange(0, array_count), compare, buffer);
	free(buffer);
}


long TestingPathological(long index, long total) {
	if (index == 0) return 10;
	else if (index < total/2) return 11;
	else if (index == total - 1) return 10;
	return 9;
}

long TestingRandom(long index, long total) {
	return rand();
}

long TestingMostlyDescending(long index, long total) {
	return total - index + rand() * 1.0/RAND_MAX * 5 - 2.5;
}

long TestingMostlyAscending(long index, long total) {
	return index + rand() * 1.0/RAND_MAX * 5 - 2.5;
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
	return (rand() * 1.0/RAND_MAX <= 0.9) ? index : (index - 2);
}

long TestingMostlyEqual(long index, long total) {
	return 1000 + rand() * 1.0/RAND_MAX * 4;
}


const long max_size = 100;
Test array1[100];

int benchmark() {
	long total, index, test_case;
	Comparison compare = TestCompare;

	__typeof__(&TestingPathological) test_cases[] = {
		TestingPathological,
		TestingRandom,
		TestingMostlyDescending,
		TestingMostlyAscending,
		TestingAscending,
		TestingDescending,
		TestingEqual,
		TestingJittered,
		TestingMostlyEqual
	};

	/* initialize the random-number generator */
	srand(0);
	/*srand(10141985);*/ /* in case you want the same random numbers */


	total = max_size;
	for (test_case = 0; test_case < sizeof(test_cases)/sizeof(test_cases[0]); test_case++) {

		for (index = 0; index < total; index++) {
			Test item;

			item.value = test_cases[test_case](index, total);
			item.index = index;

			array1[index] = item;
		}

		MergeSort(array1, total, compare);

	}

	return 0;
}

