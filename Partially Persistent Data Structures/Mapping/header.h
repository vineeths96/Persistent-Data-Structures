#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_OP 15
#define JUNK "j"
#define UNUSED -1
#define STR_SIZE 50

typedef struct map_Node map_Node;
typedef struct map_Mod map_Mod;
typedef struct map_pp map_pp;

struct map_Node
{
  char key[STR_SIZE];
  char value[STR_SIZE];
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

struct map_pp
{
  map_Node* head[MAX_OP];
  int live_version;
};

map_pp* map_init_pp();
void map_print_pp(map_pp* list, int version);
bool map_insert_pp(map_pp* list, char str[], int index);
bool map_update_pp(map_pp* list, char str[], int index);
void map_search_pp(map_pp* list, char str[]);
bool map_delete_pp(map_pp* list, int index);

#endif
