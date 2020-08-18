#include <stdio.h>
#include <stdbool.h>
#include "header.h"
//#include "implement.c"
int main()
{
  int x, y, z;
 
  int_queue_fp* queue = int_init_queue_fp();

  printf("Enter 5 numbers to enqueue\n");
  for(int i=0; i<5; i++)
    {
      scanf("%d", &x);
      if(!int_queue_enqueue_fp(queue,x, queue->live_version))
	printf("Error\n");
    }
  printf("\nEnter 3 (value,version) to enqueue \n");
  for(int i=0; i<3; i++)
    {
      scanf("%d,%d", &x, &y);
      if(!int_queue_enqueue_fp(queue,x,y))
	printf("Error\n");
    }
  
  printf("\nEnter 3 (version) to dequeue \n");
  for(int i=0; i<3; i++)
    {
      scanf("%d", &x);
      if(!int_queue_dequeue_fp(queue,x))
	printf("Error\n");
    }

  printf("\n");
  for(int i = 0; i<MAX_OP; i++)
    {
      int_print_queue_fp(queue,i);
    }
  int_print_queue_fp(queue,5);
  int_print_queue_fp(queue,6);
  int_print_queue_fp(queue,7);
  int_print_queue_fp(queue,8);
}
