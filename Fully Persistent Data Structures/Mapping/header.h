#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_OP 25
#define STR_SIZE 25
#define JUNK "j"
#define UNUSED -1

typedef struct map_Node map_Node;
typedef struct map_Mod map_Mod;
typedef struct map_fp map_fp;

struct map_Node
{
  char key[STR_SIZE];
  char value[STR_SIZE];
  int node_version;
  map_Mod* mod;
  map_Node* next;
  map_Node* prev;
};

struct map_Mod
{
  char key[STR_SIZE];
  char value[STR_SIZE];
  int version;
  map_Node* next;
  map_Node* prev;
};

struct map_fp
{
  map_Node* head[MAX_OP];
  int live_version;
};

map_fp* map_init_fp();
void map_print_fp(map_fp* list, int version);
bool map_insert_fp(map_fp* list, char str[], int index, int version);
bool map_update_fp(map_fp* list, char str[], int index, int version);
void map_search_pp(map_fp* list, char str[]);
bool map_delete_fp(map_fp* list, int index, int version);

#endif
