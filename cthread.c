#include "types.h"
#include "user.h"

#define PGSIZE 4096

int 
cthread_create(cthread_t *thread, void (*fn)(void *, void *), 
	       void *arg1, void *arg2)
{
  thread->stack = (char *)malloc(PGSIZE);
  if(thread->stack == 0){
    return -1;
  }

  // little magic cheating here?
  // breaking the kernel abstraction?
  // top - 04: arg2
  // top - 08: arg1
  // top - 12: return address..

  //*(thread_stack - 12) = exit;

  thread->pid = clone(fn, arg1, arg2, thread->stack , 0);
  if(thread->pid == -1){
    return -1;
  }

  return thread->pid;
}

int cthread_join(cthread_t *thread)
{
  if(join(thread->pid) != thread->pid){
    free(thread->stack);
    return -1;
  }
  free(thread->stack);
  return thread->pid;
}