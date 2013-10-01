/*
 * benchmark program:   fir2dim.c
 *
 * benchmark suite:     DSP-kernel
 *
 * description:         fir2dim - filter benchmarking
 *
 * The image is an array IMAGEDIM * IMAGEDIM pixels. To provide
 * conditions for the FIR filtering, the image is surrounded by a
 * set of zeros such that the image is actually stored as a
 * ARRAYDIM * ARRAYDIM = (IMAGEDIM + 2) * (IMAGEDIM + 2) array
 *
 *          <--ARRAYDIM-->
 *         |0 0 0 .... 0 0| A
 *         |0 x x .... x 0| |
 *         |0 x x .... x 0| ARRAY_
 *         |0 image area 0| DIM
 *         |0 x x .... x 0| |
 *         |0 x x .... x 0| |
 *         |0 0 0 .... 0 0| V
 *
 * The image (with boundary) is stored in row major storage. The
 * first element is array(1,1) followed by array(1,2). The last
 * element of the first row is array(1,514) following by the
 * beginning of the next column array(2,1).
 *
 * The two dimensional FIR uses a 3x3 coefficient mask:
 *
 *         |c11 c12 c13|
 *         |c21 c22 c23|
 *         |c31 c32 c33|
 *
 * The output image is of dimension IMAGEDIM * IMAGEDIM.
 *
 * reference code:      target assembly
 *
 * f. verification:     simulator based
 *
 *  organization:        Aachen University of Technology - IS2
 *                       DSP Tools Group
 *                       phone:  +49(241)807887
 *                       fax:    +49(241)8888195
 *                       e-mail: zivojnov@ert.rwth-aachen.de
 *
 * author:              Juan Martinez Velarde
 *
 * history:             15-05-94 creation fixed-point (Martinez Velarde)
 *                      16-03-95 adaption floating-point (Harald L. Schraut)
 *
 *                      $Author: schraut $
 *                      $Date: 1995/04/12 06:23:50 $
 *                      $Revision: 1.3 $
 */

#include "platformcode.h"

#define STORAGE_CLASS register
#define TYPE          float
#define IMAGEDIM      4
#define ARRAYDIM      (IMAGEDIM + 2)
#define COEFFICIENTS  3

int main()
{

   static TYPE  coefficients[COEFFICIENTS*COEFFICIENTS];
   static TYPE  array[ARRAYDIM*ARRAYDIM] ={0} ;
   static TYPE  output[IMAGEDIM*IMAGEDIM] ={0};

   static TYPE  check_output[IMAGEDIM*IMAGEDIM] =
   {4, 6, 6, 4, 6, 9, 9, 6, 6, 9, 9, 6, 4, 6, 6, 4};

   STORAGE_CLASS TYPE *parray  = &array[0], *parray2, *parray3 ;
   STORAGE_CLASS TYPE *pcoeff  = &coefficients[0] ;
   STORAGE_CLASS TYPE *poutput = &output[0]       ;
   int k, f, i, n;

   /* Start in the second row and second column to surround image with zeros */
   parray += ARRAYDIM;
   parray += 1;

   /* For all but the first and last row */
   for (i = 0 ; i < IMAGEDIM ; i++)
   {
      for (f = 0 ; f < IMAGEDIM ; f++)
         *parray++ = 1;

      /* Ignore the first and last columns */
      parray += 2;
   }

   /* Sets coefficient array to all 1s */
   for (i = 0; i < COEFFICIENTS*COEFFICIENTS; i++)
      *pcoeff++ = 1;

   /* Resets all pointers to the start of their arrays */
   parray  = &array[0]        ;
   pcoeff  = &coefficients[0] ;
   poutput = &output[0]       ;

   initialise_trigger();
   start_trigger();

   for(n = 0; n < REPEAT_FACTOR>>5; ++n)
   {
      /* Resets all pointers to the start of their arrays */
      parray  = &array[0]        ;
      pcoeff  = &coefficients[0] ;
      poutput = &output[0]       ;

      /* For every pixel in the image */
      for (k = 0 ; k < IMAGEDIM ; k++)
      {

         for (f = 0 ; f < IMAGEDIM ; f++)
         {
            pcoeff = &coefficients[0] ;
            /* Current pixel */
            parray = &array[k*ARRAYDIM + f] ;
            /* Pixel below current */
            parray2 = parray + ARRAYDIM ;
            /* Two pixels below current */
            parray3 = parray + ARRAYDIM + ARRAYDIM ;

            *poutput = 0 ;

            for (i = 0 ; i < 3 ; i++)
               *poutput += *pcoeff++ * *parray++ ;

            for (i = 0 ; i < 3 ; i++)
               *poutput += *pcoeff++ * *parray2++ ;

            for (i = 0 ; i < 3 ; i++)
               *poutput += *pcoeff++ * *parray3++ ;

            poutput++ ;
         }
      }
   }

   stop_trigger();

   /* Verify that we have the correct result. */
   int to_return = 0;
   for (i = 0; i < IMAGEDIM*IMAGEDIM; i++) {
      if (output[i] != check_output[i]) {
         to_return = -1;
         break;
      }
   }

   return to_return;
}

/* vim: set ts=3 sw=3 et: */
