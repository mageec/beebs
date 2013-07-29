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
#define UPPSALAWCET 1
#include <stdio.h>
#include <math.h>


/* ***UPPSALA WCET***:
   disable stupid UNIX includes */
#ifndef UPPSALAWCET
#include <sys/types.h>
#include <sys/times.h>
#endif

#include "platformcode.h"

/*
 * MATRIX MULTIPLICATION BENCHMARK PROGRAM:
 * This program multiplies 2 square matrices resulting in a 3rd
 * matrix. It tests a compiler's speed in handling multidimensional
 * arrays and simple arithmetic.
 */

#define UPPERLIMIT 20

typedef float matrix [UPPERLIMIT][UPPERLIMIT];

int Seed;
matrix ArrayA, ArrayB, ResultArray;

#ifdef UPPSALAWCET
/* Our picky compiler wants prototypes! */
void Multiply(matrix A, matrix B, matrix Res);
void InitSeed(void);
void Test(matrix A, matrix B, matrix Res);
void Initialize(matrix Array);
int RandomInteger(void);
#endif

int main()
{
   matrix check_ResultArray = {
      {338228864.0, 351809504.0, 406134400.0, 405078624.0, 326640512.0, 382530400.0, 367293024.0, 434923680.0, 429558656.0, 419243200.0, 442779392.0, 334610304.0, 303185184.0, 376032640.0, 440197216.0, 325681120.0, 504583392.0, 429266304.0, 439802176.0, 454102560.0},
      {235690400.0, 239545520.0, 257456064.0, 284505856.0, 291552960.0, 328769248.0, 323926304.0, 319587424.0, 299160256.0, 363729856.0, 265594160.0, 269927104.0, 267293552.0, 307936288.0, 318103232.0, 229118320.0, 396854240.0, 315739424.0, 346131680.0, 338399392.0},
      {209418000.0, 301414688.0, 303627648.0, 339308576.0, 264949440.0, 311024544.0, 295407072.0, 347252320.0, 354269440.0, 314005344.0, 292122944.0, 285267008.0, 301887680.0, 274734592.0, 298557472.0, 291661888.0, 419965056.0, 404483648.0, 347423744.0, 310703616.0},
      {241221136.0, 237103760.0, 247622928.0, 303982528.0, 271301504.0, 212602096.0, 234555248.0, 297744448.0, 310293824.0, 300394272.0, 260051616.0, 204314816.0, 276278528.0, 255892800.0, 288758592.0, 235792880.0, 344525824.0, 284312800.0, 324299936.0, 322093504.0},
      {380393472.0, 402862720.0, 398855744.0, 432482304.0, 407153920.0, 422952960.0, 422011776.0, 451230048.0, 498448960.0, 524219296.0, 417759840.0, 365195680.0, 412121952.0, 418871264.0, 441428192.0, 353423456.0, 564810560.0, 492879840.0, 508095648.0, 468476800.0},
      {306356640.0, 275397472.0, 304515232.0, 380727552.0, 310797536.0, 331773984.0, 333854752.0, 351344576.0, 339202624.0, 370581888.0, 300855936.0, 291192128.0, 302031008.0, 313214848.0, 393273568.0, 293677696.0, 467995200.0, 379024192.0, 369055072.0, 385174816.0},
      {320039616.0, 371940256.0, 322921536.0, 351020512.0, 301635296.0, 312844416.0, 285573056.0, 372698848.0, 382342016.0, 341491424.0, 359856448.0, 320798848.0, 322408128.0, 321764992.0, 310576640.0, 306506944.0, 426337248.0, 416998176.0, 407549792.0, 375390592.0},
      {296657408.0, 267583728.0, 356839712.0, 401481344.0, 350176352.0, 388862816.0, 405148416.0, 396591584.0, 455017312.0, 436997536.0, 347163104.0, 315107520.0, 305233120.0, 351858784.0, 447740960.0, 285759200.0, 482630400.0, 426083936.0, 392042016.0, 357011552.0},
      {317182080.0, 366952672.0, 376450048.0, 414122496.0, 355719616.0, 395190592.0, 380960672.0, 416462048.0, 490839136.0, 472137216.0, 408669696.0, 349862720.0, 341421632.0, 389739488.0, 394826080.0, 313607520.0, 511374496.0, 448322304.0, 453728064.0, 431061216.0},
      {314489184.0, 343884736.0, 401635456.0, 434315744.0, 357320800.0, 351456352.0, 320978912.0, 424773920.0, 448931712.0, 443452256.0, 382842752.0, 347885472.0, 356310176.0, 372470656.0, 425501472.0, 335619776.0, 512949696.0, 462584320.0, 408835008.0, 448189472.0},
      {297267072.0, 286152448.0, 355979648.0, 354568960.0, 285071328.0, 343840256.0, 288873312.0, 368091264.0, 431579040.0, 394129472.0, 385646592.0, 313014208.0, 261389344.0, 347592064.0, 357971648.0, 240070704.0, 427740544.0, 375422656.0, 362758528.0, 360431936.0},
      {247602384.0, 217976320.0, 251160688.0, 320447488.0, 234119168.0, 184044256.0, 207169536.0, 258196464.0, 332759680.0, 315295744.0, 275586752.0, 254179904.0, 239589664.0, 275478656.0, 288856320.0, 207579536.0, 343243296.0, 314564704.0, 267752832.0, 269607040.0},
      {318441152.0, 292598176.0, 384638816.0, 366877440.0, 335055072.0, 344652832.0, 301116800.0, 349933120.0, 371803776.0, 377469504.0, 287298208.0, 319400960.0, 318871232.0, 387736736.0, 378493760.0, 305144832.0, 442503712.0, 394965664.0, 336140544.0, 339646624.0},
      {223477040.0, 287384736.0, 305720960.0, 329440736.0, 286403744.0, 327774720.0, 320763904.0, 385200576.0, 331870464.0, 318018368.0, 297673856.0, 286112224.0, 274361408.0, 330746560.0, 319264640.0, 274652544.0, 423202880.0, 346326464.0, 388155200.0, 361965696.0},
      {263418384.0, 312509216.0, 359458336.0, 376478912.0, 290812960.0, 336480384.0, 300077760.0, 366194560.0, 369185120.0, 330793152.0, 329250080.0, 332988864.0, 314111360.0, 353212096.0, 354595456.0, 336455616.0, 483723232.0, 413720000.0, 377714368.0, 390015584.0},
      {271535200.0, 281752672.0, 339957344.0, 338057984.0, 320721088.0, 309228672.0, 311153856.0, 357369536.0, 361154816.0, 337181472.0, 305217280.0, 293529888.0, 247651440.0, 337274336.0, 383092032.0, 285394112.0, 406510880.0, 345289568.0, 372997888.0, 328418400.0},
      {302179744.0, 251463856.0, 295309056.0, 338014464.0, 243714416.0, 278676704.0, 289756768.0, 315516832.0, 376509216.0, 373314240.0, 354389312.0, 271496320.0, 281549312.0, 313725472.0, 335546368.0, 210446304.0, 430774464.0, 363783264.0, 321236960.0, 324650400.0},
      {308271264.0, 336757952.0, 382056224.0, 387914848.0, 375392544.0, 389635744.0, 383812384.0, 409197472.0, 456247296.0, 465891200.0, 376914464.0, 333492992.0, 368864544.0, 395671808.0, 403942528.0, 331225088.0, 514682784.0, 456907328.0, 432237280.0, 386072832.0},
      {263935088.0, 247257664.0, 275383680.0, 323392832.0, 267874928.0, 287308192.0, 246942544.0, 302991904.0, 310759776.0, 324827104.0, 295684480.0, 262772128.0, 271949504.0, 264651024.0, 316061024.0, 264473440.0, 396742880.0, 341885920.0, 319737888.0, 340814112.0},
      {291751744.0, 288431104.0, 336920640.0, 343657344.0, 311712032.0, 290429600.0, 254877712.0, 338982144.0, 349631424.0, 324975776.0, 312346304.0, 313073856.0, 288976352.0, 303386976.0, 324643456.0, 313777184.0, 365793632.0, 377537280.0, 356692864.0, 377541184.0}
   };

   int n;
   InitSeed();
   /* ***UPPSALA WCET***:
      no printing please! */
#ifndef UPPSALAWCET
   printf("\n   *** MATRIX MULTIPLICATION BENCHMARK TEST ***\n\n");
   printf("RESULTS OF THE TEST:\n");
#endif

   initialise_trigger();
   start_trigger();

   for(n = 0; n < REPEAT_FACTOR>>7; ++n)
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


void InitSeed(void)
   /*
    * Initializes the seed used in the random number generator.
    */
{
   /* ***UPPSALA WCET***:
      changed Thomas Ls code to something simpler.
      Seed = KNOWN_VALUE - 1; */
   Seed = 0;
}


void Test(matrix A, matrix B, matrix Res)
   /*
    * Runs a multiplication test on an array.  Calculates and prints the
    * time it takes to multiply the matrices.
    */
{
#ifndef UPPSALAWCET
   long StartTime, StopTime;
   float TotalTime;
#endif
   int OuterIndex, InnerIndex;

   for (OuterIndex = 0; OuterIndex < UPPERLIMIT; OuterIndex++)
      for (InnerIndex = 0; InnerIndex < UPPERLIMIT; InnerIndex++)
         A[OuterIndex][InnerIndex] = (float)RandomInteger();
   for (OuterIndex = 0; OuterIndex < UPPERLIMIT; OuterIndex++)
      for (InnerIndex = 0; InnerIndex < UPPERLIMIT; InnerIndex++)
         B[OuterIndex][InnerIndex] = (float)RandomInteger();
   //   Initialize(A);
   // Initialize(B);

   /* ***UPPSALA WCET***: don't print or time */
#ifndef UPPSALAWCET
   StartTime = ttime ();
#endif

   Multiply(A, B, Res);

   /* ***UPPSALA WCET***: don't print or time */
#ifndef UPPSALAWCET
   StopTime = ttime();
   TotalTime = (StopTime - StartTime) / 1000.0;
   printf("    - Size of array is %d\n", UPPERLIMIT);
   printf("    - Total multiplication time is %3.3f seconds\n\n", TotalTime);
#endif
}


//void Initialize(matrix Array)
/*
 * Intializes the given array with random integers.
 */
//{
//   int OuterIndex, InnerIndex;
//
//   for (OuterIndex = 0; OuterIndex < UPPERLIMIT; OuterIndex++)
//      for (InnerIndex = 0; InnerIndex < UPPERLIMIT; InnerIndex++)
//         Array[OuterIndex][InnerIndex] = (float)RandomInteger();
//}


int RandomInteger(void)
   /*
    * Generates random integers between 0 and 8095
    */
{
   Seed = ((Seed * 133) + 81) % 8095;
   return (Seed);
}


#ifndef UPPSALAWCET
int ttime()
   /*
    * This function returns in milliseconds the amount of compiler time
    * used prior to it being called.
    */
{
   struct tms buffer;
   int utime;

   /*   times(&buffer);   times not implemented */
   utime = (buffer.tms_utime / 60.0) * 1000.0;
   return (utime);
}
#endif

void Multiply(matrix A, matrix B, matrix Res)
   /*
    * Multiplies arrays A and B and stores the result in ResultArray.
    */
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
