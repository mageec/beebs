
#include <math.h>
#include <stdlib.h>

#include "platformcode.h"

#define SCALE_FACTOR (REPEAT_FACTOR >> 8)

#define PI 3.141592653589793
#define SOLAR_MASS ( 4 * PI * PI )
#define DAYS_PER_YEAR 365.24

struct body {
   double x[3], fill, v[3], mass;
};

static struct body solar_bodies[] = {
   /* sun */
   {
      .x = { 0., 0., 0. },
      .v = { 0., 0., 0. },
      .mass = SOLAR_MASS
   },
   /* jupiter */
   {
      .x = { 4.84143144246472090e+00,
         -1.16032004402742839e+00,
         -1.03622044471123109e-01 },
      .v = { 1.66007664274403694e-03 * DAYS_PER_YEAR,
         7.69901118419740425e-03 * DAYS_PER_YEAR,
         -6.90460016972063023e-05 * DAYS_PER_YEAR },
      .mass = 9.54791938424326609e-04 * SOLAR_MASS
   },
   /* saturn */
   {
      .x = { 8.34336671824457987e+00,
         4.12479856412430479e+00,
         -4.03523417114321381e-01 },
      .v = { -2.76742510726862411e-03 * DAYS_PER_YEAR,
         4.99852801234917238e-03 * DAYS_PER_YEAR,
         2.30417297573763929e-05 * DAYS_PER_YEAR },
      .mass = 2.85885980666130812e-04 * SOLAR_MASS
   },
   /* uranus */
   {
      .x = { 1.28943695621391310e+01,
         -1.51111514016986312e+01,
         -2.23307578892655734e-01 },
      .v = { 2.96460137564761618e-03 * DAYS_PER_YEAR,
         2.37847173959480950e-03 * DAYS_PER_YEAR,
         -2.96589568540237556e-05 * DAYS_PER_YEAR },
      .mass = 4.36624404335156298e-05 * SOLAR_MASS
   },
   /* neptune */
   {
      .x = { 1.53796971148509165e+01,
         -2.59193146099879641e+01,
         1.79258772950371181e-01 },
      .v = { 2.68067772490389322e-03 * DAYS_PER_YEAR,
         1.62824170038242295e-03 * DAYS_PER_YEAR,
         -9.51592254519715870e-05 * DAYS_PER_YEAR },
      .mass = 5.15138902046611451e-05 * SOLAR_MASS
   }
};

static const int BODIES_SIZE = sizeof(solar_bodies) / sizeof(solar_bodies[0]);

void offset_momentum(struct body *bodies, unsigned int nbodies)
{
   unsigned int i, k;
   for (i = 0; i < nbodies; ++i)
      for (k = 0; k < 3; ++k)
         bodies[0].v[k] -= bodies[i].v[k] * bodies[i].mass
            / SOLAR_MASS;
}


double bodies_energy(struct body *bodies, unsigned int nbodies) {
   double dx[3], distance, e = 0.0;
   unsigned int i, j, k;

   for (i=0; i < nbodies; ++i) {
      e += bodies[i].mass * ( bodies[i].v[0] * bodies[i].v[0]
         + bodies[i].v[1] * bodies[i].v[1]
         + bodies[i].v[2] * bodies[i].v[2] ) / 2.;

      for (j=i+1; j < nbodies; ++j) {
         for (k = 0; k < 3; ++k)
            dx[k] = bodies[i].x[k] - bodies[j].x[k];

         distance = sqrt(dx[0] * dx[0] + dx[1] * dx[1]
            + dx[2] * dx[2]);
         e -= (bodies[i].mass * bodies[j].mass) / distance;
      }
   }
   return e;
}

int benchmark(int n)
{
   int i;
   offset_momentum(solar_bodies, BODIES_SIZE);
   /*printf("%.9f\n", bodies_energy(solar_bodies, BODIES_SIZE));*/
   for (i = 0; i < n; ++i)
       bodies_energy(solar_bodies, BODIES_SIZE);
   /*printf("%.9f\n", bodies_energy(solar_bodies, BODIES_SIZE));*/
   return 0;
}

int main()
{
   int n;

   initialise_trigger();
   start_trigger();
   for(n = 0; n < SCALE_FACTOR; ++n)
      benchmark(100);
   stop_trigger();

   return 0;
}
