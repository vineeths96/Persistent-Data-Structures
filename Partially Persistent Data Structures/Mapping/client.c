#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  char str[STR_SIZE];
 
  map_pp* list = map_init_pp();

  printf("Enter 5 (key, value) pair without parenthesis\n");
  for(int i=0; i<5; i++)
    {
      scanf("%s", str);
      if(!map_insert_pp(list, str, i))
	printf("Error\n");
      // map_print_list_pp(list,i);
    }
    
  printf("\nEnter 5 (key, value) pair to update\n");
  for(int i=0; i<5; i++)
    {
      scanf("%s", str);
      if(!map_update_pp(list, str, i))
	printf("Error\n");
      //  map_print_list_pp(list,list->live_version);
    }
  
  printf("\nEnter 3 (key, version) pair to search\n");

  for(int i=0; i<3; i++)
    {
      scanf("%s", str);
      map_search_pp(list, str);
    }
  
  printf("\n");
  for(int i=0; i<5; i++)
    {
      if(!map_delete_pp(list, 0))
	printf("Error\n");
      // map_print_list_pp(list, list->live_version);
    }

  for(int i = 0; i<15; i++)
    {
      map_print_pp(list,i);
    }
  
}
