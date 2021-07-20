#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
cottonthread(void *a, void *b)
{
  printf(1, "\ncotton thread!!!\n");
  return 0;
}

#define NT 5
// size of ptable.proc is 64
// so there are 61 remaining slots after init, sh, clonetests
// 61 threads should be created and joined
int
cottontest1(void)
{
  cthread_t threads[NT];
  int arr[NT];
  int i;
  int ret;
  int failed = 0;

  for (i = 0; i < NT; i++){
    arr[i] = i;
    if((ret = cthread_create(&threads[i], cottonthread, (void *)&arr[i], 0)) == -1){
      printf(1, "cotton thread test failed\n");
      failed = 1;
    }
  }


  for (i = 0; i < NT; i++){
    if((ret = cthread_join(&threads[i])) != threads[i].pid){
      printf(1, "cotton thread test failed\n");
      failed = 1;
    }
  }

  if(!failed)
    printf(1, "cotton thread test ok\n");

  return 0;
}


int 
main(void)
{
  cottontest1();
}