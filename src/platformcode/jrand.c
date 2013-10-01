#include "jrand.h"

static unsigned int next = 1;

int jrand()
{
    next = next * 1103515245 + 12345;
    return next;
}
