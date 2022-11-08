#ifndef _LINKED_LIST_STACK_H_
#define _LINKED_LIST_STACK_H_

#include <stdlib.h>
#include <stdio.h>
#include "data_struct.h"

void print_stack(stack_t *stk);

void print_stack_linked_list(stack_t *stk);

void free_linked_list_stk(stack_t *stk);

void free_add_list(node_add_t *head);

char pop(stack_t *stk, node_add_t **add);

void push(stack_t *stk, node_t *node);

node_t *create_node(char x);

void init_stack_node(stack_t **stk);

int is_empty(stack_t *stk);

#endif //_LINKED_LIST_STACK_H_