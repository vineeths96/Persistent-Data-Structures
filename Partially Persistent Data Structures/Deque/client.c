#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  int x;
  bool y;

  int_deque_pp* deque = int_init_deque_pp();
  
  printf("Enter 5 numbers to enqueue at front\n");
  for(int i=0; i<3; i++)
    {
      scanf("%d", &x);
      if(!int_deque_insertFront_pp(deque, x))
	printf("Error\n");
    }

  printf("\nEnter 3 numbers to enqueue at rear\n");

  for(int i=0; i<3; i++)
    {
      scanf("%d", &x);
      if(!int_deque_insertRear_pp(deque, x))
	printf("Error\n");
      // int_print_deque_pp(deque, deque->live_version);
    }
  
  printf("\nDequeing alternatively from front and rear\n");

  for(int i=0; i<3; i++)
    {
      x = int_deque_deleteFront_pp(deque);
	
      x = int_deque_deleteRear_pp(deque);

      //  int_print_deque_pp(deque, deque->live_version);
    }
 
  for(int i = 0; i<15; i++)
    {
      int_print_deque_pp(deque,i);
    }
  
}
