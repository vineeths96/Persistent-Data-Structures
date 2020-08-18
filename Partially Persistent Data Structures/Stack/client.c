#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  printf("Enter 5 numbers to push into stack\n");

  int x;
  bool y;

  int_stack_pp* stack = int_init_stack_pp();

  for(int i=0; i<5; i++)
    {
      scanf("%d", &x);
      if(!int_stack_push_pp(stack, x))
	printf("Error\n");
    }

  printf("\nDequeing alternatively from front and rearPoping from the stack\n");

  for(int i=0; i<5; i++)
    {
      x = int_stack_pop_pp(stack);
      //  int_print_stack_pp(deque, deque->live_version);
    }
 
  for(int i = 0; i<15; i++)
    {
      int_print_stack_pp(stack,i);
    }
  
}
