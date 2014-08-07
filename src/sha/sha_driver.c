/* NIST Secure Hash Algorithm */

#include "support.h"
#include "sha.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 10)

int main()
{
   int n;
   SHA_INFO sha_info;
#ifdef __LP64__
   LONG check_digest[5] = {2408376001709644836U, 6900969603643847736U,
      4253644267545137933U, 3826789073253030153U, 2136447545864889176U};

#else
   /* Assume 32 bits */
   LONG check_digest[5] = {2692311041, 844123682,
      242085432, 2188392725, 1497303427};
#endif

   initialise_board();
   start_trigger();

   for(n = 0; n < SCALE_FACTOR; ++n) {
      sha_stream(&sha_info);
   }

   stop_trigger();

   int to_return = 0;
   for (int i = 0; i < 5; i++) {
      if (sha_info.digest[i] != check_digest[i]) {
         to_return = -1;
         break;
      }
   }

   return to_return;
}

/* vim: set ts=3 sw=3 et: */
