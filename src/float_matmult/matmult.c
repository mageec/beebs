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

#include "platformcode.h"

/*
 * MATRIX MULTIPLICATION BENCHMARK PROGRAM:
 * This program multiplies 2 square matrices resulting in a 3rd
 * matrix. It tests a compiler's speed in handling multidimensional
 * arrays and simple arithmetic.
 */

#define UPPERLIMIT 10

typedef float matrix [UPPERLIMIT][UPPERLIMIT];

int Seed;
matrix ArrayA, ArrayB, ResultArray;

void Multiply(matrix A, matrix B, matrix Res);
void InitSeed(void);
void Test(matrix A, matrix B, matrix Res);
void Initialize(matrix Array);
int RandomInteger(void);

int main()
{
   const matrix check_ResultArray = {
      {931.049988, 562.409973, 676.890015, 648.630005, 837.449951, 728.460022, 936.089905, 582.47998,  668.700012, 477.360016},
      {1296,       792.98999,  1174.41003, 411.120026, 1174.04993, 952.289978, 1285.56006, 1148.66992, 828,        751.139954},
      {903.150024, 596.609985, 937.890015, 665.279968, 1135.79993, 778.410034, 805.589966, 587.880005, 1077.29993, 540.809998},
      {552.599976, 630.539978, 1013.30994, 353.069977, 707.399963, 762.839966, 1052.45996, 924.119995, 822.599976, 631.439941},
      {1144.79993, 612.809998, 1148.48999, 759.329956, 913.949951, 808.110046, 1052.18994, 765.179993, 949.950073, 860.76001},
      {1147.04993, 698.940002, 885.059998, 386.370026, 1304.09998, 862.73999,  791.460083, 934.919983, 989.550049, 758.339966},
      {904.950012, 731.609924, 1078.73999, 819.179993, 1036.34998, 796.409973, 1067.94006, 453.780029, 809.099976, 644.309937},
      {850.049927, 784.890015, 1069.10999, 689.219971, 959.850037, 937.439941, 1162.26013, 1060.0199,  1216.79993, 916.290039},
      {931.049988, 562.409973, 676.890015, 648.630005, 837.449951, 728.460022, 936.089905, 582.47998,  668.700012, 477.360016},
      {1296,       792.98999,  1174.41003, 411.120026, 1174.04993, 952.289978, 1285.56006, 1148.66992, 828,        751.139954}
   };

   int n;
   InitSeed();

   initialise_trigger();
   start_trigger();

   for(n = 0; n < REPEAT_FACTOR>>5; ++n)
      Test(ArrayA, ArrayB, ResultArray);

   stop_trigger();

   int to_return = 0, exp;
   float diff;
   for (int i = 0; i < UPPERLIMIT; i++) {
      for (int j = 0; j < UPPERLIMIT; j++) {
         if (ResultArray[i][j] != check_ResultArray[i][j]) {
            /* Ignore the least significant bit of the mantissa
             * to account for any loss of precision due to floating point
             * operations */
            frexpf(ResultArray[i][j], &exp);
            diff = fabsf(ResultArray[i][j] - check_ResultArray[i][j]);
            /* TODO: Fix for big endian */
            if (diff > (1 << exp)) {
               to_return = -1;
               break;
            }
         }
      }
   }

   return to_return;
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
   int OuterIndex, InnerIndex;

   for (OuterIndex = 0; OuterIndex < UPPERLIMIT; OuterIndex++)
      for (InnerIndex = 0; InnerIndex < UPPERLIMIT; InnerIndex++)
         A[OuterIndex][InnerIndex] = (float)RandomInteger()/10.;
   for (OuterIndex = 0; OuterIndex < UPPERLIMIT; OuterIndex++)
      for (InnerIndex = 0; InnerIndex < UPPERLIMIT; InnerIndex++)
         B[OuterIndex][InnerIndex] = (float)RandomInteger()/10.;

   Multiply(A, B, Res);
}

/*
 * Generates random integers between 0 and 8095
 */
int RandomInteger(void)
{
   Seed = ((Seed * 133) + 81) % 255;
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
         Res [Outer][Inner] = 0.0;
         for (Index = 0; Index < UPPERLIMIT; Index++) {
            Res[Outer][Inner]  += A[Outer][Index] * B[Index][Inner];
         }
      }
}

/* vim: set ts=3 sw=3 et: */
