#include <support.h>
#include <avr/io.h>

void initialise_board()
{
  DDRC |= _BV(DDC0);
  PORTC &= ~_BV(PORTC0);
}

void start_trigger()
{
  PORTC |= _BV(PORTC0);
}

void stop_trigger()
{
  PORTC &= ~_BV(PORTC0);
}
