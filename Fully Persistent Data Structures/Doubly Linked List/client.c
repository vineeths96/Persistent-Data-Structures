#include <stdio.h>
#include <stdbool.h>
#include "header.h"
//#include "implement.c"

int main()
{
  int x, y, z;
  char str[STR_SIZE];

  int_list_fp* list = int_init_list_fp();
  
  printf("Enter 5 numbers\n");
  for(int i=0; i<5; i++)
    {
      scanf("%d", &x);
      if(!int_insert_list_fp(list,x,i, list->live_version))
	printf("Error\n");
    }
  
  printf("\nEnter 3 (value,index,version) to insert\n");
  for(int i=0; i<3; i++)
    {
      scanf("%s",str);
      sscanf(str, "%d,%d,%d", &x, &y, &z);
      if(!int_insert_list_fp(list,x,y,z))
	printf("Error\n");
    }

  printf("\nEnter 3 (value,index,version) to update\n");
  for(int i=0; i<3; i++)
    {
      scanf("%s",str);
      sscanf(str, "%d,%d,%d", &x, &y, &z);
      if(!int_update_list_fp(list,x,y,z))
	printf("Error\n");
    }
   
  printf("\nEnter 5 (index,version) to delete\n");
  for(int i=0; i<5; i++)
    {
      scanf("%s",str);
      sscanf(str, "%d,%d", &x, &y);
      if(!int_delete_list_fp(list,x,y))
	printf("Error\n");
    }

  printf("\n");
  for(int i = 0; i<MAX_OP; i++)
    {
      int_print_list_fp(list,i);
    }
  int_print_list_fp(list,5);
  int_print_list_fp(list,6);
  int_print_list_fp(list,7);
  int_print_list_fp(list,8);
  
  /*
    int_insert_list_fp(list,1,0, list->live_version);
    int_insert_list_fp(list,2,1, list->live_version);
    int_insert_list_fp(list,3,2, list->live_version);
    int_insert_list_fp(list,4,3, list->live_version);
    int_insert_list_fp(list,5,4, list->live_version);

    int_delete_list_fp(list,1,1);
    // int_delete_list_fp(list,3,3);  int_delete_list_fp(list,4,4);  int_delete_list_fp(list,2,2);  int_delete_list_fp(list,1,1);
    *
    for(int i = 0; i<MAX_OP; i++)
    {
    int_print_list_fp(list,i);
    }*/
}
