#include <support.h>

void initialise_board()
{
    PIN_INIT(0);
}

void start_trigger()
{
    PIN_SET(0);
}

void stop_trigger()
{
    PIN_CLEAR(0);
}
