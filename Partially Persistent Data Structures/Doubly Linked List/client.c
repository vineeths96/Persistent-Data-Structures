#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  printf("Enter 5 numbers\n");

  int x;
  bool y;

  int_list_pp* list = int_init_list_pp();

  for(int i=0; i<5; i++)
    {
      scanf("%d", &x);
      if(!int_insert_list_pp(list,x,i))
	printf("Error\n");
    }
  printf("\nEnter 5 numbers to update\n");

  for(int i=0; i<5; i++)
    {
      scanf("%d", &x);
      if(!int_update_list_pp(list,x,i))
	printf("Error\n");
      // int_print_list_pp(list,list->live_version);
    }
  
  // int_delete_list_pp(list,6);
  // int_delete_list_pp(list,5);
  // int_delete_list_pp(list,4);
  
  for(int i=0; i<5; i++)
    {
      if(!int_delete_list_pp(list,0))
	printf("Error\n");
      //  int_print_list_pp(list,list->live_version);
    }
 
  for(int i = 0; i<15; i++)
    {
      int_print_list_pp(list,i);
    }
  
}
