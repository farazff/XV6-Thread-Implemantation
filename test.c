#include "types.h"
#include "stat.h"
#include "user.h"

#define THREAD_NUMBER 6

int x = 0;

void
increase(void *a, void *b)
{
  x++;
  printf(1, "%d\n", x);
  exit();
}

int arrsum = 0;

void 
sum(void *x, void *y){
  arrsum += *((int *)x);
  printf(1, "%d\n", arrsum);
  exit();
}

int
thread_test1(void)
{
  cthread_t threads[THREAD_NUMBER];
  int arr[THREAD_NUMBER];
  int flag = 0;
  for (int i = 0; i < THREAD_NUMBER; i++){
    arr[i] = i;
    if(cthread_create(&threads[i], increase, (void *)&arr[i], 0) == -1){
      flag = 1;
    }
    if(cthread_join(&threads[i]) != threads[i].pid){
      flag = 1;
    }
  }
  printf(1, "\n********* x = %d *********\n", x);
  if(!flag)
    printf(1, "thread_test is ok.\n");
  else
    printf(1, "thread_test failed.\n");
  exit();
  return 0;
}

int
thread_test2(void)
{
  cthread_t threads[THREAD_NUMBER];
  int arr[THREAD_NUMBER];
  int flag = 0;
  for (int i = 0; i < THREAD_NUMBER; i++){
    arr[i] = i;
    if(cthread_create(&threads[i], sum, (void *)&arr[i], 0) == -1){
      flag = 1;
    }
    if(cthread_join(&threads[i]) != threads[i].pid){
      flag = 1;
    }
  }
  printf(1,"\n******** arrsum = %d *********\n", arrsum);
  if(!flag)
    printf(1, "thread_test is ok.\n");
  else
    printf(1, "thread_test failed.\n");
  exit();
  return 0;
}

int 
main(void)
{
  char input[2];
  printf(1, "1) tread_test1: increase\n2) tread_test2: sum\nYour choice: ");
  int choice = atoi(gets(input, 2));
  if(choice == 1)
    thread_test1();
  else if(choice == 2)
    thread_test2();
  else
    printf(1, "Incorrect input.\n");
  //thread_test1();
  //thread_test2();
}