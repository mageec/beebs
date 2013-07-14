/* NIST Secure Hash Algorithm */

#include "sha.h"

#ifdef ARM
#include "platformcode.h"
#else
#define REPEAT_FACTOR (4096)
#endif /* ARM */

int main()
{
    int n;

#ifdef ARM
    initialise_trigger();
    start_trigger();
#endif /* ARM */

    for(n = 0; n < REPEAT_FACTOR>>10; ++n)
    {
        SHA_INFO sha_info;

        sha_stream(&sha_info);
    }

#ifdef ARM
    stop_trigger();
#endif /* ARM */

    return(0);
}
