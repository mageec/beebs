#define SUPPORT_H 1

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_BOARDSUPPORT_H
// #include "@srcdir@/config/@ARCH@/boards/@BOARD@/boardsupport.h"
#include "boardsupport.h"
#else
// Default board support is here
#define REPEAT_FACTOR   4096
#endif

#ifdef HAVE_CHIPSUPPORT_H
// #include "@srcdir@/config/@ARCH@/chips/@CHIP@/chipsupport.h"
#include "chipsupport.h"
#else
// Default chip support is here
#warning No chipsupport.h
#endif

void initialise_board();
void start_trigger();
void stop_trigger();
