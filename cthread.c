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
  if((uint) thread->stack % PGSIZE != 0){
    return -1;
  }
  thread->pid = clone(fn, arg1, arg2, thread->stack);
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