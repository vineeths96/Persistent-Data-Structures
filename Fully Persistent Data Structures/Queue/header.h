#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_OP 25
#define STR_SIZE 25
#define JUNK -1
#define UNUSED -1

typedef struct int_Node int_Node;
typedef struct int_Mod int_Mod;
typedef struct int_queue_fp int_queue_fp;

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

struct int_queue_fp
{
  int_Node* head[MAX_OP];
  int num_el;
  int live_version;
};

int_queue_fp* int_init_queue_fp();

bool int_queue_isEmpty_fp(int_queue_fp* queue, int version);

bool int_queue_enqueue_fp(int_queue_fp* queue, int data, int version);
int int_queue_dequeue_fp(int_queue_fp* queue, int version);

void int_print_queue_fp(int_queue_fp* list, int version);


#endif
