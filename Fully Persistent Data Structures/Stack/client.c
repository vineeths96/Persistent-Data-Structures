#include <stdio.h>
#include <stdbool.h>
#include "header.h"
//#include "implement.c"
int main()
{
  int x, y, z;
 
  int_stack_fp* stack = int_init_stack_fp();

  printf("Enter 5 numbers to push to stack\n");
  for(int i=0; i<5; i++)
    {
      scanf("%d", &x);
      if(!int_stack_push_fp(stack,x, stack->live_version))
	printf("Error\n");
    }
 

  printf("\nEnter 3 (value,version) to push to stack\n");
  for(int i=0; i<3; i++)
    {
      scanf("%d,%d", &x, &y);
      if(!int_stack_push_fp(stack,x,y))
	printf("Error\n");
    }
  
  printf("\nEnter 3 (version) to pop from stack\n");
  for(int i=0; i<3; i++)
    {
      scanf("%d", &x);
      if(!int_stack_pop_fp(stack,x))
	printf("Error\n");
    }

  printf("\n");
  for(int i = 0; i<MAX_OP; i++)
    {
      int_print_stack_fp(stack,i);
    }
  int_print_stack_fp(stack,5);
  int_print_stack_fp(stack,6);
  int_print_stack_fp(stack,7);
  int_print_stack_fp(stack,8);
}
