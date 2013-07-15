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
    SHA_INFO sha_info;
#ifdef __LP64__
    LONG check_digest[5] = {2408376001709644836U, 6900969603643847736U,
        4253644267545137933U, 3826789073253030153U, 2136447545864889176U};

#else
    /* Assume 32 bits */
    LONG check_digest[5] = {2692311041, 844123682,
        242085432, 2188392725, 1497303427};
#endif

#ifdef ARM
    initialise_trigger();
    start_trigger();
#endif /* ARM */

    for(n = 0; n < REPEAT_FACTOR>>10; ++n) {
        sha_stream(&sha_info);
    }

#ifdef ARM
    stop_trigger();
#endif /* ARM */

    int to_return = 0;
    for (int i = 0; i < 5; i++) {
        if (sha_info.digest[i] != check_digest[i]) {
            to_return = -1;
            break;
        }
    }

    return to_return;
}
