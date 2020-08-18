#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  int x, y, z;
  char str[STR_SIZE];
  char split_str[STR_SIZE];
  
  map_fp* list = map_init_fp();

  printf("Enter 5 (key, value) pair without parenthesis\n");
  for(int i=0; i<5; i++)
    {
      scanf("%s", str);
      if(!map_insert_fp(list,str,i,list->live_version))
	printf("Error\n");
    }
 
  printf("\nEnter 3 (key,value;index,version) to insert\n");
  for(int i=0; i<3; i++)
    {
      scanf("%s",str);
      //sscanf(str, "%d,%d,%d", &x, &y, &z);
      sscanf(str, "%[^';'];%d,%d", split_str, &x, &y);
      if(!map_insert_fp(list,split_str,x,y))
	printf("Error\n");
    }

  printf("\nEnter 3 (key,value;index,version) to update\n");
  for(int i=0; i<3; i++)
    {
      scanf("%s",str);
      //sscanf(str, "%d,%d,%d", &x, &y, &z);
      sscanf(str, "%[^';'];%d,%d", split_str, &x, &y);
      if(!map_update_fp(list,split_str,x,y))
	printf("Error\n");
    }

  printf("\nEnter 3 (key, version) pair to search\n");
  for(int i=0; i<3; i++)
    {
      scanf("%s", str);
      map_search_fp(list, str);
    }
  
  printf("\nEnter 5 (index,version) to delete\n");
  for(int i=0; i<5; i++)
    {
      scanf("%s",str);
      sscanf(str, "%d,%d", &x, &y);
      if(!map_delete_fp(list,x,y))
	printf("Error\n");
    }

  printf("\n");
  for(int i = 0; i<MAX_OP; i++)
    {
      map_print_fp(list,i);
    }

  map_print_fp(list,5);
  map_print_fp(list,6);
  map_print_fp(list,7);
  map_print_fp(list,8);
}
