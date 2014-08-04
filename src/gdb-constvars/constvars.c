/* BEEBS GDB constvars benchmark

   Copyright (C) 1986-2014 Free Software Foundation, Inc.
   Copyright (C) 2014 Embecosm Limited and University of Bristol

   Contributor Pierre Langlois <pierre.langlois@embecosm.com>

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
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)

void marker1 (void)
{
}

/* misc. function params */

int
qux1 (const char cc, const char /*&*/ccr, const char *ccp, char *const cpc)
{
  return 33;
}

int
qux2 (volatile unsigned char vuc, const volatile int cvi,
      volatile short /*&*/vsr, volatile long *vlp, float *volatile fpv,
      const volatile signed char *const volatile cvscpcv)
{
  return 400;
}

void
benchmark (void)
{
  char lave = 'B';
  unsigned char lavish = 10;
  short lax = 20;
  unsigned short lecherous = 30;
  long lechery = 40;
  unsigned long lectern = 50;
  float leeway = 60;
  double legacy = 70;
  signed char lemonade = 35;

  const char            laconic = 'A';
  const unsigned char   laggard = 1;
  const short           lagoon = 2;
  const unsigned short  laity = 3;
  const long            lambent = 4;
  const unsigned long   laminated = 5;
  const float           lampoon = 6;
  const double          languid = 7;

  /* pointers to constant variables */

  const char           *legend      = &lave;
  const unsigned char  *legerdemain = &lavish;
  const short          *leniency    = &lax;
  const unsigned short *leonine     = &lecherous;
  const long           *lesion      = &lechery;
  const unsigned long  *lethal      = &lectern;
  const float          *lethargic   = &leeway;
  const double         *levity      = &legacy;

  /* constant pointers to constant variables */

  const char           *const lewd          = &laconic;
  const unsigned char  *const lexicographer = &laggard;
  const short          *const lexicon       = &lagoon;
  const unsigned short *const liaison       = &laity;
  const long           *const libation      = &lambent;
  const unsigned long  *const libelous      = &laminated;
  const float          *const libertine     = &lampoon;
  const double         *const libidinous    = &languid;

  /* this is the same as const char * legend .... */

  char           const *languish   = &laconic;
  unsigned char  const *languor    = &laggard;
  short          const *lank       = &lagoon;
  unsigned short const *lapidary   = &laity;
  long           const *larceny    = &lambent;
  unsigned long  const *largess    = &laminated;
  float          const *lascivious = &lampoon;
  double         const *lassitude  = &languid;

  /* constant pointers to variable */

  char           *const   lamprey   = &lave;
  unsigned char  *const   lariat    = &lavish;
  short          *const   laudanum  = &lax;
  unsigned short *const   lecithin  = &lecherous;
  long           *const   leviathan = &lechery;
  unsigned long  *const   libretto  = &lectern;
  float          *const   lissome   = &leeway;
  double         *const   locust    = &legacy;

  /* constant arrays */
  const char logical[2] = {laconic, laconic};
  const unsigned char lugged[2] = {laggard, laggard};
  const short luck[2] = {lagoon, lagoon};
  const unsigned short lunar[2] = {laity, laity};
  const long lumen[2] = {lambent, lambent};
  const unsigned long lurk[2] = {laminated, laminated};
  const float lush[2] = {lampoon, lampoon};
  const double lynx[2] = {languid, languid};

  /* volatile variables */

  volatile char vox = 'X';
  volatile unsigned char victuals = 13;
  volatile short vixen = 200;
  volatile unsigned short vitriol = 300;
  volatile long vellum = 1000;
  volatile unsigned long valve = 2000;
  volatile float vacuity = 3.0;
  volatile double vertigo = 10.3;
    
  /* pointers to volatile variables */

  volatile char           * vampire = &vox;
  volatile unsigned char  * viper  = &victuals;
  volatile short          * vigour = &vixen;
  volatile unsigned short * vapour = &vitriol;
  volatile long           * ventricle = &vellum;
  volatile unsigned long  * vigintillion = &valve;
  volatile float          * vocation = &vacuity;
  volatile double         * veracity = &vertigo;

  /* volatile pointers to volatile variables */

  volatile char           * volatile vapidity = &vox;
  volatile unsigned char  * volatile velocity = &victuals;
  volatile short          * volatile veneer = &vixen;
  volatile unsigned short * volatile video = &vitriol;
  volatile long           * volatile vacuum = &vellum;
  volatile unsigned long  * volatile veniality = &valve;
  volatile float          * volatile vitality = &vacuity;
  volatile double         * volatile voracity = &vertigo;

  /* const volatile vars */

  const volatile char           victor = 'Y';
  const volatile unsigned char  vicar = 11;

  /* pointers to const volatiles */

  const volatile char              * victory = &victor;
  const volatile unsigned char     * vicarage = &vicar;

  /* const pointers to volatile vars */

  volatile char                    * const vein = &vox;
  volatile unsigned char           * const vogue = &victuals;

  /* const pointers to const volatile vars */

  const volatile char              * const cavern = &victor;
  const volatile unsigned char     * const coverlet = &vicar;

  /* volatile pointers to const vars */

  const char                       * volatile caveat = &laconic;
  const unsigned char              * volatile covenant = &laggard;

  /* volatile pointers to const volatile vars */

  const volatile char              * volatile vizier = &victor;
  const volatile unsigned char     * volatile vanadium = &vicar;

  /* const volatile pointers */

  char                             * const volatile vane = &lave;
  unsigned char                    * const volatile veldt = &lavish;

  /* const volatile pointers to const vars */

  const char                       * const volatile cove = &laconic;
  const unsigned char              * const volatile cavity = &laggard;
    
  /* const volatile pointers to volatile vars */

  volatile char                    * const volatile vagus = &vox;
  volatile unsigned char           * const volatile vagrancy = &victuals;
    
  /* const volatile pointers to const volatile */

  const volatile char              * const volatile vagary = &victor;
  const volatile unsigned char     * const volatile vendor = &vicar;
  
  /* various structs with const members */

  struct crass { char * const ptr; } crass = { lamprey };
  struct crisp { char * const *ptr; } crisp = { &lamprey };

  /* Reference the structs so that they are not discarded.  */
  struct crass *creed = &crass;
  struct crisp *crow = &crisp;

  /* misc. references */
  /*
  const char           & radiation = laconic;
  volatile signed char & remuneration = lemonade;
  */
  marker1 ();

  /* Silence compiler warning about unused variables.  */
  (void) lemonade;
  (void) legend;
  (void) creed;
  (void) crow;
  (void) vendor;
  (void) vagary;
  (void) vagrancy;
  (void) vagus;
  (void) cavity;
  (void) cove;
  (void) veldt;
  (void) vane;
  (void) vanadium;
  (void) vizier;
  (void) covenant;
  (void) caveat;
  (void) coverlet;
  (void) cavern;
  (void) vogue;
  (void) vein;
  (void) vicarage;
  (void) victory;
  (void) voracity;
  (void) vitality;
  (void) veniality;
  (void) vacuum;
  (void) video;
  (void) veneer;
  (void) velocity;
  (void) vapidity;
  (void) veracity;
  (void) vocation;
  (void) vigintillion;
  (void) ventricle;
  (void) vapour;
  (void) vigour;
  (void) viper;
  (void) vampire;
  (void) lynx;
  (void) lush;
  (void) lurk;
  (void) lumen;
  (void) lunar;
  (void) luck;
  (void) lugged;
  (void) logical;
  (void) locust;
  (void) lissome;
  (void) libretto;
  (void) leviathan;
  (void) lecithin;
  (void) laudanum;
  (void) lariat;
  (void) lassitude;
  (void) lascivious;
  (void) largess;
  (void) larceny;
  (void) lapidary;
  (void) lank;
  (void) languor;
  (void) languish;
  (void) libidinous;
  (void) libertine;
  (void) libelous;
  (void) libation;
  (void) liaison;
  (void) lexicon;
  (void) lexicographer;
  (void) lewd;
  (void) levity;
  (void) lethargic;
  (void) lethal;
  (void) lesion;
  (void) leonine;
  (void) leniency;
  (void) legerdemain;
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
