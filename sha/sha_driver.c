/* NIST Secure Hash Algorithm */

#include "sha.h"

#include "platformcode.h"

int main()
{
    int n;

    initialise_trigger();
    start_trigger();
    for(n = 0; n < REPEAT_FACTOR>>10; ++n)
    {
        SHA_INFO sha_info;

        sha_stream(&sha_info);
    }
    stop_trigger();
    return(0);
}
