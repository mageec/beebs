#ifdef ARM
#include "platformcode.h"
#else
#define REPEAT_FACTOR (4096)
#endif /* ARM */

#include "snipmath.h"
#include <math.h>

/* The printf's may be removed to isolate just the math calculations */

int main(void)
{
  double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
  double  a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
  double  a3 = 1.0, b3 = -3.5, c3 = 22.0, d3 = -31.0;
  double  a4 = 1.0, b4 = -13.7, c4 = 1.0, d4 = -35.0;
  double  x[3];
  double X;
  int     solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  struct int_sqrt q;
  long n = 0;

  int output[24] = {0};
  int output_count = 0;
  int check_output[24] = {-9, 0, 0, -9, 0, 0, -8, 0, 0, -8, 0, 0,
      -4, 0, 0, -4, 0, 0, -3, 0, -1, -3, 0, -1};

#ifdef ARM
  initialise_trigger();
  start_trigger();
#endif /* ARM */

  for(n = 0; n < (REPEAT_FACTOR>>13)+1; ++n)
  {
    /* solve some cubic functions */
    /* should get 3 solutions: 2, 6 & 2.5   */
    SolveCubic(a1, b1, c1, d1, &solutions, x);
    /* should get 1 solution: 2.5           */
    SolveCubic(a2, b2, c2, d2, &solutions, x);
    SolveCubic(a3, b3, c3, d3, &solutions, x);
    SolveCubic(a4, b4, c4, d4, &solutions, x);
    /* Now solve some random equations */
    for(a1=1;a1<3;a1++) {
      for(b1=10;b1>8;b1--) {
        for(c1=5;c1<6;c1+=0.5) {
        	for(d1=-1;d1>-3;d1--) {
        	  SolveCubic(a1, b1, c1, d1, &solutions, x);
        	}

            for (i = 0; i < solutions; i++) {
                output[output_count] = x[i];
                output_count++;
            }
        }
      }
    }
  }

#ifdef ARM
  stop_trigger();
#endif /* ARM */

  /* Verify that we have the correct result. */
  int to_return = 0;
  for (i = 0; i < output_count; i++) {
      if (output[i] != check_output[i]) {
          to_return = -1;
          break;
      }
  }

  return to_return;
}
