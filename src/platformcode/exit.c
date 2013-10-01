#include "exit.h"

void exit(int a)
{
	while(1);
}

void _exit(int a)
{
    exit(a);
}
