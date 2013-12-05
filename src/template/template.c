
#include "platformcode.h"

// This scale factor will be changed to equalise the runtime of the
// benchmarks
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)

void benchmark()
{
    // Code to benchmark goes here
}


int main()
{
    int i;

    initialise_trigger();
    start_trigger();
    for(i = 0; i < SCALE_FACTOR; i++)
        benchmark();
    stop_trigger();
    return 0;
}
