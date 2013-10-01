/* +++Date last modified: 05-Jul-1997 */

/*
 **  SNIPMATH.H - Header file for SNIPPETS math functions and macros
 */

#ifndef SNIPMATH__H
#define SNIPMATH__H

#include <math.h>

#include "pi.h"
#include "sniptype.h"

/*
 **  Callable library functions begin here
 */

void    SolveCubic(double a, double b, double c,      /* Cubic.C        */
      double d, int *solutions,
      double *x);


/*
 **  File: ISQRT.C
 */

struct int_sqrt {
   unsigned sqrt,
            frac;
};

#endif /* SNIPMATH__H */

/* vim: set ts=3 sw=3 et: */
