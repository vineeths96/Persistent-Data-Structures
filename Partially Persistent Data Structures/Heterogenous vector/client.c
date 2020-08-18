#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  char str[STR_SIZE];
  bool y;
  het_list_pp* list = het_init_list_pp();

  printf("Enter 5 (type, data) pair without parenthesis\nSupported types : int, char, flaot, double\n");
   
  for(int i=0; i<5; i++)
    {
      scanf("%s", str);
      if(!het_insert_list_pp(list, str, i))
	printf("Error\n");
      //het_print_list_pp(list,i);
    }
  printf("\nEnter 5 (type, data) pair to update\n");

  for(int i=0; i<5; i++)
    {
      scanf("%s", str);
      if(!het_update_list_pp(list, str, i))
	printf("Error\n");
      //het_print_list_pp(list,list->live_version);
    }
  
  printf("\n");

  for(int i=0; i<5; i++)
    {
      if(!het_delete_list_pp(list, 0))
	printf("Error\n");
      //het_print_list_pp(list, list->live_version);
    }
  
  printf("\n");

  for(int i = 0; i<15; i++)
    {
      het_print_list_pp(list,i);
    }
  
}
