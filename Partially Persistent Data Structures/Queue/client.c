#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  printf("Enter 5 numbers to enqueue\n");

  int x;
  bool y;

  int_queue_pp* queue = int_init_queue_pp();

  for(int i=0; i<5; i++)
    {
      scanf("%d", &x);
      if(!int_queue_insertRear_pp(queue, x))
	printf("Error\n");
    }

  printf("\nDequeing  from front\n");

  for(int i=0; i<5; i++)
    {
      x = int_queue_deleteFront_pp(queue);
      //  int_print_queue_pp(queue, queue->live_version);
    }
 
  for(int i = 0; i<15; i++)
    {
      int_print_queue_pp(queue,i);
    }
  
}
