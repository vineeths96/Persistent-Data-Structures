#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_OP 15
#define JUNK -1
#define UNUSED -1

typedef struct int_Node int_Node;
typedef struct int_Mod int_Mod;
typedef struct int_stack_pp int_stack_pp;

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

struct int_stack_pp
{
  int_Node* head[MAX_OP];
  int num_el;
  int live_version;
};

int_stack_pp* int_init_stack_pp();
bool int_stack_isEmpty_pp(int_stack_pp* deque);
bool int_stack_push_pp(int_stack_pp* deque, int data);

int int_stack_pop_pp(int_stack_pp* deque);

void int_print_stack_pp(int_stack_pp* list, int version);


#endif
