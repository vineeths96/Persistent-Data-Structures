#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_OP 15
#define JUNK -1
#define UNUSED -1
#define STR_SIZE 50 

typedef struct het_Node het_Node;
typedef struct het_Mod het_Mod;
typedef struct het_list_pp het_list_pp;

struct het_Node
{
  char *identifier;
  
  int int_data;
  float float_data;
  char char_data;
  double double_data;
  
  het_Mod* mod;
  het_Node* next;
  het_Node* prev;
};

struct het_Mod
{
  char *identifier;
  
  int int_data;
  float float_data;
  char char_data;
  double double_data;
  
  int version;
  het_Node* next;
  het_Node* prev;
};

struct het_list_pp
{
  het_Node* head[MAX_OP];
  int live_version;
};

het_list_pp* het_init_list_pp();

void het_print_list_pp(het_list_pp* list, int version);

bool het_insert_list_pp(het_list_pp* list, char str[], int index);
bool het_update_list_pp(het_list_pp* list, char str[], int index);

bool het_delete_list_pp(het_list_pp* list, int index);
#endif
