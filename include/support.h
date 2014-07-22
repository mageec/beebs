#define SUPPORT_H 1

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_BOARDSUPPORT_H
// #include "@srcdir@/config/@ARCH@/boards/@BOARD@/boardsupport.h"
#include "boardsupport.h"
#else
// Default board support is here
#define BOARD_REPEAT_FACTOR   4096
#endif

// If we don't define a default scaling value for the benchmark, define
#ifndef CALIB_SCALE
#define CALIB_SCALE 0
#endif

// The overall repeat factor is scaled by the command-line given
// CALIB_SCALE.
#define REPEAT_FACTOR ((BOARD_REPEAT_FACTOR) >> (CALIB_SCALE))

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
