#include "types.h"
#include "user.h"

int 
thread_create(int (*fn)(void *, void *))
{
    void *stack = malloc(4096);

    return clone(fn, stack);
}