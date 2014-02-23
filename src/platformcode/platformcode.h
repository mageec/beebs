#ifndef __PLATFORMCODE_H__
#define __PLATFORMCODE_H__

#ifndef REPEAT_FACTOR
#define REPEAT_FACTOR   (4096)
#endif

#ifdef ARM
#include "exit.h"
#include "sbrk.h"
#else
#define jrand rand
#endif /* ARM */

extern void initialise_trigger();
extern void stop_trigger();
extern void start_trigger();

#endif /* __PLATFORMCODE_H__ */
