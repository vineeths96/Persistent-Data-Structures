#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_OP 25
#define STR_SIZE 25
#define JUNK -1
#define UNUSED -1

typedef struct het_Node het_Node;
typedef struct het_Mod het_Mod;
typedef struct het_list_fp het_list_fp;


struct het_Node
{
  char *identifier;
  int node_version;
  
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

struct het_list_fp
{
  het_Node* head[MAX_OP];
  int live_version;
};

het_list_fp* het_init_list_fp();

void het_print_list_fp(het_list_fp* list, int version);
bool het_insert_list_fp(het_list_fp* list, char str[], int index, int version);
bool het_update_list_fp(het_list_fp* list, char str[], int index, int version);
bool het_delete_list_fp(het_list_fp* list, int index, int version);

#endif
