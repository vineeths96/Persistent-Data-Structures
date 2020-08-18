#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_OP 25
#define STR_SIZE 25
#define JUNK -1
#define UNUSED -1

typedef struct int_Node int_Node;
typedef struct int_Mod int_Mod;
typedef struct int_deque_fp int_deque_fp;

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

struct int_deque_fp
{
  int_Node* head[MAX_OP];
  int num_el;
  int live_version;
};

int_deque_fp* int_init_deque_fp();

bool int_deque_isEmpty_fp(int_deque_fp* deque, int version);
bool int_deque_insertFront_fp(int_deque_fp* deque, int data, int version);
bool int_deque_insertRear_fp(int_deque_fp* deque, int data, int version);
int int_deque_deleteFront_fp(int_deque_fp* deque, int version);
int int_deque_deleteRear_fp(int_deque_fp* deque, int version);

void int_print_deque_fp(int_deque_fp* list, int version);


#endif
