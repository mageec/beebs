/* NIST Secure Hash Algorithm */

#include "support.h"
#include <stdlib.h>
#include "sha.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 10)

int benchmark()
{
   SHA_INFO sha_info;
   int n, i;
   BYTE data[256];

   srand(0);
   sha_init(&sha_info);
   for(n = 0; n < 256; ++n)
   {
      for(i = 0; i < 256; ++i)
         data[i] = rand();
      sha_update(&sha_info, data, 256);
   }
   sha_final(&sha_info);

   return 0;
}

/* vim: set ts=3 sw=3 et: */
