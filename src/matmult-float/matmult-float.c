/* BEEBS matmult benchmark

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

/* Original code from: WCET Benchmarks,
       http://www.mrtc.mdh.se/projects/wcet/benchmarks.html
   Permission to license under GPL obtained by email from Björn Lisper
 */

/* $Id: matmult.c,v 1.2 2005/04/04 11:34:58 csg Exp $ */

/* matmult.c */
/* was mm.c! */


/*----------------------------------------------------------------------*
 * To make this program compile under our assumed embedded environment,
 * we had to make several changes:
 * - Declare all functions in ANSI style, not K&R.
 *   this includes adding return types in all cases!
 * - Declare function prototypes
 * - Disable all output
 * - Disable all UNIX-style includes
 *
 * This is a program that was developed from mm.c to matmult.c by
 * Thomas Lundqvist at Chalmers.
 *----------------------------------------------------------------------*/

#include <math.h>
#include <string.h>
#include "support.h"
/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */

#define LOCAL_SCALE_FACTOR 20
#define UPPERLIMIT 10
typedef float matrix [UPPERLIMIT][UPPERLIMIT];
#define RANDOM_VALUE ((float) RandomInteger () / 10.0)
#define ZERO 0.0
#define MOD_SIZE 255

int
values_match (float v1, float v2)
{
  if (v1 != v2)
    {
      int exp;
      float diff;

      /* Ignore the least significant bit of the mantissa
       * to account for any loss of precision due to floating point
       * operations */
      frexpf(v1, &exp);
      diff = fabsf(v1 - v2);
      /* TODO: Fix for big endian */
      if (diff > (1 << exp)) {
	return 0;
      }
    }

  return 1;
}


/*
 * MATRIX MULTIPLICATION BENCHMARK PROGRAM:
 * This program multiplies 2 square matrices resulting in a 3rd
 * matrix. It tests a compiler's speed in handling multidimensional
 * arrays and simple arithmetic.
 */




int Seed;
matrix ArrayA_ref, ArrayA, ArrayB_ref, ArrayB, ResultArray;

void Multiply(matrix A, matrix B, matrix Res);
void InitSeed(void);
void Test(matrix A, matrix B, matrix Res);
void Initialize(matrix Array);
int RandomInteger(void);

int benchmark()
{
  int  i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    {
      memcpy (ArrayA, ArrayA_ref,
	      UPPERLIMIT * UPPERLIMIT * sizeof (ArrayA[0][0]));
      memcpy (ArrayB, ArrayB_ref,
	      UPPERLIMIT * UPPERLIMIT * sizeof (ArrayA[0][0]));

      Test(ArrayA, ArrayB, ResultArray);
    }

  return 0;
}


/*
 * Initializes the seed used in the random number generator.
 */
void InitSeed(void)
{
   Seed = 0;
}

/*
 * Runs a multiplication test on an array.  Calculates and prints the
 * time it takes to multiply the matrices.
 */
void Test(matrix A, matrix B, matrix Res)
{
   Multiply(A, B, Res);
}

/*
 * Generates random integers between 0 and 8095
 */
int RandomInteger(void)
{
   Seed = ((Seed * 133) + 81) % MOD_SIZE;
   return (Seed);
}

/*
 * Multiplies arrays A and B and stores the result in ResultArray.
 */
void Multiply(matrix A, matrix B, matrix Res)
{
   register int Outer, Inner, Index;

   for (Outer = 0; Outer < UPPERLIMIT; Outer++)
      for (Inner = 0; Inner < UPPERLIMIT; Inner++)
      {
         Res [Outer][Inner] = ZERO;
         for (Index = 0; Index < UPPERLIMIT; Index++)
            Res[Outer][Inner] += A[Outer][Index] * B[Index][Inner];
      }
}

void initialise_benchmark() {
   InitSeed();
   int OuterIndex, InnerIndex;

   for (OuterIndex = 0; OuterIndex < UPPERLIMIT; OuterIndex++)
      for (InnerIndex = 0; InnerIndex < UPPERLIMIT; InnerIndex++)
         ArrayA_ref[OuterIndex][InnerIndex] = RANDOM_VALUE;
   for (OuterIndex = 0; OuterIndex < UPPERLIMIT; OuterIndex++)
      for (InnerIndex = 0; InnerIndex < UPPERLIMIT; InnerIndex++)
         ArrayB_ref[OuterIndex][InnerIndex] = RANDOM_VALUE;
}

int verify_benchmark(int unused)
{
  int i, j;
  matrix exp = {
    {  949.950073,  860.760010, 1184.940186,  971.279968, 1180.799927,
       887.309937, 1281.239990,  613.529968, 1144.799927,  612.809998,
    },
    {  989.550049,  758.339966, 1288.259888,  760.320007,  832.500000,
       739.890015, 1381.860107,  969.119995, 1147.049927,  698.940002,
    },
    {  809.099976,  644.309937, 1241.190063,  959.130005,  677.700012,
       763.109924, 1251.989990,  551.880005,  904.950012,  731.609924,
    },
    { 1216.799927,  916.290039, 1371.059937,  563.669983, 1106.999878,
       603.090027, 1277.910034,  835.469971,  850.049927,  784.890015,
    },
    {  668.700012,  477.360016, 1100.339966,  732.330017,  762.299988,
       647.910034,  841.139893,  408.329987,  931.049988,  562.409973,
    },
    {  828.000000,  751.139954, 1537.109985,  715.320007,  949.950012,
      1004.940063, 1425.960083, 1079.369873, 1296.000000,  792.989990,
    },
    { 1077.299927,  540.809998,  852.840027,  667.979980,  844.649963,
       733.859924,  985.139954,  775.979980,  903.150024,  596.609985,
    },
    {  822.599976,  631.439941, 1133.010010,  238.769989,  667.799988,
       567.989990, 1093.859985,  884.070007,  552.599976,  630.539978,
    },
    {  949.950073,  860.760010, 1184.940186,  971.279968, 1180.799927,
       887.309937, 1281.239990,  613.529968, 1144.799927,  612.809998,
    },
    {  989.550049,  758.339966, 1288.259888,  760.320007,  832.500000,
       739.890015, 1381.860107,  969.119995, 1147.049927,  698.940002
    } };

  return 0 == memcmp (ResultArray, exp,
		      UPPERLIMIT * UPPERLIMIT * sizeof (exp[0][0]));
}

/* vim: set ts=3 sw=3 et: */
