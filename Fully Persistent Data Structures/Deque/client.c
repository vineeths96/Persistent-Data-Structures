#include <stdio.h>
#include <stdbool.h>
#include "header.h"
//#include "implement.c"
int main()
{
  int x, y, z;
 
  int_deque_fp* deque = int_init_deque_fp();

  printf("Enter 3 numbers to enqueue at front\n");
  for(int i=0; i<3; i++)
    {
      scanf("%d", &x);
      if(!int_deque_insertFront_fp(deque,x, deque->live_version))
	printf("Error\n");
    }
 
  printf("\nEnter 3 numbers to enqueue at rear\n");
  for(int i=0; i<3; i++)
    {
      scanf("%d",&x);
      if(!int_deque_insertRear_fp(deque,x,deque->live_version))
	printf("Error\n");
    }

  printf("\nEnter 3 (value,version) to enqueue at front\n");
  for(int i=0; i<3; i++)
    {
      scanf("%d,%d", &x, &y);
      if(!int_deque_insertFront_fp(deque,x,y))
	printf("Error\n");
    }

  printf("\nEnter 3 (value,version) to enqueue at rear\n");
  for(int i=0; i<3; i++)
    {
      scanf("%d,%d", &x, &y);
      if(!int_deque_insertRear_fp(deque,x,y))
	printf("Error\n");
    }
  
  printf("\nEnter 3 (version) to dequeue from front\n");
  for(int i=0; i<3; i++)
    {
      scanf("%d", &x);
      if(!int_deque_deleteFront_fp(deque,x))
	printf("Error\n");
    }

  printf("\nEnter 3 (version) to dequeue from rear\n");
  for(int i=0; i<3; i++)
    {
      scanf("%d", &x);
      if(!int_deque_deleteRear_fp(deque,x))
	printf("Error\n");
    }

  printf("\n");
  for(int i = 0; i<MAX_OP; i++)
    {
      int_print_deque_fp(deque,i);
    }
  int_print_deque_fp(deque,5);
  int_print_deque_fp(deque,6);
  int_print_deque_fp(deque,7);
  int_print_deque_fp(deque,8);
}
