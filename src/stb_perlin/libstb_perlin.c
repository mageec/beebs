/* -*- mode: C++; c-file-style: "gnu-mode" -*- */
/* BEEBS perlin noise benchmark

   Adapted from stb_perlin.h -- perlin noise generation -- v0.2
   public domain single-file C implementation by Sean Barrett
   <https://github.com/nothings/stb>

   Copyright (C) 2013 Embecosm Limited and University of Bristol

   Contributor George Field <george.field@bristol.ac.uk>

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
/* Required for floor() */
#include <math.h>

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 4


/* Not same permutation table as Perlin's reference to avoid copyright issues;
   Perlin's table can be found at http://mrl.nyu.edu/~perlin/noise/ */
static const int stb__perlin_randtab[512] =
{
   23,  125, 161, 52,  103, 117, 70,  37,  247, 101, 203, 169, 124, 126, 44,  123, 
   152, 238, 145, 45,  171, 114, 253, 10,  192, 136, 4,   157, 249, 30,  35,  72, 
   175, 63,  77,  90,  181, 16,  96,  111, 133, 104, 75,  162, 93,  56,  66,  240, 
   8,   50,  84,  229, 49,  210, 173, 239, 141, 1,   87,  18,  2,   198, 143, 57, 
   225, 160, 58,  217, 168, 206, 245, 204, 199, 6,   73,  60,  20,  230, 211, 233, 
   94,  200, 88,  9,   74,  155, 33,  15,  219, 130, 226, 202, 83,  236, 42,  172, 
   165, 218, 55,  222, 46,  107, 98,  154, 109, 67,  196, 178, 127, 158, 13,  243, 
   65,  79,  166, 248, 25,  224, 115, 80,  68,  51,  184, 128, 232, 208, 151, 122, 
   26,  212, 105, 43,  179, 213, 235, 148, 146, 89,  14,  195, 28,  78,  112, 76,  
   250, 47,  24,  251, 140, 108, 186, 190, 228, 170, 183, 139, 39,  188, 244, 246, 
   132, 48,  119, 144, 180, 138, 134, 193, 82,  182, 120, 121, 86,  220, 209, 3,   
   91,  241, 149, 85,  205, 150, 113, 216, 31,  100, 41,  164, 177, 214, 153, 231, 
   38,  71,  185, 174, 97,  201, 29,  95,  7,   92,  54,  254, 191, 118, 34,  221, 
   131, 11,  163, 99,  234, 81,  227, 147, 156, 176, 17,  142, 69,  12,  110, 62,  
   27,  255, 0,   194, 59,  116, 242, 252, 19,  21,  187, 53,  207, 129, 64,  135, 
   61,  40,  167, 237, 102, 223, 106, 159, 197, 189, 215, 137, 36,  32,  22,  5, 

   /* and a second copy so we don't need an extra mask or static initializer */
   23,  125, 161, 52,  103, 117, 70,  37,  247, 101, 203, 169, 124, 126, 44,  123, 
   152, 238, 145, 45,  171, 114, 253, 10,  192, 136, 4,   157, 249, 30,  35,  72, 
   175, 63,  77,  90,  181, 16,  96,  111, 133, 104, 75,  162, 93,  56,  66,  240, 
   8,   50,  84,  229, 49,  210, 173, 239, 141, 1,   87,  18,  2,   198, 143, 57, 
   225, 160, 58,  217, 168, 206, 245, 204, 199, 6,   73,  60,  20,  230, 211, 233, 
   94,  200, 88,  9,   74,  155, 33,  15,  219, 130, 226, 202, 83,  236, 42,  172, 
   165, 218, 55,  222, 46,  107, 98,  154, 109, 67,  196, 178, 127, 158, 13,  243, 
   65,  79,  166, 248, 25,  224, 115, 80,  68,  51,  184, 128, 232, 208, 151, 122, 
   26,  212, 105, 43,  179, 213, 235, 148, 146, 89,  14,  195, 28,  78,  112, 76,  
   250, 47,  24,  251, 140, 108, 186, 190, 228, 170, 183, 139, 39,  188, 244, 246, 
   132, 48,  119, 144, 180, 138, 134, 193, 82,  182, 120, 121, 86,  220, 209, 3,   
   91,  241, 149, 85,  205, 150, 113, 216, 31,  100, 41,  164, 177, 214, 153, 231, 
   38,  71,  185, 174, 97,  201, 29,  95,  7,   92,  54,  254, 191, 118, 34,  221, 
   131, 11,  163, 99,  234, 81,  227, 147, 156, 176, 17,  142, 69,  12,  110, 62,  
   27,  255, 0,   194, 59,  116, 242, 252, 19,  21,  187, 53,  207, 129, 64,  135, 
   61,  40,  167, 237, 102, 223, 106, 159, 197, 189, 215, 137, 36,  32,  22,  5, 
};

static float stb__perlin_lerp(float a, float b, float t)
{
   return a + (b-a) * t;
}

/* different grad function from Perlin's, but easy to modify to match reference */
static float stb__perlin_grad(int hash, float x, float y, float z)
{
   static float basis[12][4] =
   {
      {  1, 1, 0 },
      { -1, 1, 0 },
      {  1,-1, 0 },
      { -1,-1, 0 },
      {  1, 0, 1 },
      { -1, 0, 1 },
      {  1, 0,-1 },
      { -1, 0,-1 },
      {  0, 1, 1 },
      {  0,-1, 1 },
      {  0, 1,-1 },
      {  0,-1,-1 },
   };

   /* perlin's gradient has 12 cases so some get used 1/16th of the time
      and some 2/16ths. We reduce bias by changing those fractions
      to 5/16ths and 6/16ths, and the same 4 cases get the extra weight. */
   static unsigned char indices[64] =
   {
      0,1,2,3,4,5,6,7,8,9,10,11,
      0,9,1,11,
      0,1,2,3,4,5,6,7,8,9,10,11,
      0,1,2,3,4,5,6,7,8,9,10,11,
      0,1,2,3,4,5,6,7,8,9,10,11,
      0,1,2,3,4,5,6,7,8,9,10,11,
   };

   /* if you use reference permutation table, change 63 below to 15 to 
      match reference */
   float *grad = basis[indices[hash & 63]];
   return grad[0]*x + grad[1]*y + grad[2]*z;
}

#define stb__perlin_ease(a)   (((a*6-15)*a + 10) * a * a * a);

float stb_perlin_noise3(float x, float y, float z, int x_wrap, int y_wrap, int z_wrap)
{
   float u,v,w;
   float n000,n001,n010,n011,n100,n101,n110,n111;
   float n00,n01,n10,n11;
   float n0,n1;

   unsigned int x_mask = (x_wrap-1) & 255;
   unsigned int y_mask = (y_wrap-1) & 255;
   unsigned int z_mask = (z_wrap-1) & 255;
   int px = (int) floor(x);
   int py = (int) floor(y);
   int pz = (int) floor(z);
   int x0 = px & x_mask, x1 = (px+1) & x_mask;
   int y0 = py & y_mask, y1 = (py+1) & y_mask;
   int z0 = pz & z_mask, z1 = (pz+1) & z_mask;
   int r0,r1, r00,r01,r10,r11;

   x -= px; u = stb__perlin_ease(x);
   y -= py; v = stb__perlin_ease(y);
   z -= pz; w = stb__perlin_ease(z);

   r0 = stb__perlin_randtab[x0];
   r1 = stb__perlin_randtab[x1];

   r00 = stb__perlin_randtab[r0+y0];
   r01 = stb__perlin_randtab[r0+y1];
   r10 = stb__perlin_randtab[r1+y0];
   r11 = stb__perlin_randtab[r1+y1];

   n000 = stb__perlin_grad(stb__perlin_randtab[r00+z0], x  , y  , z   );
   n001 = stb__perlin_grad(stb__perlin_randtab[r00+z1], x  , y  , z-1 );
   n010 = stb__perlin_grad(stb__perlin_randtab[r01+z0], x  , y-1, z   );
   n011 = stb__perlin_grad(stb__perlin_randtab[r01+z1], x  , y-1, z-1 );
   n100 = stb__perlin_grad(stb__perlin_randtab[r10+z0], x-1, y  , z   );
   n101 = stb__perlin_grad(stb__perlin_randtab[r10+z1], x-1, y  , z-1 );
   n110 = stb__perlin_grad(stb__perlin_randtab[r11+z0], x-1, y-1, z   );
   n111 = stb__perlin_grad(stb__perlin_randtab[r11+z1], x-1, y-1, z-1 );

   n00 = stb__perlin_lerp(n000,n001,w);
   n01 = stb__perlin_lerp(n010,n011,w);
   n10 = stb__perlin_lerp(n100,n101,w);
   n11 = stb__perlin_lerp(n110,n111,w);

   n0 = stb__perlin_lerp(n00,n01,v);
   n1 = stb__perlin_lerp(n10,n11,v);

   return stb__perlin_lerp(n0,n1,u);
}

#define NOISE_START_XY 5.0
#define NOISE_Z 1.0
#define NOISE_STEP 0.1

#define PX_LIM 10

static float res[PX_LIM][PX_LIM];

/* This benchmark does not support verification */

int
verify_benchmark (int result __attribute ((unused)) )
{
  static const float exp[PX_LIM][PX_LIM] = {
    {  0.0000000000, -0.0077039809, -0.0463358946, -0.1141561490, -0.1904640640,
      -0.2500000000, -0.2730239930, -0.2510761020, -0.1884158850, -0.0991439149
    },
    {  0.0991439074,  0.0914399251,  0.0486288741, -0.0293106586, -0.1212705220,
      -0.2000000480, -0.2428427490, -0.2382289170, -0.1879217920, -0.1050186680
    },
    {  0.1884158550,  0.1848910150,  0.1420799490,  0.0571305156, -0.0497226715,
      -0.1500000800, -0.2179950920, -0.2379744350, -0.2075582590, -0.1372817460
    },
    {  0.2510760720,  0.2576704920,  0.2218693490,  0.1369199310,  0.0202583969,
      -0.0999999046, -0.1956550480, -0.2461079360, -0.2431345280, -0.1927489340
    },
    {  0.2730240230,  0.2952703830,  0.2743625640,  0.1992214920,  0.0825599432,
      -0.0499999821, -0.1692286430, -0.2500150200, -0.2775152330, -0.2517227530
    },
    {  0.2500000000,  0.2914399800,  0.2920800450,  0.2369198350,  0.1325598960,
       0.0000000000, -0.1325598960, -0.2369198800, -0.2920802240, -0.2914400100
    },
    {  0.1904640500,  0.2517227230,  0.2775151130,  0.2500150200,  0.1692286130,
       0.0499999523, -0.0825599432, -0.1992214920, -0.2743628030, -0.2952704430
    },
    {  0.1141561270,  0.1927488740,  0.2431344090,  0.2461079060,  0.1956550180,
       0.0999999046, -0.0202584267, -0.1369199750, -0.2218695880, -0.2576705810
    },
    {  0.0463357568,  0.1372815970,  0.2075580810,  0.2379743460,  0.2179950770,
       0.1500000950,  0.0497227311, -0.0571305752, -0.1420801280, -0.1848910450
    },
    {  0.00770395994, 0.1050186530,  0.1879217030,  0.2382288870,  0.2428427190,
       0.2000000480,  0.1212705080,  0.0293106437, -0.0486289859, -0.0914399624}
  };

  int xpx, ypx;

  for (ypx = 0; ypx < PX_LIM; ypx++)
    for (xpx = 0; xpx < PX_LIM; xpx++)
      if (fabs (res[ypx][xpx] - exp[ypx][xpx]) > 1.0e-6)
	return 0;

  return 1;
}


void
initialise_benchmark (void)
{
}



int benchmark(void)
{
  int  i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    {
      int xpx, ypx;
      float x, y;

      /* Calculate a plane of noise */
      for (ypx = 0; ypx < PX_LIM; ++ypx)
	{
	  for (xpx = 0; xpx < PX_LIM; ++xpx)
	    {
	      x = (float)xpx * NOISE_STEP + NOISE_START_XY;
	      y = (float)ypx * NOISE_STEP + NOISE_START_XY;
	      res[ypx][xpx] = stb_perlin_noise3(x, y, NOISE_Z, 0, 0, 0);
	    }
	}
    }

  return 0;
}
