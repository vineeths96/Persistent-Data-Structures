#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  int x,y;
  char str[STR_SIZE];
  char split_str[STR_SIZE];

  het_list_fp* list = het_init_list_fp();

  printf("Enter 5 (type, data) pair without parenthesis\nSupported types : int, char, flaot, double\n");
  
  for(int i=0; i<5; i++)
    {
      scanf("%s", str);
      if(!het_insert_list_fp(list, str, i, list->live_version))
	printf("Error\n");
    }
 
  printf("\nEnter 3 (type,data;index,version) to insert\n");
  for(int i=0; i<3; i++)
    {
      scanf("%s",str);
      //sscanf(str, "%d,%d,%d", &x, &y, &z);
      sscanf(str, "%[^';'];%d,%d", split_str, &x, &y);
      if(!het_insert_list_fp(list, split_str, x, y))
	printf("Error\n");
    }
  
  printf("\nEnter 3 (type,data;index,version) to update\n");
  for(int i=0; i<3; i++)
    {
      scanf("%s",str);
      //sscanf(str, "%d,%d,%d", &x, &y, &z);
      sscanf(str, "%[^';'];%d,%d", split_str, &x, &y);
      if(!het_update_list_fp(list, split_str, x, y))
	printf("Error\n");
    }
  
  printf("\nEnter 3 (index,version) to delete\n");
  for(int i=0; i<5; i++)
    {
      scanf("%s",str);
      sscanf(str, "%d,%d", &x, &y);
      if(!het_delete_list_fp(list,x,y))
	printf("Error\n");
    }
  
  printf("\n");
  for(int i = 0; i<MAX_OP; i++)
    {
      het_print_list_fp(list,i);
    }
  het_print_list_fp(list,5);
  het_print_list_fp(list,6);
  het_print_list_fp(list,7);
  het_print_list_fp(list,8);
}
