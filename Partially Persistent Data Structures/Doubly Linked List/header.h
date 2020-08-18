#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_OP 15
#define JUNK -1
#define UNUSED -1

typedef struct int_Node int_Node;
typedef struct int_Mod int_Mod;
typedef struct int_list_pp int_list_pp;

struct int_Node
{
  int data;
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

struct int_list_pp
{
  int_Node* head[MAX_OP];
  int live_version;
};

int_list_pp* int_init_list_pp();
void int_print_list_pp(int_list_pp* list, int version);
bool int_insert_list_pp(int_list_pp* list, int data, int index);
bool int_update_list_pp(int_list_pp* list, int data, int index);
bool int_delete_list_pp(int_list_pp* list, int index);

#endif
