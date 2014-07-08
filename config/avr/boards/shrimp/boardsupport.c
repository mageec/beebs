#include <support.h>
#include <avr/io.h>

void initialise_board()
{
  PIN_INIT(C, 0);
}

void start_trigger()
{
  PIN_SET(C, 0);
}

void stop_trigger()
{
  PIN_CLEAR(C, 0);
}
