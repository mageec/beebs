#ifndef CHIPSUPPORT_H
#define CHIPSUPPORT_H

#define PIN_INIT(port, number)                  \
  DDR ## port |= _BV(DD ## port ## number);     \
  PORT ## port &= ~_BV(PORT ## port ## number);

#define PIN_SET(port, number)                   \
  PORT ## port |= _BV(PORT ## port ## number);

#define PIN_CLEAR(port, number)                 \
  PORT ## port &= ~_BV(PORT ## port ## number);

#endif
