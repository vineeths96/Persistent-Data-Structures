#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_OP 25
#define STR_SIZE 25
#define JUNK -1
#define UNUSED -1

typedef struct int_Node int_Node;
typedef struct int_Mod int_Mod;
typedef struct int_stack_fp int_stack_fp;

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

struct int_stack_fp
{
  int_Node* head[MAX_OP];
  int num_el;
  int live_version;
};

int_stack_fp* int_init_stack_fp();

bool int_stack_isEmpty_fp(int_stack_fp* stack, int version);
bool int_stack_push_fp(int_stack_fp* stack, int data, int version);
int int_stack_pop_fp(int_stack_fp* stack, int version);

void int_print_stack_fp(int_stack_fp* list, int version);


#endif
