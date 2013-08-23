#include "sbrk.h"

void *_sbrk (int nbytes)
{
  /* Symbol defined by linker map */
  extern int  _start_heap;              /* start of free memory (as symbol) */

  /* Value set by crt0.S */
  extern void *end;           /* end of free memory */

  /* The statically held previous end of the heap, with its initialization. */
  static void *heap_ptr = (void *)&_start_heap;         /* Previous end */

  if ((end - (heap_ptr + nbytes)) < STACK_BUFFER )
    {
      void *base  = heap_ptr;
      heap_ptr   += nbytes;

      return  base;
    }
  else
    {
      return  (void *) -1;
    }
}       /* _sbrk () */
