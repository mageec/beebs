/* BEEBS cubic benchmark

   Contributor: James Pallister <james.pallister@bristol.ac.uk>
   From http://www.snippets.org/.

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

/* +++Date last modified: 05-Jul-1997 */

/*
 **  CUBIC.C - Solve a cubic polynomial
 **  public domain by Ross Cottrell
 */

#include <math.h>
#include "snipmath.h"

void SolveCubic(double  a,
      double  b,
      double  c,
      double  d,
      int    *solutions,
      double *x)
{
  long double  a1 = (long double) (b/a);
  long double  a2 = (long double) (c/a);
  long double  a3 = (long double) (d/a);
  long double  Q = (a1*a1 - 3.0L*a2)/9.0L;
  long double  R = (2.0L*a1*a1*a1 - 9.0L*a1*a2 + 27.0L*a3)/54.0L;
  double  R2_Q3 = (double) (R*R - Q*Q*Q);

  double  theta;

   if (R2_Q3 <= 0)
   {
      *solutions = 3;
      theta = acos(((double) R)/sqrt((double) (Q*Q*Q)));
      x[0] = -2.0*sqrt((double) Q)*cos(theta/3.0) - a1/3.0;
      x[1] = -2.0*sqrt((double) Q)*cos((theta+2.0*PI)/3.0) - a1/3.0;
      x[2] = -2.0*sqrt((double) Q)*cos((theta+4.0*PI)/3.0) - a1/3.0;
   }
   else
   {
      *solutions = 1;
      x[0] = pow(sqrt(R2_Q3)+fabs((double) R), 1/3.0);
      x[0] += ((double) Q)/x[0];
      x[0] *= (R < 0.0L) ? 1 : -1;
      x[0] -= (double) (a1/3.0L);
   }
}

/* vim: set ts=3 sw=3 et: */
