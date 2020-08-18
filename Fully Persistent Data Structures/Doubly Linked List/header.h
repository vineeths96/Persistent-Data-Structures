#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_OP 25
#define STR_SIZE 25
#define JUNK -1
#define UNUSED -1

typedef struct int_Node int_Node;
typedef struct int_Mod int_Mod;
typedef struct int_list_fp int_list_fp;

struct int_Node
{
  int data;
  int node_version;
  int_Mod* mod;
  int_Node* next;
  int_Node* prev;
};

struct int_Mod
{
  int data;
  int version;
  int_Node* next;
  int_Node* prev;
};

struct int_list_fp
{
  int_Node* head[MAX_OP];
  int live_version;
};

int_list_fp* int_init_list_fp();
void int_print_list_fp(int_list_fp* list, int version);
bool int_update_list_fp(int_list_fp* list, int data, int index, int version);
bool int_insert_list_fp(int_list_fp* list, int data, int index, int version);
bool int_delete_list_fp(int_list_fp* list, int index, int version);

#endif
